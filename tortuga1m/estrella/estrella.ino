#include <Arduino.h>

// Pines del ESP32 conectados a dos módulos ULN2003 para dos motores
const int IN1_1 = 16; // GPIO16 del ESP32
const int IN2_1 = 17; // GPIO17 del ESP32
const int IN3_1 = 18; // GPIO18 del ESP32
const int IN4_1 = 19; // GPIO19 del ESP32

const int IN1_2 = 22; // GPIO22 del ESP32
const int IN2_2 = 23; // GPIO23 del ESP32
const int IN3_2 = 21; // GPIO21 del ESP32
const int IN4_2 = 5;  // GPIO5 del ESP32

const int STEP_DELAY = 1000; // Velocidad de pasos (en microsegundos)

// Secuencia de pasos para ambos motores avanzando hacia adelante
int steps[8][4] = {
    {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
    {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}
};

void setup() {
    pinMode(IN1_1, OUTPUT); pinMode(IN2_1, OUTPUT); pinMode(IN3_1, OUTPUT); pinMode(IN4_1, OUTPUT);
    pinMode(IN1_2, OUTPUT); pinMode(IN2_2, OUTPUT); pinMode(IN3_2, OUTPUT); pinMode(IN4_2, OUTPUT);

    digitalWrite(IN1_1, LOW); digitalWrite(IN2_1, LOW); digitalWrite(IN3_1, LOW); digitalWrite(IN4_1, LOW);
    digitalWrite(IN1_2, LOW); digitalWrite(IN2_2, LOW); digitalWrite(IN3_2, LOW); digitalWrite(IN4_2, LOW);

    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < 5; i++) { // Repetir 6 veces
        moverAdelanteTiempo(3000); // Mover hacia adelante durante 10 segundos
        delay(1000);                // Pausa después de avanzar
        girarIzquierda(179);        // Giro a la izquierda de 180 pasos
        moverAdelanteTiempo(3000); // Mover hacia adelante durante 10 segundos
        delay(1000);                // Pausa después de avanzar
        girarDerecha(358);          // Giro a la derecha de 360 pasos
    }
}

// Función para mover adelante durante un tiempo específico
void moverAdelanteTiempo(int tiempoMs) {
    unsigned long startTime = millis();
    while (millis() - startTime < tiempoMs) {
        for (int i = 0; i < 8; i++) {
            setStep(IN1_1, IN2_1, IN3_1, IN4_1, steps[i][0], steps[i][1], steps[i][2], steps[i][3]);
            setStep(IN1_2, IN2_2, IN3_2, IN4_2, steps[i][0], steps[i][1], steps[i][2], steps[i][3]);
            delayMicroseconds(STEP_DELAY);
        }
    }
}

// Función para girar a la izquierda un número específico de pasos
void girarIzquierda(int pasos) {
    for (int stepCount = 0; stepCount < pasos; stepCount++) {
        for (int i = 0; i < 8; i++) {
            // Motor 1 (izquierda): en sentido contrario (anticlck)
            // Motor 2 (derecha): en el sentido de las agujas del reloj (clockwise)
            // Invertir el sentido de giro para girar a la izquierda
            setStep(IN1_1, IN2_1, IN3_1, IN4_1, steps[7 - i][0], steps[7 - i][1], steps[7 - i][2], steps[7 - i][3]);
            setStep(IN1_2, IN2_2, IN3_2, IN4_2, steps[i][0], steps[i][1], steps[i][2], steps[i][3]);
            delayMicroseconds(STEP_DELAY);
        }
    }
}

void girarDerecha(int pasos) {
    for (int stepCount = 0; stepCount < pasos; stepCount++) {
        for (int i = 0; i < 8; i++) {
            // Un motor avanza y el otro retrocede
            setStep(IN1_1, IN2_1, IN3_1, IN4_1, steps[i][0], steps[i][1], steps[i][2], steps[i][3]);
            setStep(IN1_2, IN2_2, IN3_2, IN4_2, steps[7 - i][0], steps[7 - i][1], steps[7 - i][2], steps[7 - i][3]);
            delayMicroseconds(STEP_DELAY);
        }
    }
}

// Función para configurar los pasos de los motores
void setStep(int IN1, int IN2, int IN3, int IN4, int a, int b, int c, int d) {
    digitalWrite(IN1, a);
    digitalWrite(IN2, b);
    digitalWrite(IN3, c);
    digitalWrite(IN4, d);
}
