#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

bool repeating_timer_callback(struct repeating_timer *timer) {
    printf("Callback is on!\n");
    return true;
}

int main()
{
    // Inicializa a comunicação serial
    stdio_init_all();

    // Declaração da estrutura do temporizador
    // Essa estrutura armzena informações sobre o temporizador
    struct repeating_timer timer;

    add_repeating_timer_ms(1000, repeating_timer_callback, NULL, &timer);

    while (true) {
        sleep_ms(10); // Pausa por 10 milissegundos para não sobrecarregar o processador
    }
}
