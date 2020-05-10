#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>

/* https://github.com/1Bitsy/1bitsy-examples/blob/master/examples/1bitsy/timer2_blink/timer2_blink.c */

volatile uint32_t system_millis;

void sys_tick_handler(void) {
    system_millis++;
}

/* sleep for delay milliseconds. */
static void msleep(uint32_t delay) {
    uint32_t wake = system_millis + delay;
    while (wake > system_millis);
}

/*
 * systick_setup(void)
 *
 * This function sets up the 1khz "system tick" count.
 * The SYSTICK counter is a standard feature of the Cortex-M series.
 */
static void systick_setup() {
    /* clock rate / 1000 to get 1mS interrupt rate */
    systick_set_reload(168000); // 168MHz
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    // do this last
    systick_interrupt_enable();
}

static void clock_setup(void) {
    // set STM32 to 168 MHz using the HSE clock (external)
    rcc_clock_setup_hse_3v3(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
}

int main(void) {
    clock_setup();
    systick_setup();
    gpio_setup();

    // Blink the LED (PA8) on the board
    while (1) {
        gpio_set(GPIOA, GPIO8);
        msleep(1000);
        gpio_clear(GPIOA, GPIO8);
        msleep(100);
    }

    return 0;
}
