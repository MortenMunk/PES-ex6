#pragma once

#include <stdint.h>

typedef uint32_t datum;

int memtestDataBus(datum *pAddress, datum **ppFailAddr);
int memtestAddressBus(datum *pBaseAddress, uint32_t numbytes,
                      datum **ppFailAddr);
int memtestDevice(datum *pBaseAddress, uint32_t numBytes, datum **ppFailAddr);
