
# Ctrl-4All

## Descrição do Projeto

Este projeto visa melhorar a acessibilidade de pessoas com deficiência motora em jogos educativos como o Kahoot. O sistema consiste em um controle adaptado que detecta movimentos da cabeça (inclinações) e os traduz em comandos de teclado, simulando cliques em posições específicas da tela. O dispositivo é composto por um sensor MPU-6050 acoplado a uma tiara com um Arduino Pro Micro 5V, que se comunica com um computador para executar ações pré-definidas.

---

## Componentes Necessários

### Hardware

- Tiara  
- Acelerômetro e Giroscópio 3 Eixos (MPU-6050)  
- Placa Arduino Pro Micro 5V 

### Software

- Arduino IDE (para programação do Arduino)  
- AutoHotkey v2.0 (para mapeamento dos comandos no computador)  

---

## Funcionamento

### Hardware

- O sensor MPU-6050 detecta inclinações da cabeça em quatro direções (frente/trás, esquerda/direita).
- O Arduino envia comandos de teclado (F13–F16) conforme a direção detectada.
- O comando permanece ativo enquanto a inclinação for mantida e é interrompido quando a cabeça retorna à posição neutra.

### Software

- O script AutoHotkey mapeia os comandos F13–F16 para cliques do mouse em coordenadas específicas da tela, correspondendo às opções de resposta do Kahoot (A, B, C, D).

---

## Configuração do Projeto

### 1. Código Arduino

O código fornecido deve ser carregado no Arduino Pro Micro 5V. Certifique-se de:

- Conectar o sensor MPU-6050 corretamente ao Arduino.
- Calibrar a posição neutra do sensor durante a inicialização.
- Ajustar as zonas mortas (`xDeadzone` e `yDeadzone`) conforme necessário para evitar detecções acidentais.

## 2. Script AutoHotkey

Para telas de **1920x1080p**, providenciamos um [Script de exemplo](https://github.com/Marcelomenezes07/projeto-ctrl4all/blob/main/Script%20de%20exemplo.ahk):
O script AutoHotkey deve ser executado no computador. Substitua os *placeholders* (`coordX1`, `coordY1`, etc.) pelas coordenadas reais da tela onde estão as opções de resposta do Kahoot.

### Exemplo:

```ahk
#Requires AutoHotkey v2.0

CoordMode("Mouse", "Screen")  ; Garante que as coordenadas são absolutas da tela

; Clica em posições absolutas da tela quando F13–F16 são pressionadas

^F13:: {  ; X+
    MouseClick("left", coordX1, coordY1)
}

^F14:: {  ; X-
    MouseClick("left", coordX2, coordY2)
}

^F15:: {  ; Y+
    MouseClick("left", coordX3, coordY3)
}

^F16:: {  ; Y-
    MouseClick("left", coordX4, coordY4)
}
```

---

## Montagem e Uso

1. Monte o sensor MPU-6050 na tiara e conecte-o ao Arduino.  
2. Carregue o código no Arduino e conecte-o ao computador via USB.  
3. Execute o script AutoHotkey no computador.  
4. Incline a cabeça para selecionar as opções no Kahoot:

   - **Frente/Trás**: Alternativas A/B (ou outras, conforme configurado).  
   - **Esquerda/Direita**: Alternativas C/D (ou outras, conforme configurado).  

---

## Dependências

### Software Necessário
- [Arduino IDE 2.3.6 ou superior](https://www.arduino.cc/en/software)  
- [AutoHotkey v2.0 ou superior](https://www.autohotkey.com)

### Bibliotecas do Arduino
Todas estas bibliotecas estão incluídas por padrão na Arduino IDE:
- **Wire.h** – Para comunicação I2C com o sensor  
- **Keyboard.h** – Para emulação de teclado

Biblioteca adicional necessária:
1. [MPU6050_light.h](https://github.com/rfetick/MPU6050_light)  
   Biblioteca específica para o sensor MPU-6050. Instale via:
   - **Gerenciador de Bibliotecas:** (busque por `MPU6050_light`)
---

### Guia de Instalação

#### Instalação da Biblioteca MPU6050_light:

**Pelo Arduino IDE (Recomendado):**
1. Abra o Arduino IDE
2. Vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...**
3. Busque por `MPU6050_light` e clique em **Instalar**

---

## Equipe

**G13:**

- Arthur Sindeaux de Araújo Nogueira
- Estêvão Queiroz dos Santos  
- Igor Moura Nunes  
- Marcelo Asfora de Menezes  
- Marina de Queiróz Negromonte  
- Caio Leon Almeida Andrade Michalewicz  
- Humberto Mota de Lima    
- Maria Bertholine Rêgo Barros Simões  
- Rafael Chiappetta Barboza  

## Licença

Este projeto está licenciado sob a **Licença Apache 2.0**. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

### Direitos Autorais

Copyright 2025 **Arthur Sindeaux de Araújo Nogueira, Estêvão Queiroz dos Santos, Igor Moura Nunes, Marcelo Asfora de Menezes, Marina de Queiróz Negromonte, Caio Leon Almeida Andrade Michalewicz, Humberto Mota de Lima, Maria Bertholine Rêgo Barros Simões, Rafael Chiappetta Barboza**

Licenciado sob a Licença Apache, Versão 2.0 (a "Licença"); você não pode usar este arquivo, exceto em conformidade com a Licença. Você pode obter uma cópia da Licença em

    http://www.apache.org/licenses/LICENSE-2.0

A menos que exigido por lei aplicável ou acordado por escrito, o software distribuído sob a Licença é distribuído "NO ESTADO EM QUE SE ENCONTRA", SEM GARANTIAS OU CONDIÇÕES DE QUALQUER TIPO, expressas ou implícitas. Consulte a Licença para o idioma específico que rege permissões e limitações sob a Licença.
