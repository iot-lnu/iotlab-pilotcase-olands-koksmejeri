#include <Arduino.h>

volatile int pulseCount;
volatile float totalWaterAmount;
int hallsensor = 13;
int pulseFlowKoefficient = 8.2;

// put function declarations here:
void increasePulseCount() {
  pulseCount ++;
}

void resetTotalWaterAmount() {
  totalWaterAmount = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hallsensor, INPUT);
  attachInterrupt(hallsensor, increasePulseCount, RISING);
  resetTotalWaterAmount();
}

// Function returns the current flow in liters/minute:
float getCurrentFlow() {
  return pulseCount/pulseFlowKoefficient;
}

void increaseTotalWaterAmount() {
  totalWaterAmount += getCurrentFlow()/60;
}

void loop() {
  pulseCount = 0;
  sei();
  delay(1000);
  cli();
  increaseTotalWaterAmount();
  // Serial.print(getCurrentFlow()/60);
  // Serial.print(getCurrentFlow());
  // Serial.print(" L/M is the current water flow\n");
  Serial.print(totalWaterAmount);
  Serial.print(" L is the total amount of water\n");
}