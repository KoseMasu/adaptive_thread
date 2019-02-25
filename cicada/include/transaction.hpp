#pragma once

#include <stdio.h>

#include <atomic>
#include <iostream>
#include <map>
#include <queue>

#include "../../include/debug.hpp"
#include "../../include/util.hpp"

#include "common.hpp"
#include "procedure.hpp"
#include "tuple.hpp"
#include "timeStamp.hpp"
#include "version.hpp"
#include "result.hpp"

using namespace std;

enum class TransactionStatus : uint8_t {
  invalid,
  inflight,
  commit,
  abort,
};

class TxExecutor {
public:
  TransactionStatus status = TransactionStatus::invalid;
  TimeStamp wts;
  vector<ReadElement> readSet;
  vector<WriteElement> writeSet;
  queue<GCElement> gcq;
  Result rsobject;

  bool ronly;
  uint8_t thid;
  uint64_t rts;
  uint64_t start, stop; // for one-sided synchronization
  uint64_t spinstart, spinstop; // for spin-wait
  uint64_t grpcmt_start, grpcmt_stop; // for group commit
  uint64_t GCstart, GCstop; // for garbage collection
  uint64_t continuingCommit;

  char returnVal[VAL_SIZE] = {};
  char writeVal[VAL_SIZE] = {};

  TxExecutor(unsigned int newThid) {
    // wait to initialize MinWts
    while(MinWts.load(memory_order_acquire) == 0);
    rts = MinWts.load(memory_order_acquire) - 1;
    wts.generateTimeStampFirst(thid);
    ronly = false;
    thid = newThid;

    __atomic_store_n(&(ThreadWtsArray[thid].obj), wts.ts, __ATOMIC_RELEASE);
    unsigned int expected, desired;
    expected = FirstAllocateTimestamp.load(memory_order_acquire);
    for (;;) {
      desired = expected + 1;
      if (FirstAllocateTimestamp.compare_exchange_weak(expected, desired, memory_order_acq_rel)) break;
    }

    readSet.reserve(MAX_OPE);
    writeSet.reserve(MAX_OPE);

    continuingCommit = 0;
    rsobject.thid = thid;

    writeValGenerator(writeVal, VAL_SIZE, thid);

    start = rdtsc();
    GCstart = start;
  }

  void tbegin(bool ronly);
  char* tread(unsigned int key);
  void twrite(unsigned int key);
  bool validation();
  void writePhase();
  void swal();
  void pwal();  //parallel write ahead log.
  void precpv();  //pre-commit pending versions
  void cpv(); //commit pending versions
  void gcpv();  //group commit pending versions
  bool chkGcpvTimeout();
  void earlyAbort();
  void abort();
  void wSetClean();
  void displayWset();
  void mainte();  //maintenance
};
