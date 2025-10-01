#include "led.h"
#include "memtest.h"

#define BASE_ADDRESS (datum *)(0x20000000)
#define NUM_BYTES (20 * 1024)

int main() {
  datum *pFailAddr;

  ledInit();
  ledOff();

  if ((memtestDataBus(BASE_ADDRESS, &pFailAddr) != 1) ||
      (memtestAddressBus(BASE_ADDRESS, NUM_BYTES, &pFailAddr) != 1) ||
      (memtestDevice(BASE_ADDRESS, NUM_BYTES, &pFailAddr) != 1)) {
    ledOn();
    while (1) {
    };
  } else {
    while (1) {
      ledToggle();
      delay_ms(500);
    }
  }
}
