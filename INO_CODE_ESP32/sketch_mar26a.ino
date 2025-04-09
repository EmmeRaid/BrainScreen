#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;

#define SDA_PIN 22
#define SCL_PIN 23

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully.");
  } else {
    Serial.println("MPU6050 connection failed.");
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);

    // Calcolo dell'angolo nel piano X-Y
    float angle_rad = atan2((float)ay, (float)ax);
    float angle_deg = angle_rad * 180.0 / PI;

    // Normalizza l'angolo in range 0-360
    if (angle_deg < 0) {
      angle_deg += 360;
    }

    Serial.println((int)angle_deg);  // Cast per avere un valore intero
  }
}
