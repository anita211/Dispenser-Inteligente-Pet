# Dispenser Inteligente de Ração MSP430

Um projeto final para sistemas microprocessados que implementa um dispenser automático de ração para pets. Este sistema utiliza a microcontroladora MSP430 da Texas Instruments, integrando sensor de movimento, LCD e botões para controle de modos, garantindo que o pet receba sua ração de forma controlada (com intervalos de 1 minuto, para evitar a alimentação excessiva).

## Funcionalidades

- **Sensor de Movimento:** Detecta a presença do pet para acionar o dispenser.
- **Controle do Motor:** Libera a ração de forma automatizada, respeitando um intervalo mínimo de 1 minuto entre ativações.
- **Interface LCD:** Exibe informações e status do sistema.
- **Botões de Controle:** Permitem a seleção de diferentes modos de operação.

## Hardware Utilizado

- **MSP430 (Texas Instruments):** Microcontrolador responsável pelo processamento.
- **Sensor de Movimento:** Para detectar a presença do pet.
- **LCD:** Para exibição de informações.
- **Motor:** Para liberação da ração.
- **Botões:** Para controle e seleção dos modos de operação.

## Configuração e Instalação

1. **Clone o Repositório:**

   ```bash
   git clone https://github.com/seu-usuario/Dispenser-Inteligente-de-Racao-MSP430.git

2. **Configuração do Ambiente**:

- Instale o Code Composer Studio (CCS) para desenvolver e compilar o projeto.
- Configure o ambiente de acordo com as instruções da TI para a MSP430.

3. **Compilação e Upload**:

- Abra o projeto no CCS.
- Compile o projeto.
- Faça o upload para a MSP430 conforme as orientações da documentação do seu kit de desenvolvimento.

## Uso do Projeto
Após a instalação:

1. **Início Automático**: O sistema inicia e aguarda a detecção de movimento após 1 minuto. ALternativamente, é possível ativar a liberação através dos botões e do LCD.
2. **Ativação**: Ao detectar movimento, o motor é acionado para liberar a ração, respeitando o intervalo mínimo de 1 minuto entre ativações.
3. **Modos de Operação**: Utilize os botões para alternar entre os modos de funcionamento e visualize os status no LCD.
