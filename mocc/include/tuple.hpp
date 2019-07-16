#pragma once

#include <string.h> // memcpy
#include <atomic>
#include <cstdint>

#include "lock.hpp"

#include "../../include/cache_line_size.hpp"

#define TEMP_THRESHOLD 5
#define TEMP_MAX 20
#define TEMP_RESET_US 100

struct Tidword {
  union {
    uint64_t obj;
    struct {
      uint64_t tid:32;
      uint64_t epoch:32;
    };
  };

  Tidword() {
    obj = 0;
  }

  bool operator==(const Tidword& right) const {
    return obj == right.obj;
  }

  bool operator!=(const Tidword& right) const {
    return !operator==(right);
  }

  bool operator<(const Tidword& right) const {
    return this->obj < right.obj;
  }
};

// 32bit temprature, 32bit epoch
struct Epotemp {
  union {
    uint64_t obj_;
    struct {
      uint64_t temp_:32;
      uint64_t epoch_:32;
    };
  };
  uint8_t pad[CACHE_LINE_SIZE - sizeof(uint64_t)];

  Epotemp() : obj_(0) {}
  Epotemp(uint64_t temp, uint64_t epoch) : temp_(temp), epoch_(epoch) {}

  bool operator==(const Epotemp& right) const {
    return obj_ == right.obj_;
  }

  bool operator!=(const Epotemp& right) const {
    return !operator==(right);
  }

  bool eqEpoch(uint64_t epo) {
    if (epoch_ == epo) return true;
    else return false;
  }
};

class Tuple {
public:
  Tidword tidword;
#ifdef RWLOCK
  RWLock rwlock;  // 4byte
  // size to here is 20 bytes
#endif
#ifdef MQLOCK
  MQLock mqlock;
#endif

  char keypad[KEY_SIZE];
  char val[VAL_SIZE];

#ifdef RWLOCK

#ifdef SHAVE_REC
  int8_t pad[4];
#endif // SHAVE_REC
#ifndef SHAVE_REC
  int8_t pad[CACHE_LINE_SIZE - ((20 + KEY_SIZE + VAL_SIZE) % CACHE_LINE_SIZE)];
#endif // SHAVE_REC

#endif // RWLOCK
};

