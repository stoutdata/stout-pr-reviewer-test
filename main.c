#include <stdio.h>

int main(void) {
    printf("Hello from firmware v1.0\n");
    return 0;
}

extern void gpio_init(void);
extern void gpio_set_led(int on);

void setup(void) {
    gpio_init();
    gpio_set_led(1);
}
