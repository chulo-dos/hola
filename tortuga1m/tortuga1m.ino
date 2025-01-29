#include <Arduino.h>

// Pines del ESP32 conectados a dos módulos ULN2003 para dos motores
// Primer motor (gira a la derecha)
const int IN1_1 = 16;  // GPIO16 del ESP32
const int IN2_1 = 17;  // GPIO17 del ESP32
const int IN3_1 = 18;  // GPIO18 del ESP32
const int IN4_1 = 19;  // GPIO19 del ESP32

// Segundo motor (gira a la izquierda)
const int IN1_2 = 22;  // GPIO22 del ESP32
const int IN2_2 = 23;  // GPIO23 del ESP32
const int IN3_2 = 21;  // GPIO21 del ESP32
const int IN4_2 = 5;   // GPIO5 del ESP32

// Configuración del delay entre pasos para la máxima velocidad (en microsegundos)
const int STEP_DELAY = 2000; // Esto es el tiempo de espera entre pasos, 2000 microsegundos

// Secuencia de pasos para el motor 28BYJ-48 (Sentido horario - derecha)
int steps[8][4] = {
    {1, 0, 0, 0}, // Paso 1
    {1, 1, 0, 0}, // Paso 2
    {0, 1, 0, 0}, // Paso 3
    {0, 1, 1, 0}, // Paso 4
    {0, 0, 1, 0}, // Paso 5
    {0, 0, 1, 1}, // Paso 6
    {0, 0, 0, 1}, // Paso 7
    {1, 0, 0, 1}  // Paso 8
};

// Secuencia inversa de pasos para el motor 2 (Sentido antihorario - izquierda)
int stepsReverse[8][4] = {
    {1, 0, 0, 1}, // Paso 1
    {0, 0, 0, 1}, // Paso 2
    {0, 0, 1, 1}, // Paso 3
    {0, 0, 1, 0}, // Paso 4
    {0, 1, 1, 0}, // Paso 5
    {0, 1, 0, 0}, // Paso 6
    {1, 1, 0, 0}, // Paso 7
    {1, 0, 0, 0}  // Paso 8
};

void setup() {
    // Configurar pines como salida para ambos motores
    pinMode(IN1_1, OUTPUT);
    pinMode(IN2_1, OUTPUT);
    pinMode(IN3_1, OUTPUT);
    pinMode(IN4_1, OUTPUT);
    
    pinMode(IN1_2, OUTPUT);
    pinMode(IN2_2, OUTPUT);
    pinMode(IN3_2, OUTPUT);
    pinMode(IN4_2, OUTPUT);

    // Inicializar todos los pines en bajo
    digitalWrite(IN1_1, LOW);
    digitalWrite(IN2_1, LOW);
    digitalWrite(IN3_1, LOW);
    digitalWrite(IN4_1, LOW);

    digitalWrite(IN1_2, LOW);
    digitalWrite(IN2_2, LOW);
    digitalWrite(IN3_2, LOW);
    digitalWrite(IN4_2, LOW);

    // Comunicación Serial
    Serial.begin(9600);
}

void loop() {
    // Hacer que el primer motor gire en sentido horario (derecha)
    for (int i = 0; i < 8; i++) {
        setStep(IN1_1, IN2_1, IN3_1, IN4_1, steps[i][0], steps[i][1], steps[i][2], steps[i][3]);
        delayMicroseconds(STEP_DELAY); // Paso rápido (ajustado a la velocidad máxima)
    }

    // Hacer que el segundo motor gire en sentido antihorario (izquierda)
    for (int i = 0; i < 8; i++) {
        setStep(IN1_2, IN2_2, IN3_2, IN4_2, stepsReverse[i][0], stepsReverse[i][1], stepsReverse[i][2], stepsReverse[i][3]);
        delayMicroseconds(STEP_DELAY); // Paso rápido (ajustado a la velocidad máxima)
    }

    // Imprimir el estado
    Serial.println("Motores girando a máxima velocidad...");
}

// Función para establecer los pines del motor
void setStep(int IN1, int IN2, int IN3, int IN4, int a, int b, int c, int d) {
    digitalWrite(IN1, a);
    digitalWrite(IN2, b);
    digitalWrite(IN3, c);
    digitalWrite(IN4, d);
}
