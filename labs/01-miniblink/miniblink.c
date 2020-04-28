#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

/*
* Blinks onboard LED (PA8)
*/

static void gpio_setup(void) {
  /* NOTE: we are not setting up any clocks, this means the MCU will run
   * on default settings using the internal oscillator.
   */

  // Enable GPIOA clock
  // Manually:
  // RCC_AHB1ENR |= RCC_AHB1ENR_IOPAEN;
  rcc_periph_clock_enable(RCC_GPIOA);

  // Set GPIO8 (in GPIO port A to 'output push-pull'
  // Manually:
  // GPIOA_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 0) + 2));
  // GPIOA_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((8 - 8) * 0));
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
}

int main(void) {
  gpio_setup();

  // Blink the LED (PA8) on the board
  int i;
  int j = 0;
  while (1) {
    // toggle LED on/off
    gpio_toggle(GPIOA, GPIO8);
    for (i = 0; i < 1000000; i++) {
      __asm__("nop");
    }
    j++;
  }

  return 0;
}
