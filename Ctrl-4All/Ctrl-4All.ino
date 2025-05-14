#include <Wire.h>          // Built-in library
#include <MPU6050_light.h> // From: https://github.com/rfetick/MPU6050_light
#include <Keyboard.h>      // Built-in library

MPU6050 mpu(Wire);

// === CONFIGURABLE VARIABLES ===
const int updateRate = 50;  // milliseconds between updates

const float xDeadzone = 20.0;
const float yDeadzone = 20.0;

bool estadoDEBUG;
int pinoJumperDEBUG = 8;

// Key combinations (you can change these)
const uint8_t keysXPositive[] = { KEY_LEFT_CTRL, KEY_F13 }; // X+
const uint8_t keysXNegative[] = { KEY_LEFT_CTRL, KEY_F14 }; // X-
const uint8_t keysYPositive[] = { KEY_LEFT_CTRL, KEY_F15 }; // Y+
const uint8_t keysYNegative[] = { KEY_LEFT_CTRL, KEY_F16 }; // Y-

bool xPosActive = false, xNegActive = false, yPosActive = false, yNegActive = false;
// ==============================

unsigned long timer = 0;

// Helper function to press multiple keys simultaneously
// Useful for triggering key combinations like Ctrl+Arrow
void pressCombo(const uint8_t* keys, size_t length) {
  for (size_t i = 0; i < length; i++) {
    Keyboard.press(keys[i]);
  }
}

// Helper function to release multiple keys simultaneously
// Complements pressCombo by ensuring all keys in the combo are released
void releaseCombo(const uint8_t* keys, size_t length) {
  for (size_t i = 0; i < length; i++) {
    Keyboard.release(keys[i]);
  }
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Keyboard.begin();

  byte status = mpu.begin();
  while (status != 0) {
    Serial.println("MPU6050 connection failed, retrying...");
    delay(1000);
    status = mpu.begin();
  }

  mpu.calcOffsets(); // Calibrate sensor
  
  // Uncomment the following line if the MPU6050 is mounted upside down
  // mpu.upsideDownMounting = true;
  pinMode(pinoJumperDEBUG, INPUT_PULLUP);
}

void loop() {
  estadoDEBUG = digitalRead(pinoJumperDEBUG);
  if (estadoDEBUG == HIGH) {
    releaseCombo(keysXPositive, sizeof(keysXPositive));
    releaseCombo(keysYPositive, sizeof(keysYPositive));
    releaseCombo(keysXNegative, sizeof(keysXNegative));
    releaseCombo(keysYNegative, sizeof(keysYPositive));
  }
  if (estadoDEBUG == LOW) {
    mpu.update();
    if ((millis() - timer) > updateRate) {
      float x = mpu.getAngleX();
      float y = mpu.getAngleY();

      // X+
      if (x > xDeadzone && !xPosActive) {
        pressCombo(keysXPositive, sizeof(keysXPositive));
        xPosActive = true;
      } else if (x <= xDeadzone && xPosActive) {
        releaseCombo(keysXPositive, sizeof(keysXPositive));
        xPosActive = false;
      }

      // X-
      if (x < -xDeadzone && !xNegActive) {
        pressCombo(keysXNegative, sizeof(keysXNegative));
        xNegActive = true;
      } else if (x >= -xDeadzone && xNegActive) {
        releaseCombo(keysXNegative, sizeof(keysXNegative));
        xNegActive = false;
      }

      // Y+
      if (y > yDeadzone && !yPosActive) {
        pressCombo(keysYPositive, sizeof(keysYPositive));
        yPosActive = true;
      } else if (y <= yDeadzone && yPosActive) {
        releaseCombo(keysYPositive, sizeof(keysYPositive));
        yPosActive = false;
      }

      // Y-
      if (y < -yDeadzone && !yNegActive) {
        pressCombo(keysYNegative, sizeof(keysYNegative));
        yNegActive = true;
      } else if (y >= -yDeadzone && yNegActive) {
        releaseCombo(keysYNegative, sizeof(keysYNegative));
        yNegActive = false;
      }

      timer = millis();
    }
  }
}
