#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

/* https://github.com/1Bitsy/1bitsy-examples/blob/master/examples/1bitsy/timer2_blink/timer2_blink.c
 * https://github.com/libopencm3/libopencm3-examples/blob/master/examples/stm32/f4/stm32f4-discovery/timer/timer.c
 */

// 168,000,000 MHz clock so for 1 second interrup, need PRESCALE * PERIOD = 168M
#define PRESCALE    10000
#define PERIOD      16800

volatile uint32_t system_millis;

void tim2_isr(void) {
    if (timer_interrupt_source(TIM2, TIM_SR_UIF)) {
        timer_clear_flag(TIM2, TIM_SR_UIF);
        gpio_toggle(GPIOA, GPIO8);
        gpio_toggle(GPIOA, GPIO7);
    }
}

static void timer2_setup(void) {
    // enable TIM2 clock (bring online)
    rcc_periph_clock_enable(RCC_TIM2);

    // enable TIM2 interrupt
    nvic_enable_irq(NVIC_TIM2_IRQ);

    // reset TIM2 to defaults
    rcc_periph_reset_pulse(RST_TIM2);

    /*
     * Timer global mode:
     *
     */


    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_prescaler(TIM2, PRESCALE);
    timer_set_period(TIM2, PERIOD);
    timer_enable_update_event(TIM2);
    timer_generate_event(TIM2, TIM_EGR_UG);
    timer_continuous_mode(TIM2);
    timer_enable_preload(TIM2);

    timer_enable_counter(TIM2);

    timer_enable_irq(TIM2, TIM_DIER_UIE);
}

static void clock_setup(void) {
    rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);

    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
}

int main(void) {
    clock_setup();
    gpio_setup();
    timer2_setup();

    while (1) {}

    return 0;
}
