#include "led.h"
#include "memtest.h"

#define BASE_ADDRESS (datum *)(0x00500000)
#define NUM_BYTES (0x10000)

int main() {
  datum *pFailAddr;

  ledInit();
  ledOff();

  if ((memtestDataBus(BASE_ADDRESS, &pFailAddr) != 1) ||
      (memtestAddressBus(BASE_ADDRESS, NUM_BYTES, &pFailAddr) != 1) ||
      (memTestDevice(BASE_ADDRESS, NUM_BYTES, &pFailAddr) != 1)) {
    ledOn();
    return 0;
  } else {
    ledOn();
    return 1;
  }
}
