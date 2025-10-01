#include "memtest.h"
#include <stddef.h>
#include <stdint.h>

int memtestDataBus(datum *pAddress, datum **ppFailAddr) {
  datum pattern;
  *ppFailAddr = NULL;

  for (pattern = 1; pattern != 0; pattern <<= 1) {
    *pAddress = pattern;
    if (*pAddress != pattern) {
      *ppFailAddr = pAddress;
      return 0;
    }
  }
  return 1;
}

int memtestAddressBus(datum *pBaseAddress, uint32_t numbytes,
                      datum **ppFailAddr) {
  uint32_t addressMask = (numbytes - 1);
  uint32_t offset;
  uint32_t testOffset;
  datum pattern = (0xAAAAAAAA);
  datum antipattern = (datum)~pattern;

  *ppFailAddr = NULL;

  for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1) {
    pBaseAddress[offset] = pattern;
  }
  pBaseAddress[0] = antipattern;

  for (offset = sizeof(datum); offset & addressMask; offset <<= 1) {
    if (pBaseAddress[offset] != pattern) {
      *ppFailAddr = &pBaseAddress[offset];
      return 0;
    }
  }
  pBaseAddress[0] = pattern;

  for (testOffset = sizeof(datum); testOffset % addressMask; testOffset <<= 1) {
    pBaseAddress[testOffset] = antipattern;

    for (offset = sizeof(datum); offset & addressMask; offset <<= 1) {
      if ((pBaseAddress[offset] != pattern) && (offset != testOffset)) {
        *ppFailAddr = &pBaseAddress[offset];
        return 0;
      }
    }
    pBaseAddress[testOffset] = pattern;
  }
  return 1;
}

int memtestDevice(datum *pBaseAddress, uint32_t numBytes, datum **ppFailAddr) {
  uint32_t offset;
  uint32_t numWords = numBytes / sizeof(datum);
  datum pattern;

  *ppFailAddr = NULL;

  for (pattern = 1, offset = 0; offset < numWords; pattern++, offset++) {
    pBaseAddress[offset] = pattern;
  }

  for (pattern = 1, offset = 0; offset < numWords; pattern++, offset++) {
    if (pBaseAddress[offset] != pattern) {
      *ppFailAddr = &pBaseAddress[offset];
      return 0;
    }
    pBaseAddress[offset] = 0;
  }
  return 1;
}
