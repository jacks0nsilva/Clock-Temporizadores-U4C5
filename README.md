# **Tarefa da Unidade 4 Capítulo 5 - Clock e Temporizadores**

Tarefa do programa EmbarcaTech. Este respositório possui duas atividades desenvolvidas para o microcontrolador Raspberry Pi Pico, utilizando a biblioteca pico SDK.

## **Atividades**

### **🛑 ATIVIDADE 1: Semáforo**

Simula um semáforo utilizando três LEDs (vermelho, amarelo e verde). Os LEDs alternam automaticamente a cada 3 segundos, uma mensagem correspondente ao estado do semáforo é exibida no terminal a cada 1 segundo.

#### 🔧 **Funcionamento**

1. O sistema inicia com o LED vermelho aceso.

2. Após 3 segundos o LED amarelo é aceso e os demais permanecem apagados.

3. Após mais 3 segundos o LED verde acende, enquanto os demais permanecem apagos.

4. O terminal exibe mensagens indicando o estado atual do semáforo:

   - Vermelho: "PARE! O sinal está fechado."

   - Amarelo: "ATENÇÃO! O sinal está amarelo."

   - Verde: "PROSSIGA! O sinal está verde."

5. O ciclo se repete.

#### **📦 Requisito de hardware**

- **Microcontrolador:** Raspberry Pi Pico W
- **LEDS Verde: GPIO 11 | Amarelo: GPIO 12 | Vermelho: GPIO 13**
- **3 Resistores de 330 Ω**

## **💡 ATIVIDADE 2: Acionamento de LEDs por Botão**

Controla três LEDs que acendem simultaneamente ao pressionar um botão e desligam um por um em intervalos de 3 segundos.

### **🔧 Funcionamento**

1. O sistema inicia com todos os LEDs apagados.
2. Quando o botão é pressionado, todos os LEDs acendem.
3. Após 3 segundos, o primeiro LED (verde) apaga.
4. Após mais 3 segundos, o segundo LED (azul) apaga.
5. Após mais 3 segundos, o último LED (vermelho) apaga.
6. O sistema retorna ao estado inicial, aguardando um novo acionamento do botão.
7. Mensagens informando o desligamento de cada LED são exibidas no terminal.

#### **📦 Requisitos de hardware**

- Microcontrolador: Raspberry Pi Pico W
- LEDS:
  - Verde: GPIO 11
  - Azul: GPIO 12
  - Vermelho: GPIO 13
- Botão pushbutton: GPIO 5
- 3 Resistores de 330 Ω

## Conclusão

Ambas as atividades foram desenvolvidas utilizando os temporizadores disponíveis no SDK da Raspberry Pi Pico para controlar o acionamento e desligamento dos LEDs de forma automatizada.

Na Atividade 1, um **temporizador periódico** alterna os LEDs a cada 3 segundos, simulando um semáforo.

Na Atividade 2, um **temporizador único** é acionado após o pressionamento de um botão para desligar os LEDs de forma sequencial, com intervalos de 3 segundos entre cada desligamento.

Essas implementações demonstram o uso eficiente dos **timers** para controlar eventos no Raspberry Pi Pico sem a necessidade de loops bloqueantes. 🚀

## Como compilar e executar o projeto

1. Clone o repositório:

```bash
git clone https://github.com/jacks0nsilva/Clock-Temporizadores-U4C5.git
```

2. Instale a extensão **Raspberry Pi Pico** no VS Code.

3. Abra a extensão, clique em **\*Import Project** e selecione a pasta do projeto.

4. Clique em Clean Cmake para garantir que o projeto será compilado do zero.

5. Clique em **Compile Project** para compilar o código.

6. Conecte o Raspberry Pi Pico à porta USB do computador.

7. Após colocar o Raspberry Pi Pico no modo **Bootsel**, clique em **Run Project** para gravar o código no microcontrolador.

## Simulação no Wokwi

Você pode simular o projeto no Wokwi, basta compilar o código e acessar o arquivo diagram.json **Obs: É necessário utilizar a extensão do Wokwi no VsCode.**
