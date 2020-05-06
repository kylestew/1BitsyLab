#include <stdint.h>

/*
* Blinks onboard LED (PA8)
*/


// memory mapped I/O accessors
// cast uint32_t value (the address) into pointer
#define MMIO32(addr)    (*(volatile uint32_t *)(addr))

// USERS GUIDE: 2-12 Memory Model
#define PERIPH_BASE         0x40000000U // unsigned 32-bit
// REF MAN: pg 65
#define PERIPH_BASE_AHB1    (PERIPH_BASE + 0x20000)
#define GPIO_PORT_A_BASE    (PERIPH_BASE_AHB1 + 0x0000)
#define RCC_BASE            (PERIPH_BASE_AHB1 + 0x3800)
// REF MAN: pg 210
#define RCC_AHB1ENR         MMIO32(RCC_BASE + 0x30)
#define RCC_AHB1ENR_GPIOAEN (1 << 0)
// REF MAN: pg 288
#define GPIO_MODER(port)    MMIO32((port) + 0x00)
#define GPIO_BSRR(port)     MMIO32((port) + 0x18)

// REF MAN: pg 281
#define GPIO_MODE_OUTPUT    0x01

// aliases
#define RCC_AHB1ENR_IOPAEN  RCC_AHB1ENR_GPIOAEN
#define GPIOA               GPIO_PORT_A_BASE
#define GPIO8       (1 << 8)


static void gpio_setup(void) {
  /* NOTE: we are not setting up any clocks, this means the MCU will run
   * on default settings using the internal oscillator.
   */

  // Enable GPIOA clock
  RCC_AHB1ENR |= RCC_AHB1ENR_IOPAEN;

  // Enable GPIOA8 as an output in the GPIOA_MODER register
  // REF MAN: pg 281
  GPIO_MODER(GPIOA) |= (GPIO_MODE_OUTPUT << 16);
}

int main(void) {
  gpio_setup();

  // Blink the LED (PA8) on the board
  int i;
  while (1) {
      // set
      GPIO_BSRR(GPIOA) = GPIO8;

      for (i = 0; i < 500000; i++) {
          __asm__("nop");
      }

      // clear
      GPIO_BSRR(GPIOA) = (GPIO8 << 16);

      for (i = 0; i < 1000000; i++) {
          __asm__("nop");
      }
  }

  return 0;
}
