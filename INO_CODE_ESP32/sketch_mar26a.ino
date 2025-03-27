#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Configurazione I2C su ESP32 (puoi cambiare SDA e SCL se necessario)
#define SDA_PIN 23  // Pin SDA su ESP32
#define SCL_PIN 22  // Pin SCL su ESP32

unsigned long previousMillis = 0;  // Tempo dell'ultima lettura
const long interval = 5000;         // Intervallo di 5 secondi (5000 ms)

void setup() {
  Serial.begin(9600);              // Inizializza la comunicazione seriale
  Wire.begin(SDA_PIN, SCL_PIN);    // Inizializza la comunicazione I2C con i pin definiti

  mpu.initialize();
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully.");
  } else {
    Serial.println("MPU6050 connection failed.");
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Verifica se sono passati 5 secondi
  if (currentMillis - previousMillis >= interval) {
    // Salva il tempo dell'ultima lettura
    previousMillis = currentMillis;

    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    
    // Invia solo l'angolo x per la rotazione del display
    int angle_x = map(ax, -17000, 17000, 0, 360);  // Scala l'asse X per ottenere un angolo (0-360 gradi)
    
    // Invia l'angolo X al PC
    Serial.println(angle_x);
  }
}
