#include "led.h"
#include "registers.h"

void ledInit() {
  // Open GPIOA clock
  RCC_APB2ENR |= (1 << 2);

  // Reset LED
  GPIOA_BSRR = (LED_PIN << 16);

  // set CNF/MODE TO 0000
  GPIOA_CRL &= ~(0xF << 20);

  // set MODE to OUTPUT
  GPIOA_CRL |= (0x2 << 20);
}

void ledToggle() {
  if (GPIOA_ODR & (1 << 5)) {
    // GPIO reset starts at 16, and I need to reset pin 5 hence 16+5=21
    GPIOA_BSRR = (1 << 21);
  } else {
    // GPIO set starts at 0, and I need to set pin 5
    GPIOA_BSRR = (1 << 5);
  }
}

void delay_ms(int ms) {
  volatile long cycles = ms * CYCLES_PR_MS;
  while (cycles != 0) {
    cycles--;
  }
}
