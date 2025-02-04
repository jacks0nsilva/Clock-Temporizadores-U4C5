#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_COUNT 3 // Quantidade de LEDs

// Struct para representar um LED
typedef struct {
    uint pin; // Pino do LED
    bool state; // Estado do LED (ligado/desligado)
} LED;

LED leds[LED_COUNT] = {
    {13, false}, // LED vermelho 
    {12, false}, // LED amarelo 
    {11, false} // LED verde 

};



// Inicializa os pinos dos LEDs
void initialize_gpio(LED *led){
    gpio_init(led->pin); // Inicializa o GPIO
    gpio_set_dir(led->pin, GPIO_OUT); // Define o pino como saída
    gpio_put(led->pin, 0); // Inicializa o pino em nível lógico baixo
}

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *timer) {
    static int led_index = 1; // Índice do LED que será aceso
    printf("Callback is on! | index: %d\n", led_index);
    
// Desliga todos os LEDs antes de ligar o próximo
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].state = false;
        gpio_put(leds[i].pin, leds[i].state);
    }

    // Liga apenas o LED atual
    leds[led_index].state = true;
    gpio_put(leds[led_index].pin, leds[led_index].state);

    // Atualiza o index para o próximo LED na próxima chamada do timer
    led_index = (led_index + 1) % LED_COUNT;
    return true;
}

int main()
{
    // Inicializa a comunicação serial
    stdio_init_all();

    // Inicializa os pinos dos LEDs
    for(int i = 0; i < LED_COUNT; i++){
        initialize_gpio(&leds[i]);
    }

    // Declaração da estrutura do temporizador
    // Essa estrutura armzena informações sobre o temporizador
    struct repeating_timer timer;

    // Inicializa o temporizador com um intervalo de 3000ms (3 segundos)
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    leds[0].state = true; // Habilita o LED vermelho
    gpio_put(leds[0].pin, leds[0].state); // Acerde o LED vermelho
    while (true) {
        sleep_ms(10); // Pausa por 10 milissegundos para não sobrecarregar o processador
    }
}
