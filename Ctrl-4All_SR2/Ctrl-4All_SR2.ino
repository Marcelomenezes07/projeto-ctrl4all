#include <Wire.h>          // Biblioteca I2C integrada
#include <MPU6050_light.h> // Biblioteca do acelerômetro/giroscópio: https://github.com/rfetick/MPU6050_light
#include <Keyboard.h>      // Biblioteca para simular teclado (Arduino Leonardo ou similar)

MPU6050 mpu(Wire); // Cria o objeto do sensor MPU usando comunicação I2C

// === VARIÁVEIS CONFIGURÁVEIS ===
const int updateRate = 50;  // Tempo entre atualizações (ms)

const float xDeadzone = 25.0; // Zona morta para o eixo X (evita pequenos ruídos)

bool estadoDEBUG; // Armazena se o jumper está conectado (ativo) ou não (modo teste/debug)
int pinoJumperDEBUG = 8; // Pino conectado a um jumper físico para ativar/desativar o modo DEBUG

// Combinações de teclas (modificáveis conforme necessidade)
// Combinações de teclas (movimentos):
const uint8_t keysXPositive[] = {KEY_LEFT_ARROW}; // "X+"
const uint8_t keysXNegative[] = {KEY_RIGHT_ARROW}; // "X-"

// Flags para evitar múltiplos pressionamentos da mesma direção
bool xPosActive = false, xNegActive;
// ==============================

unsigned long timer = 0; // Temporizador para controlar frequência de atualização

// Função auxiliar para pressionar várias teclas ao mesmo tempo
void pressCombo(const uint8_t* keys, size_t length) {
  for (size_t i = 0; i < length; i++) {
    Keyboard.press(keys[i]);
  }
}

// Função auxiliar para soltar várias teclas ao mesmo tempo
void releaseCombo(const uint8_t* keys, size_t length) {
  for (size_t i = 0; i < length; i++) {
    Keyboard.release(keys[i]);
  }
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Keyboard.begin();

  // Inicializa o sensor e tenta novamente até conseguir conexão
  byte status = mpu.begin();
  while (status != 0) {
    Serial.println("MPU6050 connection failed, retrying...");
    delay(1000);
    status = mpu.begin();
  }

  mpu.calcOffsets(); // Calibra o sensor

  // Descomente se o sensor estiver montado de cabeça pra baixo
  // mpu.upsideDownMounting = true;

  pinMode(pinoJumperDEBUG, INPUT_PULLUP); // Jumper com pull-up interno ativado
}

void loop() {
  estadoDEBUG = digitalRead(pinoJumperDEBUG);

  if (estadoDEBUG == HIGH) {
    // DEBUG ATIVO — solta todas as teclas e reseta os estados ativos
    releaseCombo(keysXPositive, sizeof(keysXPositive));
    releaseCombo(keysXNegative, sizeof(keysXNegative));

    xPosActive = false;
    xNegActive = false;
  }

  if (estadoDEBUG == LOW) {
    mpu.update();

    // Só executa após o tempo de atualização definido
    if ((millis() - timer) > updateRate) {
      float x = mpu.getAngleX();

      // --- DETECÇÃO EIXO X ---
      if (x > xDeadzone && !xPosActive) { // X+
        // sizeof(keysXPositive) funciona aqui pois cada tecla tem 1 byte (uint8_t)
        // Em vetores de tipos maiores, use: sizeof(keysXPositive) / sizeof(keysXPositive[0])
        pressCombo(keysXPositive, sizeof(keysXPositive));
        xPosActive = true;
	releaseCombo(keysXPositive, sizeof(keysXPositive));
      } else if (x <= xDeadzone && xPosActive) {
        xPosActive = false;
      }

      if (x < -xDeadzone && !xNegActive) { // X-
        pressCombo(keysXNegative, sizeof(keysXNegative));
        xNegActive = true;
	releaseCombo(keysXNegative, sizeof(keysXNegative));
      } else if (x >= -xDeadzone && xNegActive) {
        xNegActive = false;
      }

      timer = millis(); // Atualiza temporizador
    }
  }
}
