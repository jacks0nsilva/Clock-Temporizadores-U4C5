#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_COUNT 3
#define BUTTON_PIN 5

// Pinos dos LEDs em ordem de desligamento
const uint LED_PINS[LED_COUNT] = {11, 12, 13}; // Verde, Azul, Vermelho

bool leds_on = false; // Estado dos LEDs
int led_index = 0;    // Índice do LED a ser apagado

// Inicializa um pino como entrada ou saída
void initialize_gpio(uint pin, bool is_output) {
    gpio_init(pin);
    gpio_set_dir(pin, is_output ? GPIO_OUT : GPIO_IN);
    if (!is_output) gpio_pull_up(pin); // Habilita pull-up para o botão
}

// Callback para desligar os LEDs um por um
int64_t turn_off_led(alarm_id_t id, void *user_data) {
    if (led_index < LED_COUNT) {
        gpio_put(LED_PINS[led_index], 0); // Desliga o LED atual
        printf("LED %d apagado!\n", LED_PINS[led_index]);
        led_index++;

        if (led_index < LED_COUNT) {
            add_alarm_in_ms(3000, turn_off_led, NULL, false); // Agenda o próximo desligamento
        } else {
            leds_on = false; // Todos os LEDs foram apagados
        }
    }
    return 0;
}

int main() {
    stdio_init_all();

    // Inicializa LEDs e botão
    for (int i = 0; i < LED_COUNT; i++) {
        initialize_gpio(LED_PINS[i], GPIO_OUT);
        gpio_put(LED_PINS[i], 0); // Garante que todos iniciem apagados
    }
    initialize_gpio(BUTTON_PIN, GPIO_IN);

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0 && !leds_on) { // Se o botão for pressionado e os LEDs estiverem apagados
            sleep_ms(50); // Debounce
            printf("Botão pressionado!\n");

            // Acende todos os LEDs
            for (int i = 0; i < LED_COUNT; i++) {
                gpio_put(LED_PINS[i], 1);
            }

            leds_on = true; // Indica que os LEDs estão acesos
            led_index = 0; // Reseta o índice de desligamento
            add_alarm_in_ms(3000, turn_off_led, NULL, false); // Inicia o desligamento gradual
        }
        sleep_ms(10); // Evita uso excessivo da CPU
    }
}
