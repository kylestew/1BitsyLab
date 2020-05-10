#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>


static void exti_setup() {
    // Enable GPIOC clock
    rcc_periph_clock_enable(RCC_GPIOC);

    // Enable AFIO clock
    rcc_periph_clock_enable(RCC_SYSCFG);

    // Enable EXTI1 interrupt
    nvic_enable_irq(NVIC_EXTI1_IRQ);

    // Set GPIO1 (in GPIO port C) to 'input open-drain'
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO1);

    // Configure the EXTI subsystem
    exti_select_source(EXTI1, GPIOC);
    exti_set_trigger(EXTI1, EXTI_TRIGGER_FALLING);
    exti_enable_request(EXTI1);
}

void exti1_isr(void) {
    exti_reset_request(EXTI1);

//    if (exti_direction == FALLING) {
//        gpio_set(GPIOC, GPIO12);
//        exti_direction = RISING;
//        exti_set_trigger(EXTI0, EXTI_TRIGGER_RISING);
//    } else {
//        gpio_clear(GPIOC, GPIO12);
//        exti_direction = FALLING;
//        exti_set_trigger(EXTI0, EXTI_TRIGGER_FALLING);
//    }
}

static void gpio_setup(void) {
    // LED output on GPIO A
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);




    // Enable GPIOC clock
    rcc_periph_clock_enable(RCC_GPIOC);

    // Set GPIO1 (in GPIO port C) to 'input open-drain'
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO1);
}

int main(void) {
    // set STM32 to 168 MHz
    rcc_clock_setup_hse_3v3(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

    gpio_setup();

    exti_setup();

    while (1) {
        __asm__("nop");
    }

    return 0;
}
