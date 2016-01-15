#include <Servo.h>

#define MOTOR0_PIN 0
#define MOTOR1_PIN 0
#define MOTOR2_PIN 6
#define MOTOR3_PIN 11

#define MOTOR_COUNT 4
#define CHANNEL_COUNT 6

#define CHANNEL1_PIN 3
#define CHANNEL2_PIN 10
#define CHANNEL3_PIN 8
#define CHANNEL4_PIN 4
#define CHANNEL5_PIN 0
#define CHANNEL6_PIN 0

#define CHANNEL1_MIN 1100
#define CHANNEL1_MAX 1900
#define CHANNEL2_MIN 1100
#define CHANNEL2_MAX 1900
#define CHANNEL3_MIN 1100
#define CHANNEL3_MAX 1900
#define CHANNEL4_MIN 1100
#define CHANNEL4_MAX 1900

#define MOTOR_MIN 700
#define MOTOR_MAX 2000

int pulseinAux = 0;
byte motor_pins[] = {MOTOR0_PIN, MOTOR1_PIN, MOTOR2_PIN, MOTOR3_PIN};
byte channel_pins[] = {CHANNEL1_PIN, CHANNEL2_PIN, CHANNEL3_PIN, CHANNEL4_PIN, CHANNEL5_PIN, CHANNEL6_PIN};

Servo motors[MOTOR_COUNT];
int speeds[] = {0, 0, 0, 0};
int ch1, ch2, ch3, ch4, ch5, ch6;

void setup() {  
  for (int i = 0; i < CHANNEL_COUNT; i++) {
    pinMode(channel_pins[i], INPUT);
  }

  for (int i = 0; i < MOTOR_COUNT; i++) {
    motors[i].attach(motor_pins[i]);
  }

  Serial.begin(9600);
}

void loop() {
  if (pulseinAux == 0) {
    ch1 = pulseIn(CHANNEL1_PIN, HIGH); 
    ch1 = map(ch1, CHANNEL1_MIN, CHANNEL1_MAX, -25, 25);
    ch2 = pulseIn(CHANNEL2_PIN, HIGH); 
    ch2 = map(ch2, CHANNEL2_MIN, CHANNEL2_MAX, -25, 25);
    pulseinAux = 1;
  } else {
    ch3 = pulseIn(CHANNEL3_PIN, HIGH);    
    ch3 = map(ch3, CHANNEL3_MIN, CHANNEL3_MAX, 0, 100); 
    ch4 = pulseIn(CHANNEL4_PIN, HIGH); 
    ch4 = map(ch4, CHANNEL4_MIN, CHANNEL4_MAX, -25, 25);
    pulseinAux = 0;
  }

  speeds[0] = ch3 - ch2;
  speeds[1] = ch3 + ch1;
  speeds[2] = ch3 + ch2;
  speeds[3] = ch3 - ch1;

  for (int i = 0; i < MOTOR_COUNT; i++) {
    speeds[i] = map(speeds[i], -25, 125, MOTOR_MIN, MOTOR_MAX); 
  }
  
  for (int i = 0; i < MOTOR_COUNT; i++) {
    motors[i].write(speeds[i]);
  }
}
