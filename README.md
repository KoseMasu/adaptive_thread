# CCBench : Redesign and Implement Many Concurrency Control

---

## Installing a binary distribution package
On Debian/Ubuntu Linux, execute below statement or bootstrap_apt.sh.
```
$ sudo apt update -y
$ sudo apt-get install -y libgflags-dev libgoogle-glog-dev cmake cmake-curses-gui libboost-filesystem-dev
```

## Prepare using
```
$ git clone this_repository
$ cd ccbench
$ source bootstrap.sh
```
Processing of bootstrap.sh :  
git submodule init, update. <br>
Build third_party/masstree, third_party/mimalloc.<br>
Export LD_LIBRARY_PATH to ./third_party/mimalloc/out/release for using mimalloc library.<br>
<br>
So it's script should be executed by "source" command.<br>
I recommend you that you also add LD_LIBRARY_PATH to your ~/.bashrc by yourself.
<br>
Each protocols has own Makefile, so you should build each.
<br>
Prepare gflags for command line options.
```
$ cd third_party/gflags
$ mkdir build
$ cd build
$ ccmake ..
  - Press 'c' to configure the build system and 'e' to ignore warnings.
  - Set CMAKE_INSTALL_PREFIX and other CMake variables and options.
  - Continue pressing 'c' until the option 'g' is available.
  - Then press 'g' to generate the configuration files for GNU Make.
$ make -j && make install
```
Prepare glog for command line options.
```
./autogen.sh && ./configure && make -j && make install
```
---

## Data Structure
### Masstree
This is a submodule.  
usage:  
`git submodule init`  
`git submodule update`  
tanabe's wrapper is include/masstree\_wrapper.hpp

---

## Experimental data
https://github.com/thawk105/ccdata 

---

## Runtime arguments
This system uses third_party/gflags and third_party/glog.<br>
So you can use without runtime arguments, then it executes with default args.<br>
You can also use runtime arguments like below.<br>
Note that args you don't set is used default args.<br>
```
$ ./cicada.exe -tuple_num=1000000 -thread_num=224
```

---

## Details for improving performance
- It uses xoroshiro128plus which is high performance random generator.
- It is friendly to Linux vertual memory system.
- It uses high performance memory allocator mimalloc/tbd appropriately.
- It reduces memory management cost by our original technique.
- It refrain from creating temporary objects to improve performance as much as possible.
- It fixed bug of original cicada.
- It modifies almost protocols appropriately to improve performance.

---

## Welcom
Welcom pull request about 
- Improvement of performance in any workloads.
- Bug fix.
- Improvement about comments (doxygen style is recommended).
- Improvement of versatile.
- Extending CCBench
  - Reference materials : https://github.com/thawk105/ccbench/pull/7
  
---

## TODO
- cmake and ninja build
- doxygen
- Jenkins
- google test
- improve software architecture
- improve coding about rvalue reference
- Constrain the function declaration to allow calls from lvalues or calls from rvalues.

---

## Acknowledgments
Takayuki.T dedicates special thanks to ...<br>
- Cybozu Labs Youth 8th term supported this activity. (2018/4/10 - 2019/4/10)<br>
- Takashi Hoshino who is very kind advisor from Cybozu Labs Youth.
- Hideyuki Kawashima/Osamu Tatebe who is very kind supervisor.

