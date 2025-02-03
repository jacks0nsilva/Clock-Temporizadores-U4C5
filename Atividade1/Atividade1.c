#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_GREEN 11 // Define o pino do LED verde
#define LED_PIN_YELLOW 12 // Define o pino do LED amarelo
#define LED_PIN_RED 13 // Define o pino do LED vermelho

static volatile int count = 0;


void initialize_gpio(uint pin, uint mode){
    gpio_init(pin); // Inicializa o GPIO
    gpio_set_dir(pin, mode); // Define o pino como saída
    gpio_put(pin, 0); // Inicializa o pino em nível lógico baixo
}

bool repeating_timer_callback(struct repeating_timer *timer) {
    printf("Callback is on!\n");
    switch(count){
        case 0:
            printf("Case 0\n");
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_GREEN, 0);
            gpio_put(LED_PIN_YELLOW, 0);
            count++;
            break;
        case 1:
            printf("Case 1\n");
            gpio_put(LED_PIN_YELLOW, 1);
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 0);
            count++;
            break;
        case 2:
            printf("Case 2\n");
            gpio_put(LED_PIN_GREEN, 1);
            gpio_put(LED_PIN_YELLOW, 0);
            gpio_put(LED_PIN_RED, 0);
            count = 0;
            break;
        default:
            break;
    }
    return true;
}

int main()
{
    // Inicializa a comunicação serial
    stdio_init_all();
    initialize_gpio(LED_PIN_GREEN, GPIO_OUT);
    initialize_gpio(LED_PIN_YELLOW, GPIO_OUT);
    initialize_gpio(LED_PIN_RED, GPIO_OUT);

    // Declaração da estrutura do temporizador
    // Essa estrutura armzena informações sobre o temporizador
    struct repeating_timer timer;

    // Inicializa o temporizador com um intervalo de 1000ms (1 segundo)
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        sleep_ms(10); // Pausa por 10 milissegundos para não sobrecarregar o processador
    }
}
