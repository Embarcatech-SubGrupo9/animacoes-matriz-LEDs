#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/watchdog.h"

//Controlar leds 5x5
#include "hardware/pio.h"
#include "ws2812.pio.h"

// Constantes
#define LED_PIN 7
#define NUM_LEDS 25

const int colunas = 4;
const int linhas = 4;
const int leds = 3;
const uint8_t led_pin[] = {11, 12, 13};
const uint8_t coluna_pins[] = {20, 4, 9, 8};
const uint8_t linha_pins[] = {16, 17, 18, 19};
const uint8_t buzzer_pin = 10;

void inicializar_pinos();
char verificar_tecla();
void ligar_todos_leds(uint32_t cor, float brilho, PIO pio, uint sm);

const char mapa_tecla[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int main()
{
    inicializar_pinos();
    stdio_init_all();
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, LED_PIN, 800000, false);

    while (true)
    {

        char tecla = verificar_tecla(); // Obtém a tecla pressionada
        //funcao de teste
       // if (stdio_usb_connected() && getchar_timeout_us(0) != PICO_ERROR_TIMEOUT)
        //{
        //    char tecla = getchar();

        // Utilizando switch para simplificar os casos
        switch (tecla)
        {
        case '0':
            sleep_ms(100);
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
            sleep_ms(100);
            break;
        case 'B':
            ligar_todos_leds(0x00FF00, 1.0, pio, sm); // Ligar Cor Azul 100%
            break;
        case 'C':
            ligar_todos_leds(0x0000FF, 0.8, pio, sm); // Ligar Cor Vermelho 80%
            break;
        case 'D':
            sleep_ms(100);
            break;
        case '#':
            sleep_ms(100); // Ação genérica para essas teclas
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
    return 0;
}

// Função para inicializar os pinos
void inicializar_pinos()
{

    for (int i = 0; i < linhas; i++)
    {
        gpio_init(linha_pins[i]);
        gpio_set_dir(linha_pins[i], GPIO_OUT);
        gpio_put(linha_pins[i], 0); // Inicialmente, todas as linhas devem estar em nível baixo
    }

    for (int j = 0; j < colunas; j++)
    {
        gpio_init(coluna_pins[j]);
        gpio_set_dir(coluna_pins[j], GPIO_IN);
        gpio_pull_down(coluna_pins[j]); // Ative o pull-down
    }

    // Inicializando os leds green, blue e red
    for (int i = 0; i < leds; i++)
    {
        gpio_init(led_pin[i]);
        gpio_set_dir(led_pin[i], GPIO_OUT);
    }
}

// Função para verificar qual tecla foi pressionada
char verificar_tecla()
{
    for (int i = 0; i < linhas; i++)
    {
        gpio_put(linha_pins[i], 1);
        /* O uso do sleep_us(200) fez o código funcionar porque ele permite tempo suficiente
        para estabilização dos sinais elétricos no teclado matricial.
        Isso está relacionado à forma como os sinais são gerados e lidos nos circuitos digitais. */
        sleep_us(200); // Pequeno atraso para estabilização
        for (int j = 0; j < colunas; j++)
        {
            /*        bool estado = gpio_get(coluna_pins[j]); */
            /*            printf("Linha %d, Coluna %d: %d\n", i, j, estado); */
            if (gpio_get(coluna_pins[j]))
            {
                printf("Tecla detectada em linha %d e coluna %d\n", i, j);
                gpio_put(linha_pins[i], 0);
                return mapa_tecla[i][j];
            }
        }
        gpio_put(linha_pins[i], 0);
    }
    return '\0'; // se nenhuma tecla for pressionada
}

//função para ligar todos os leds 5x5
void ligar_todos_leds(uint32_t cor, float brilho, PIO pio, uint sm)
{
    uint32_t adjusted_color = ((uint8_t)(((cor >> 16) & 0xFF) * brilho) << 16) |
                              ((uint8_t)(((cor >> 8) & 0xFF) * brilho) << 8) |
                              (uint8_t)((cor & 0xFF) * brilho);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        pio_sm_put_blocking(pio, sm, adjusted_color);
    }
}