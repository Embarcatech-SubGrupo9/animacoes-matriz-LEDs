#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/watchdog.h"

// Constantes
const int colunas = 4;
const int linhas = 4;
const int leds = 3;

const uint8_t led_pin[] = {11, 12, 13};
const uint8_t coluna_pins[] = {20, 4, 9, 8};
const uint8_t linha_pins[] = {16, 17, 18, 19};
const uint8_t buzzer_pin = 10;

void reboot_sistema();
char verificar_tecla();

const char mapa_tecla[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int main()
{
    stdio_init_all();

    while (true)
    {

        char tecla = verificar_tecla(); // Obtém a tecla pressionada

        if (tecla != '\0') // Verifica se uma tecla foi pressionada
        {
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
                sleep_ms(100);
                break;
            case 'C':
                sleep_ms(100);
                break;
            case 'D':
                sleep_ms(100);
                break;
            case '#':
                sleep_ms(100); // Ação genérica para essas teclas
                break;
            case '*':
                reboot_sistema(); // Reinicia o sistema para a tecla '*'
                sleep_ms(100);
                break;

            default:
                sleep_ms(100);
                break;
            }
        }
        sleep_ms(100);
    }
}

// Função para verificar qual tecla foi pressionada
char verificar_tecla()
{
    for (int i = 0; i < linhas; i++)
    {
        gpio_put(linha_pins[i], 1);
        for (int j = 0; j < colunas; j++)
        {
            if (gpio_get(coluna_pins[j]))
            {
                gpio_put(linha_pins[i], 0);
                return mapa_tecla[i][j];
            }
        }
        gpio_put(linha_pins[i], 0);
    }
    return '\0'; // Retorna '\0' se nenhuma tecla for pressionada
}

// Função para reiniciar o sistema
void reboot_sistema()
{
    reset_usb_boot(0, 0);
}
