#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/watchdog.h"

#include "teclado/tecladoMatricial.h"

// Controlar leds 5x5
#include "hardware/pio.h"
#include "ws2818b.pio.h"

// Constantes
#define LED_PIN 7
#define NUM_LEDS 25

const uint8_t buzzer_pin = 10;

//Primeira animação, preenchimento.
double animacao01_frame01 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

double animacao01_frame02 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

double animacao01_frame03 [NUM_LEDS] = { 0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0};

double animacao01_frame04 [NUM_LEDS] = { 0.0, 1.0, 1.0, 1.0, 0.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0};

double animacao01_frame05 [NUM_LEDS] = { 1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0};

//Segunda animação pessoa se mexendo.
double animacao02_frame01 [NUM_LEDS] = { 0.0, 1.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         1.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 1.0};

double animacao02_frame02 [NUM_LEDS] = { 0.0, 1.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0};

double animacao02_frame03 [NUM_LEDS] = { 0.0, 1.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 1.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0,
                                         1.0, 0.0, 1.0, 0.0, 0.0};

double animacao02_frame04 [NUM_LEDS] = { 0.0, 1.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0};

double animacao02_frame05 [NUM_LEDS] = { 0.0, 1.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         1.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 1.0, 1.0, 1.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 1.0};

//Terceira animação, farol.
double animacao03_frame01 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         1.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 1.0,
                                         1.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

double animacao03_frame02 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 1.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 1.0, 0.0,
                                         0.0, 1.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

double animacao03_frame03 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 1.0, 0.0,
                                         0.0, 1.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 1.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

double animacao03_frame04 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 1.0,
                                         1.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 1.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

double animacao03_frame05 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                         1.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 1.0,
                                         0.0, 0.0, 0.0, 0.0, 0.0};

//Quarta animação, ícone de carregamento.
double animacao04_frame01 [NUM_LEDS] = { 1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 1.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0};

double animacao04_frame02 [NUM_LEDS] = { 1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0};

double animacao04_frame03 [NUM_LEDS] = { 1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 0.0, 0.0, 1.0, 1.0,
                                         1.0, 0.0, 1.0, 0.0, 1.0,
                                         1.0, 1.0, 0.0, 0.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0};

double animacao04_frame04 [NUM_LEDS] = { 1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 0.0, 1.0, 0.0, 1.0,
                                         1.0, 0.0, 1.0, 0.0, 1.0,
                                         1.0, 0.0, 1.0, 0.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0};

double animacao04_frame05 [NUM_LEDS] = { 1.0, 1.0, 1.0, 1.0, 1.0,
                                         1.0, 1.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 1.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 1.0, 1.0,
                                         1.0, 1.0, 1.0, 1.0, 1.0};

//Quinta animação, barras coloridas.
double animacao05_frame01 [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 1.0};

double animacao05_frame02 [NUM_LEDS] = { 0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0, 0.0};

double animacao05_frame03 [NUM_LEDS] = { 1.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 0.0, 1.0,
                                         1.0, 0.0, 0.0, 0.0, 0.0};

double animacao05_frame04 [NUM_LEDS] = { 0.0, 0.0, 0.0, 1.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 0.0};

double animacao05_frame05 [NUM_LEDS] = { 0.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0, 0.0};

//Frame para apagar os led.
double frame_branco [NUM_LEDS] = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                   0.0, 0.0, 0.0, 0.0, 0.0,
                                   0.0, 0.0, 0.0, 0.0, 0.0,
                                   0.0, 0.0, 0.0, 0.0, 0.0,
                                   0.0, 0.0, 0.0, 0.0, 0.0};

void inicializar_pinos();
char verificar_tecla();
void ligar_todos_leds(uint8_t r, uint8_t g, uint8_t b, float brilho, PIO pio, uint sm);
void apagar_led(double *frame, PIO pio, uint sm);
void animacaoRBG(double *frame, PIO pio, uint sm, uint8_t red, uint8_t green, uint8_t blue);
void selececao_animacao(uint8_t escolha, PIO pio, uint sm);

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
                sleep_ms(100);
                break;
            case '1':
                selececao_animacao(1, pio, sm);
                sleep_ms(100);
                break;
            case '2':
                selececao_animacao(2, pio, sm);
                sleep_ms(100);
                break;
            case '3':
                selececao_animacao(3, pio, sm);
                sleep_ms(100);
                break;
            case '4':
                selececao_animacao(4, pio, sm);
                sleep_ms(100);
                break;
            case '5':
                selececao_animacao(5, pio, sm);
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
                ligar_todos_leds(255, 0, 0, 0.8, pio, sm); // Ligar Cor Vermelho 80%
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

//Função responsável por desligar todos os leds da matriz.
void apagar_led(double *frame, PIO pio, uint sm){
    for(uint8_t i = 0; i < NUM_LEDS; i++){
        uint8_t intensidade = (uint8_t) (frame[i] * 255);
        pio_sm_put_blocking(pio, sm, intensidade);
        pio_sm_put_blocking(pio, sm, intensidade);
        pio_sm_put_blocking(pio, sm, intensidade);
    }
}

//Função responsável por acionar os leds da matriz.
void animacaoRBG(double *frame, PIO pio, uint sm, uint8_t red, uint8_t green, uint8_t blue){
    for(uint8_t i = 0; i < NUM_LEDS; i++){
        uint8_t BLUE = 0, RED = 0, GREEN = 0;

        BLUE = (uint8_t) (blue * frame[i]);
        RED = (uint8_t) (red * frame[i]);
        GREEN = (uint8_t) (green * frame[i]);

        pio_sm_put_blocking(pio, sm, GREEN);
        pio_sm_put_blocking(pio, sm, RED);
        pio_sm_put_blocking(pio, sm, BLUE);
    }
}

//Função que controla qual animação será executada.
void selececao_animacao(uint8_t escolha, PIO pio, uint sm){
    if(escolha == 1){
        for(uint8_t i = 0; i < 3; i++){
            animacaoRBG(animacao01_frame01, pio, sm, 0, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao01_frame02, pio, sm, 0, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao01_frame03, pio, sm, 0, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao01_frame04, pio, sm, 0, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao01_frame05, pio, sm, 255, 0, 0);
            sleep_ms(500);
            apagar_led(frame_branco, pio, sm);
            sleep_ms(500);
        }
    }
    else if(escolha == 2){
        for(uint8_t i = 0; i < 3; i++){
            animacaoRBG(animacao02_frame01, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao02_frame02, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao02_frame03, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao02_frame04, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao02_frame05, pio, sm, 255, 255, 0);
            sleep_ms(500);
            apagar_led(frame_branco, pio, sm);
            sleep_ms(500);
        }
    }
    else if(escolha == 3){
        for(uint8_t i = 0; i < 3; i++){
            animacaoRBG(animacao03_frame01, pio, sm, 255, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao03_frame02, pio, sm, 255, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao03_frame03, pio, sm, 255, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao03_frame04, pio, sm, 255, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao03_frame05, pio, sm, 255, 255, 0);
            sleep_ms(500);
        }
        apagar_led(frame_branco, pio, sm);
        sleep_ms(500);
    }
    else if(escolha == 4){
        for(uint8_t i = 0; i < 3; i++){
            animacaoRBG(animacao04_frame01, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao04_frame02, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao04_frame03, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao04_frame04, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao04_frame05, pio, sm, 255, 0, 0);
            sleep_ms(500);
        }
        apagar_led(frame_branco, pio, sm);
        sleep_ms(500);
    }
    else if(escolha == 5){
        for(uint8_t i = 0; i < 3; i++){
            animacaoRBG(animacao05_frame01, pio, sm, 255, 0, 0);
            sleep_ms(500);
            animacaoRBG(animacao05_frame02, pio, sm, 255, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao05_frame03, pio, sm, 0, 255, 0);
            sleep_ms(500);
            animacaoRBG(animacao05_frame04, pio, sm, 0, 0, 255);
            sleep_ms(500);
            animacaoRBG(animacao05_frame05, pio, sm, 255, 255, 255);
            sleep_ms(500);
        }
        apagar_led(frame_branco, pio, sm);
        sleep_ms(500);
    }
}