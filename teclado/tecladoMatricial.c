#include "tecladoMatricial.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define colunas 4
#define linhas 4

const uint8_t coluna_pins[] = {20, 4, 9, 8};
const uint8_t linha_pins[] = {16, 17, 18, 19};

static const char mapa_tecla[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Função para inicializar os pinos
void inicializar_pinos()
{
    for (int i = 0; i < linhas; i++)
    {
        gpio_init(linha_pins[i]);
        gpio_set_dir(linha_pins[i], GPIO_IN); // Linhas como entrada
        gpio_pull_down(linha_pins[i]);        // Ativa o pull-down
    }

    for (int j = 0; j < colunas; j++)
    {
        gpio_init(coluna_pins[j]);
        gpio_set_dir(coluna_pins[j], GPIO_OUT); // Colunas como saída
        gpio_put(coluna_pins[j], 0);            // Inicialmente, todas as colunas devem estar em nível baixo
    }
}

/* char verificar_tecla()
{
    // Itera sobre todas as linhas
    for (int i = 0; i < linhas; i++)
    {
        // Ativa apenas a linha atual
        gpio_put(linha_pins[i], 1);
        sleep_us(200); // Atraso para estabilização

        // Itera sobre todas as colunas para verificar se há tecla pressionada
        for (int j = 0; j < colunas; j++)
        {
            if (gpio_get(coluna_pins[j]))
            {
                printf("Tecla detectada em linha %d e coluna %d\n", i, j);

                // Desativa a linha antes de retornar o caractere correspondente
                gpio_put(linha_pins[i], 0);
                return mapa_tecla[i][j];
            }
        }

        // Desativa a linha após verificar todas as colunas
        gpio_put(linha_pins[i], 0);
    }

    // Retorna '\0' caso nenhuma tecla tenha sido pressionada
    return '\0';
} */
/*
// Função para verificar qual tecla foi pressionada
char verificar_tecla()
{
    // Reseta todas as colunas
    for (int i = 0; i < 4; i++)
    {
        gpio_put(coluna_pins[i], 1);
    }

    for (int coluna = 0; coluna < 4; coluna++)
    {
        gpio_put(coluna_pins[coluna], 0); // Ativa a coluna atual

        for (int linha = 0; linha < 4; linha++)
        {
            if (gpio_get(linha_pins[linha]) == 0)
            {                                     // Detecta pressão na linha
                gpio_put(coluna_pins[coluna], 1); // Desativa a coluna atual
                return mapa_tecla[linha][coluna]; // Retorna imediatamente
            }
        }

        gpio_put(coluna_pins[coluna], 1); // Desativa a coluna atual
    }

    return '\0'; // Nenhuma tecla pressionada
} */

// Aguarda até que todas as teclas sejam soltas
void aguardar_solta()
{
    while (1)
    {
        bool tecla_pressionada = false;

        // Verifica se há alguma tecla pressionada
        for (int linha = 0; linha < linhas; linha++)
        {
            if (gpio_get(linha_pins[linha]))
            {
                tecla_pressionada = true;
                break;
            }
        }

        if (!tecla_pressionada)
            break;

        sleep_ms(20); // Debounce
    }
}

// Função para verificar qual tecla foi pressionada
char verificar_tecla()
{
    for (int coluna = 0; coluna < colunas; coluna++)
    {
        // Garante que todas as colunas estão em nível baixo antes de ativar uma.
        for (int i = 0; i < colunas; i++)
        {
            gpio_put(coluna_pins[i], 0);
        }

        gpio_put(coluna_pins[coluna], 1); // Ativa apenas a coluna atual
        sleep_us(200);                    // Pequeno atraso para estabilizar

        for (int linha = 0; linha < linhas; linha++)
        {
            if (gpio_get(linha_pins[linha]))
            {
                sleep_ms(20); // Debounce

                if (gpio_get(linha_pins[linha]))
                { // Confirma a tecla pressionada
                    char tecla = mapa_tecla[linha][coluna];

                    // Garante que as colunas sejam resetadas antes de retornar
                    gpio_put(coluna_pins[coluna], 0);
                    aguardar_solta(); // Aguarda a tecla ser solta
                    return tecla;
                }
            }
        }

        gpio_put(coluna_pins[coluna], 0); // Desativa a coluna atual
    }

    return '\0'; // Nenhuma tecla pressionada
}