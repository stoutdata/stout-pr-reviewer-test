#include <stdint.h>

#define GPIO_BASE 0x40021000
#define GPIO_MODER   (*(volatile uint32_t *)(GPIO_BASE + 0x00))
#define GPIO_ODR     (*(volatile uint32_t *)(GPIO_BASE + 0x14))

void gpio_init(void) {
    // Configure PA5 as output (LED pin on STM32 Nucleo)
    GPIO_MODER &= ~(0x3 << (5 * 2));
    GPIO_MODER |=  (0x1 << (5 * 2));
}

void gpio_set_led(int on) {
    if (on) {
        GPIO_ODR |= (1 << 5);
    } else {
        GPIO_ODR &= ~(1 << 5);
    }
}
