#pragma once

#include <x86intrin.h>

#include <atomic>
#include <cmath>
#include <iostream>

#include "atomic_wrapper.hh"
#include "result.hh"
#include "tsc.hh"
#include "util.hh"

using namespace std;

class Backoff {
public:
  static std::atomic<double> Backoff_;
  static constexpr double kMinBackoff = 0;
  static constexpr double kMaxBackoff = 1000;
  //static constexpr double kIncrBackoff = 100;
  static constexpr double kIncrBackoff = 0.5;
  //static constexpr double k = 10;
  static bool thad[224];
  static int act_th_num;
#if COUNT_THREAD
  static bool threadSleep[224]; //64byteにする
  static bool tslook;
#endif
  uint64_t last_committed_txs_ = 0;
  double last_committed_tput_ = 0;
  uint64_t last_backoff_ = 0;
  uint64_t last_time_ = 0;
  size_t clocks_per_us_;
#if BACK_OFF_ANALYZE
  uint64_t last_time_analyze = 0;
  vector<double> backoff_analyze_result;
  vector<double> backoff_analyze_result_tput;
#endif
#if COUNT_THREAD
  uint64_t last_time_tc = 0;
  vector<int> tc_result;
#endif

  Backoff(size_t clocks_per_us) {
    init(clocks_per_us);
  }
#if BACK_OFF_ANALYZE
  ~Backoff(){
    for(auto i_backoff=backoff_analyze_result.begin(); i_backoff != backoff_analyze_result.end(); ++i_backoff){
      cout<<*i_backoff<<endl;
    }
    if(backoff_analyze_result.size()>0)
    cout<<endl<<endl<<endl<<"############################"<<endl<<"############################"<<endl<<endl<<endl;
    for(auto i_backoff=backoff_analyze_result_tput.begin(); i_backoff != backoff_analyze_result_tput.end(); ++i_backoff){
      cout<<*i_backoff<<endl;
    }
  }
#endif
#if COUNT_THREAD
  ~Backoff(){
    for(auto i_backoff=tc_result.begin(); i_backoff != tc_result.end(); ++i_backoff){
      cout<<*i_backoff<<endl;
      //cout<<"b";
    }
    //cout<<"a";
  }
#endif
  void init(size_t clocks_per_us) {
    last_time_ = rdtscp();
    for(int i=0;i<224;i++){
      thad[i]=0;
    }
    thad[0]=1;
    act_th_num = 2;
#if BACK_OFF_ANALYZE
    last_time_analyze = rdtscp();
    backoff_analyze_result.reserve(600);
    backoff_analyze_result_tput.reserve(600);
#endif
#if COUNT_THREAD
    tc_result.reserve(60);
    tslook = false;
#endif    
    clocks_per_us_ = clocks_per_us;
  }

  bool thad_ch_sleep(size_t id){
   
      //cout<<thad[id]<<"  ";
    return thad[id]==0;
  }

  bool check_update_backoff() {
    if (chkClkSpan(last_time_, rdtscp(), clocks_per_us_ * 50000))

      return true;
    else
      return false;
  }
#if BACK_OFF_ANALYZE
  bool check_analyze_backoff() {
    if (chkClkSpan(last_time_analyze, rdtscp(), clocks_per_us_ * 500000))
      return true;
    else
      return false;
  }
  void analyze_backoff(){
    last_time_analyze = rdtscp();
    double result_backoff = Backoff_.load(std::memory_order_acquire);
   // cout<<result_backoff<<endl;
    //backoff_analyze_result.push_back(result_backoff);
    backoff_analyze_result.push_back(act_th_num);
    backoff_analyze_result_tput.push_back(last_committed_tput_);
  }
#endif
#if COUNT_THREAD
  bool check_threadCount() {
    if (chkClkSpan(last_time_tc, rdtscp(), clocks_per_us_ * 50000))
      return true;
    else
      return false;
  }
  void threadCount(){
    last_time_tc = rdtscp();
    int result_tc=0;
    tslook = 1;
    for(int i=0;i<224;i++){
      if(threadSleep[i] == true)result_tc++;;
    }
    //cout<<result_tc<<endl;
    tc_result.push_back(result_tc);
    tslook = 0;
  }
#endif
  void update_backoff(const uint64_t committed_txs) {
    uint64_t now = rdtscp();
    uint64_t time_diff = now - last_time_;
    last_time_ = now;

    double new_backoff = Backoff_.load(std::memory_order_acquire);
    double backoff_diff = new_backoff - last_backoff_;

    uint64_t committed_diff = committed_txs - last_committed_txs_;
    double committed_tput = static_cast<double>(committed_diff) /
                            (static_cast<double>(time_diff) / clocks_per_us_) *
                            pow(10.0, 6);
    double committed_tput_diff = committed_tput - last_committed_tput_;

    last_committed_txs_ = committed_txs;
    last_committed_tput_ = committed_tput;
    last_backoff_ = new_backoff;
    
    /*
    cout << "=====" << endl;
    cout << "committed_tput_diff:\t" <<
    static_cast<int64_t>(committed_tput_diff) << endl; cout <<
    "last_backoff_:\t" << last_backoff_ << endl; cout << "backoff_diff:\t" <<
    backoff_diff << endl;
    */
    
    double gradient;
    if (backoff_diff != 0)
      gradient = committed_tput_diff / backoff_diff;//cicada提案式
      //gradient = committed_tput_diff /committed_tput/backoff_diff;//上昇％の傾き 
    else
      gradient = 0;
      //cout<<gradient*k<<endl;
      //cout<<committed_tput_diff<<" / "<<committed_tput<<endl;
    //if (gradient!=0)
      //new_backoff += k * gradient;
    if (gradient < 0){
      new_backoff -= kIncrBackoff;
      if(act_th_num<224)act_th_num+=1;
    }
    else if (gradient > 0){
      new_backoff += kIncrBackoff;
      if(act_th_num>1)act_th_num-=1;
    }
    else {
      if ((committed_txs & 1) == 0 ||
          new_backoff == kMaxBackoff){  // 確率はおよそ 1/2, すなわちランダム．
        new_backoff -= kIncrBackoff;
	if(act_th_num<224)act_th_num+=1;
      }
      else if ((committed_txs & 1) == 1 || new_backoff == kMinBackoff){
        new_backoff += kIncrBackoff;
        if(act_th_num>1)act_th_num-=1;
      }
    }

    if (new_backoff < kMinBackoff)
      new_backoff = kMinBackoff;
    else if (new_backoff > kMaxBackoff)
      new_backoff = kMaxBackoff;
    // new_backoff = 0;
    Backoff_.store(new_backoff, std::memory_order_release);
    for(int i=0;i<act_th_num;i++){
      thad[i] = 1;
    }
    for(int i=0;i<224-act_th_num;i++){
      thad[i+act_th_num] = 0;
    }
    //cout<<act_th_num<<endl;
  }
#if COUNT_THREAD
  static void backoff(size_t clocks_per_us,size_t id){//,Xoroshiro128Plus &rnd) {
#endif
  static void backoff(size_t clocks_per_us){
    uint64_t start(rdtscp()), stop;
    double now_backoff = Backoff_.load(std::memory_order_acquire);

    // printf("clocks_per_us * now_backoff:\t%lu\n",
    // static_cast<uint64_t>(static_cast<double>(clocks_per_us) * now_backoff));
    
    //ランダムバックオフ用
    //int backoff_clock = static_cast<int>(static_cast<double>(clocks_per_us) *now_backoff);
    //if(backoff_clock>0) backoff_clock = rnd.next() % backoff_clock;
#if COUNT_THREAD
    if(tslook==0){
      threadSleep[id]=1;
    }
#endif
    for (;;) {
      _mm_pause();
      stop = rdtscp();
      //ランダムバックオフ用
      //if (chkClkSpan(start, stop,backoff_clock))
      if (chkClkSpan(start, stop,
                    static_cast<uint64_t>(static_cast<double>(clocks_per_us) *
                                           now_backoff)))
        break;
    }
#if COUNT_THREAD
    if(tslook==0){
      threadSleep[id]=0;
    }
#endif
  }
};


[[maybe_unused]] inline void
leaderBackoffWork([[maybe_unused]] Backoff &backoff, [[maybe_unused]] std::vector <Result> &res) {
  if (backoff.check_update_backoff()) {
    uint64_t sum_committed_txs(0);
    for (auto &th : res) {
      sum_committed_txs += loadAcquire(th.local_commit_counts_);
    }
    backoff.update_backoff(sum_committed_txs);
  }
#if BACK_OFF_ANALYZE
  if(backoff.check_analyze_backoff()){
    backoff.analyze_backoff();
  }
#endif
#if COUNT_THREAD
  if(backoff.check_threadCount()){
    backoff.threadCount();
  }
#endif
}

#ifdef GLOBAL_VALUE_DEFINE
std::atomic<double> Backoff::Backoff_(0);
bool Backoff::thad[224]={};
int Backoff::act_th_num=1;
#if COUNT_THREAD
bool Backoff::threadSleep[224] = {}; //64byteにする
bool Backoff::tslook = false;
#endif
#endif
