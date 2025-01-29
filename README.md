# animacoes-matriz-LEDs

Geração de animações em uma matriz de LEDs 5x5 utilizando Raspberry Pi Pico W.

## 📄 Descrição

Este projeto visa gerar animações em uma matriz de LEDs WS2812 5x5 com o auxílio de um teclado matricial 4x4 e Raspberry Pi Pico W. As animações são acionadas através das teclas de 0 a 9, enquanto teclas como A, B, C, D, e # controlam as cores da matriz. O projeto também integra um buzzer opcional para efeitos sonoros.

## 🔌 Conexões de Hardware

### Esquema de Conexões
| Componente                             | Pino do Pico |
|----------------------------------------|--------------|
| Dados LEDs WS2812                      | GP7          |
| Linha 1 do teclado                     | GP9          |
| Linha 2 do teclado                     | GP8          |
| Linha 3 do teclado                     | GP4          |
| Linha 4 do teclado                     | GP20         |
| Coluna 1 do teclado                    | GP19         |
| Coluna 2 do teclado                    | GP18         |
| Coluna 3 do teclado                    | GP17         |
| Coluna 4 do teclado                    | GP16         |

## 👥 Equipe de Desenvolvimento

- **Líder**: *Fernando Hali Santos Andrade*  
  Responsável por: Teclado matricial, documentação e vídeos.

- **Desenvolvedor**: *Leandro Alves dos Santos*  
  Responsável por: Implementação das animações das teclas A, B, C e D com as intensidades especificadas.

- **Desenvolvedor**: *Heli Neres Silva*  
  Responsável por: Implementação das animações associadas às teclas '8' e '9' com efeito de buzzer.

- **Desenvolvedor**: *Gabriel Adriano de Jesus Reis*  
  Responsável por: Animações para as teclas 6 e 7.

- **Desenvolvedor**: *Luis Eduardo F. S. Pereira*  
  Responsável por: Animações para as teclas 1, 2, 3, 5, 4 e 0.

## 🔧 Requisitos

- **Teclado Matricial 4x4**: Para acionar as animações.
- **Raspberry Pi Pico W**: Microcontrolador utilizado.
- **Matriz de LEDs 5x5 WS2812**: Para exibição das animações.
- **Buzzer Passivo Eletromagnético MLT-8530 SMD** (opcional).

## ⚙️ Funcionalidades

- Teclas de 0 a 9: Cada tecla ativa uma animação específica.
- Tecla A: Desliga todos os LEDs.
- Tecla B: Liga todos os LEDs na cor azul (100% intensidade).
- Tecla C: Liga todos os LEDs na cor vermelha (80% intensidade).
- Tecla D: Liga todos os LEDs na cor verde (50% intensidade).
- Tecla #: Liga todos os LEDs na cor branca (20% intensidade).
- Tecla *: Habilita o modo de gravação via software (reboot).

### Requisitos para animações:
- Mínimo de 5 frames por animação.
- Definir FPS (quadros por segundo).

## 💻 Como Usar

1. Conecte os componentes de acordo com as especificações de pinos.
2. Carregue o código no Raspberry Pi Pico W.
3. Interaja com o teclado matricial para gerar animações.
4. (Opcional) Acione o buzzer para um efeito sonoro nas animações.

## 🛠️ Instalação e Execução

1. Clone o repositório:
   ```bash
   git clone https://github.com/Embarcatech-SubGrupo9/animacoes-matriz-LEDs
   ```

2. Instale as dependências necessárias (caso haja alguma dependência, como bibliotecas específicas).

3. Carregue o código no Raspberry Pi Pico W.

4. Execute o projeto com:
   ```bash
   animacoes-matriz-LEDs.c
   ```

   ### Link para o vídeo:

[Apresentação do Projeto](https://www.dropbox.com/scl/fi/4l90wj1f2qzk3ncintjkx/video_2025-01-28_23-24-17.mp4?rlkey=rpsj8l56v9lyy8bkshf19pxdz&st=f0hsnnak&dl=0)

