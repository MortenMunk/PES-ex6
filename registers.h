#pragma once

#define SYSCLK_HZ 8000000
#define CYCLES_PR_MS (SYSCLK_HZ / 1000)

#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800

#define RCC_APB2ENR (*(volatile unsigned long *)(RCC_BASE + 0x18))
#define GPIOA_CRL (*(volatile unsigned long *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile unsigned long *)(GPIOA_BASE + 0x0C))
#define GPIOA_BSRR (*(volatile unsigned long *)(GPIOA_BASE + 0x10))

#define LED_PIN (1 << 5)
