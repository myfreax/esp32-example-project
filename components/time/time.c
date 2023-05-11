#include "time.h"

int64_t time_currnet_us(struct timeval *tv) {
  gettimeofday(tv, NULL);
  int64_t time_us = (int64_t)tv->tv_sec * 1000000L + (int64_t)tv->tv_usec;
  return time_us;
}
