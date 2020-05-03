
/*
* Blinks onboard LED (PA8)
*/

/*
static void gpio_setup(void) {
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
*/

int main(void) {
  //gpio_setup();

  while (1) {
    __asm__("nop");
  }

  return 0;
}
