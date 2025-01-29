#ifndef _buzzer_H
#define _buzzer_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

extern uint notas[];
extern uint notas2[];

void inicializa_buzzer_pwm(uint pin);
void toca_nota(uint pin, uint frequencia, uint duracao);

#endif