#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void clock_setup(void) {
    // set STM32 to 168 MHz
    rcc_clock_setup_hse_3v3(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void) {
    // Enable GPIOA clock
    rcc_periph_clock_enable(RCC_GPIOA);

    // Set GPIO8 (in GPIO port A) to 'output push-pull'
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
}

static void button_setup(void) {
    // Enable GPIOC clock
    rcc_periph_clock_enable(RCC_GPIOC);

    // Set GPIO1 (in GPIO port C) to 'input open-drain'
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO1);
}

int main(void) {
    clock_setup();
    button_setup();
    gpio_setup();

    // Blink the LED (PA8) on the board
    int i;
    uint16_t portc = 0;
    while (1) {

        portc = GPIOC_IDR;
        if ( (portc & (1 << 1)) != 0) {
            gpio_set(GPIOA, GPIO8);
        } else {
            gpio_clear(GPIOA, GPIO8);
        }

        __asm__("nop");
    }

    return 0;
}
