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
uint32_t matriz_rgb(double b, double r, double g);
void desenha_pio(double *desenho, PIO pio, uint sm, uint tempo_frame);

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
                desenha_pio(animacao_sabre, pio, sm, 500);
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

// função para definição da intensidade dos leds
uint32_t matriz_rgb(double r, double g, double b)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// função para desenhar a animação
void desenha_pio(double *desenho, PIO pio, uint sm, uint tempo_frame){
    int valor_led;
    for(int j=0; j<NUM_FRAMES; j++){
        for(int i=0; i<NUM_LEDS; i++){
            valor_led = matriz_rgb(desenho[j][i]);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}