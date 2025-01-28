#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/watchdog.h"

#include "teclado/tecladoMatricial.h"
#include "animacoes/animacoes.h"

// Controlar leds 5x5
#include "hardware/pio.h"
#include "ws2818b.pio.h"

// Constantes
#define LED_PIN 7
#define NUM_LEDS 25
#define NUM_FRAMES 5

const uint8_t buzzer_pin = 10;

void inicializar_pinos();
char verificar_tecla();
void ligar_todos_leds(uint8_t r, uint8_t g, uint8_t b, float brilho, PIO pio, uint sm);
void animacao_pio(double desenho[5][25][3], PIO pio, uint sm, uint tempo_frame);
void desenhaRBG(double frame[][3], PIO pio, uint sm);

int main()
{
    inicializar_pinos();
    stdio_init_all();
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2818b_program);
    ws2818b_program_init(pio, sm, offset, LED_PIN, 800000);

    sleep_ms(1000);

    while (true)
    {
        char tecla = verificar_tecla(); // Obtém a tecla pressionada
        // Colocando esse if não vai entrar toda hora no printf, então não vai imprimir toda hora.
        if (tecla != '\0')

        {
            printf("Tecla pressionada: %c\n", tecla);
            // Utilizando switch para simplificar os casos
            switch (tecla)
            {
            case '0':
                animacao_pio(animacao_sabre, pio, sm, 500);
                ligar_todos_leds(0, 0, 0, 0.0, pio, sm); // Desligar todos os leds
                break;
            case '1':
                sleep_ms(100);
                break;
            case '2':
                sleep_ms(100);
                break;
            case '3':
                sleep_ms(100);
                break;
            case '4':
                sleep_ms(100);
                break;
            case '5':
                sleep_ms(100);
                break;
            case '6':
                sleep_ms(100);
                break;
            case '7':
                sleep_ms(100);
                break;
            case '8':
                sleep_ms(100);
                break;
            case '9':
                sleep_ms(100);
                break;
            case 'A':
                ligar_todos_leds(0, 0, 0, 0.0, pio, sm); // Desligar todos os leds
                break;
            case 'B':
                ligar_todos_leds(0, 255, 0, 1.0, pio, sm); // Ligar Cor Azul 100%
                break;
            case 'C':
                ligar_todos_leds(255, 0, 0, 1.0, pio, sm); // Ligar Cor Vermelho 80%
                break;
            case 'D':
                ligar_todos_leds(0, 0, 255, 0.5, pio, sm); // ligar Cor Verde 50%
                break;
            case '#':
                ligar_todos_leds(255, 255, 255, 1.0, pio, sm); // ligar Cor Branca 20%
                break;
            case '*':
                reset_usb_boot(0, 0);
                sleep_ms(100);
                break;
            default:
                sleep_ms(100);
                break;
            }
        }
        }
    return 0;
}

// função para ligar todos os leds 5x5
void ligar_todos_leds(uint8_t r, uint8_t g, uint8_t b, float brilho, PIO pio, uint sm)
{
    // ajustar a cor do brilh
    r = (uint8_t)(r * brilho);
    g = (uint8_t)(g * brilho);
    b = (uint8_t)(b * brilho);

    /*uint32_t adjusted_color = (r << 16) | (g << 8) | b;

    for (int i = 0; i < NUM_LEDS; i++)
    {
        pio_sm_put_blocking(pio, sm, adjusted_color);
    }*/
    for (int i = 0; i < NUM_LEDS; i++)
    {
        pio_sm_put_blocking(pio, sm, b); // WS2818B usa ordem GRB
        pio_sm_put_blocking(pio, sm, r);
        pio_sm_put_blocking(pio, sm, g);
    }
}

//Função responsável por acionar os leds da matriz.
void desenhaRBG(double frame[][3], PIO pio, uint sm){
    for(uint8_t i = 0; i < NUM_LEDS; i++){
        uint8_t BLUE = 0, RED = 0, GREEN = 0;

        RED = (uint8_t) (255 * frame[24-i][0]);
        GREEN = (uint8_t) (255 * frame[24-i][1]);
        BLUE = (uint8_t) (255 * frame[24-i][2]);

        pio_sm_put_blocking(pio, sm, GREEN);
        pio_sm_put_blocking(pio, sm, RED);
        pio_sm_put_blocking(pio, sm, BLUE);
    }
}

// função para desenhar a animação
void animacao_pio(double desenho[5][25][3], PIO pio, uint sm, uint tempo_frame){
    int valor_led;
    uint8_t r, g, b;
    
    for(int j=0; j<NUM_FRAMES; j++){
        desenhaRBG(desenho[j], pio, sm);
        sleep_ms(tempo_frame);
    }
}
