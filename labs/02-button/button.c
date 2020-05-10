#include <stdint.h>

// memory mapped I/O accessors
// cast uint32_t value (the address) into pointer
#define MMIO32(addr)    (*(volatile uint32_t *)(addr))

// USERS GUIDE: 2-12 Memory Model
#define PERIPH_BASE         0x40000000U // unsigned 32-bit
// REF MAN: pg 65
#define PERIPH_BASE_AHB1    (PERIPH_BASE + 0x20000)
#define GPIO_PORT_A_BASE    (PERIPH_BASE_AHB1 + 0x0000)
#define GPIO_PORT_C_BASE    (PERIPH_BASE_AHB1 + 0x0800)
#define RCC_BASE            (PERIPH_BASE_AHB1 + 0x3800)
// REF MAN: pg 210
#define RCC_AHB1ENR         MMIO32(RCC_BASE + 0x30)
#define RCC_AHB1ENR_GPIOAEN (1 << 0)
#define RCC_AHB1ENR_GPIOCEN (1 << 2)
// REF MAN: pg 288
#define GPIO_MODER(port)    MMIO32((port) + 0x00)
#define GPIO_PUPDR(port)    MMIO32((port) + 0x0C)
#define GPIO_BSRR(port)     MMIO32((port) + 0x18)
#define GPIO_IDR(port)      MMIO32((port) + 0x10)

// REF MAN: pg 281
#define GPIO_MODE_INPUT     0x00
#define GPIO_MODE_OUTPUT    0x01
// REF MAN: pg 282
#define GPIO_PUPD_NONE      0x00

// aliases
#define RCC_AHB1ENR_IOPAEN  RCC_AHB1ENR_GPIOAEN
#define RCC_AHB1ENR_IOPCEN  RCC_AHB1ENR_GPIOCEN
#define GPIOA               GPIO_PORT_A_BASE
#define GPIOC               GPIO_PORT_C_BASE
#define GPIO1       (1 << 1)
#define GPIO8       (1 << 8)

// shift binary 11 left N positions in register
// where register has 2 bits per position
#define GPIO_MODE_MASK(n)   (0b11 << (2 * (n)))
#define GPIO_MODE(n, mode)  ((mode) << (2 * (n)))


static void gpio_setup(void) {
    // See 01-miniblink for details on enabling LED 1
    // Enable GPIOA clock
    RCC_AHB1ENR |= RCC_AHB1ENR_IOPAEN;
    // Enable GPIOA8 as an output in the GPIOA_MODER register
    // libopencm3 uses a mask-clear and set approach
    GPIO_MODER(GPIOA) &= ~GPIO_MODE_MASK(8); // clear
    GPIO_MODER(GPIOA) |= GPIO_MODE(8, GPIO_MODE_OUTPUT); // set
}

static void button_setup(void) {
    // Enable GPIOC clock
    RCC_AHB1ENR |= RCC_AHB1ENR_IOPCEN;

    // Button SW1 is pulled up externally via a 10k resistor to 3V3
    // pressing it pulls pin 9 (PC1) to ground
    GPIO_MODER(GPIOC) &= ~GPIO_MODE_MASK(1); // clear
    GPIO_MODER(GPIOC) |= GPIO_MODE(1, GPIO_MODE_INPUT); // set

    // need to set PC1 to input mode with no pull up/ pull (is external)
    // No PUPD is considered 'open-drain'
    GPIO_PUPDR(GPIOC) &= ~GPIO_MODE_MASK(1); // clear
   GPIO_PUPDR(GPIOC) |= GPIO_MODE(1, GPIO_PUPD_NONE); // set
}

int main(void) {
    gpio_setup();
    button_setup();

    while (1) {
        // is button pressed?
       if ((uint16_t)GPIO_IDR(GPIOC) & GPIO1) {
            // turn on LED
            GPIO_BSRR(GPIOA) = GPIO8;
        } else {
            // turn off LED
            GPIO_BSRR(GPIOA) = (GPIO8 << 16);
        }
        __asm__("nop");
    }

    return 0;
}
