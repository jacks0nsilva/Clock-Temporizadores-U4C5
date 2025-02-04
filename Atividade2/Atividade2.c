#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_PIN 5

void initialize_gpio(uint pin, bool input) {
    gpio_init(pin);
    gpio_set_dir(pin, input);
}


int main()
{
    stdio_init_all();

    initialize_gpio(LED_PIN_GREEN, GPIO_OUT);
    initialize_gpio(LED_PIN_BLUE, GPIO_OUT);
    initialize_gpio(LED_PIN_RED, GPIO_OUT);
    initialize_gpio(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
