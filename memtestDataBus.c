#include <stdint.h>
#include <string.h>

typedef uint32_t datum;

int memtestDataBus(datum *pAddress, datum **ppFailAddr) {
  datum pattern;
  *ppFailAddr = NULL;

  for (pattern = 1; pattern != 0; pattern <<= = 1) {
    *pAddress = pattern;
    if (*pAddress != pattern) {
      *ppFailAddr = pAddress;
      return 0;
    }
  }
  return 1;
}
