#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Inicializa o MPU6050
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 conectado com sucesso!");
  } else {
    Serial.println("Erro ao conectar com o MPU6050.");
    while (1); // Travar se falhar
  }
}

void loop() {
  int16_t ax, ay, az;
  
  // Obtém os valores de aceleração
  mpu.getAcceleration(&ax, &ay, &az);

  // Normaliza os valores (g = 16384)
  float x = ax / 16384.0;
  float y = ay / 16384.0;

  // Determina o movimento com base na inclinação
  if (x > 0.5) {
    Serial.println("Movendo para a DIREITA");
  } else if (x < -0.5) {
    Serial.println("Movendo para a ESQUERDA");
  } else if (y > 0.5) {
    Serial.println("Inclinado para FRENTE");
  } else if (y < -0.5) {
    Serial.println("Inclinado para TRÁS");
  } else {
    Serial.println("Em repouso ou estável");
  }

  delay(500); // Aguarda meio segundo entre as leituras
}
