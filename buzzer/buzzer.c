#include "buzzer.h"

// Notas iniciais da música tema de Star Wars
const uint notas[] = {
    330, 330, 330, 262, 392
};

// Inicializa o PWM no pino do buzzer
void inicializa_buzzer_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint faixa = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 2.0f); // Ajusta divisor de clock
    pwm_init(faixa, &config, true);
    pwm_set_gpio_level(pin, 0); // Desliga o PWM inicialmente
}

// Toca uma nota com a frequência e duração especificadas
void toca_nota(uint pin, uint frequencia, uint duracao) {
    uint faixa = pwm_gpio_to_slice_num(pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t top = clock_freq / frequencia - 1;

    pwm_set_wrap(faixa, top);
    pwm_set_gpio_level(pin, top / 2); // 50% de duty cycle

    sleep_ms(duracao);

    pwm_set_gpio_level(pin, 0); // Desliga o som após a duração
}