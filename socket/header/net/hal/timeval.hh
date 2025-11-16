#pragma once

#include <sys/time.h>

// https://man7.org/linux/man-pages/man3/timeval.3type.html
// https://man7.org/linux/man-pages/man2/gettimeofday.2.html
// https://man7.org/linux/man-pages/man3/pmtimeval.3.html

namespace flp::Net {

enum class TimeOfDayError {
  Fault = EFAULT,

  Inval = EINVAL,
  Invalid = Inval,

  Perm = EPERM,
};

void foo() {
  timeval tv;
  tv.tv_sec = 2;
  tv.tv_usec = 500'000;

  gettimeofday();
  settimeofday();

  gettimeofday();
  pmtimevalNow();
  pmtimevalInc();
  pmtimevalDec();
  pmtimevalAdd();
  pmtimevalSub();
}

}
