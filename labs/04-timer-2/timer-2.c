#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

/* https://github.com/1Bitsy/1bitsy-examples/blob/master/examples/1bitsy/timer2_blink/timer2_blink.c */

// 168,000,000 MHz clock so for 1 second interrup, need PRESCALE * PERIOD = 168M
#define PRESCALE    10000
#define PERIOD      16800

volatile uint32_t system_millis;

void tim2_isr(void) {
    if (timer_interrupt_source(TIM2, TIM_SR_UIF)) {
        timer_clear_flag(TIM2, TIM_SR_UIF);
        gpio_toggle(GPIOA, GPIO8);
    }
}

static void timer2_setup(void) {
    rcc_periph_clock_enable(RCC_TIM2);
//    timer_reset(TIM2);

    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM2, PRESCALE);
    timer_set_period(TIM2, PERIOD);
    timer_enable_update_event(TIM2);
    timer_generate_event(TIM2, TIM_EGR_UG);
    timer_enable_irq(TIM2, TIM_DIER_UIE);
    timer_continuous_mode(TIM2);
    timer_enable_preload(TIM2);

    nvic_enable_irq(NVIC_TIM2_IRQ);
    timer_enable_counter(TIM2);
}

static void clock_setup(void) {
    rcc_clock_setup_hse_3v3(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
}

int main(void) {
    clock_setup();
    gpio_setup();
    timer2_setup();

    while (1) {}

    return 0;
}
