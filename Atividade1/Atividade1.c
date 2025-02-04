#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_COUNT 3 // Quantidade de LEDs
static volatile int led_index = 0; // Começa com o LED vermelho aceso

// Estrutura para representar um LED
typedef struct {
    uint pin;      // Pino do LED
    bool state;    // Estado do LED (ligado/desligado)
    char *message; // Mensagem exibida no terminal
} LED;

// Definição dos LEDs e suas mensagens
LED leds[LED_COUNT] = {
    {13, true, "PARE! O sinal está fechado."},  // LED vermelho (inicialmente ligado)
    {12, false, "ATENÇÃO! O sinal está amarelo."}, // LED amarelo
    {11, false, "PROSSIGA! O sinal está verde."}  // LED verde
};

// Inicializa os pinos dos LEDs
void initialize_gpio(LED *led) {
    gpio_init(led->pin); // Inicializa o pino do LED
    gpio_set_dir(led->pin, GPIO_OUT); // Define o pino como saída
    gpio_put(led->pin, led->state); // Mantém o estado inicial do LED
}

// Callback do temporizador para alternar os LEDs
bool repeating_timer_callback(struct repeating_timer *timer) {

    // Apaga apenas o LED anterior
    leds[led_index].state = false;
    gpio_put(leds[led_index].pin, leds[led_index].state);

    // Atualiza o índice para o próximo LED
    led_index = (led_index + 1) % LED_COUNT;

    // Liga o novo LED
    leds[led_index].state = true;
    gpio_put(leds[led_index].pin, leds[led_index].state);
    printf("Alterando o sinal!\n");

    return true;
}

int main() {
    stdio_init_all(); // Inicializa comunicação serial

    // Inicializa os pinos dos LEDs
    for (int i = 0; i < LED_COUNT; i++) {
        initialize_gpio(&leds[i]);
    }

    // Configura o temporizador para alternar os LEDs a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal: exibe a mensagem a cada 1 segundo
    while (true) {
        printf("%s\n", leds[led_index].message); // Exibe a mensagem do LED aceso
        sleep_ms(1000); // Aguarda 1 segundo antes de imprimir novamente
    }
}
