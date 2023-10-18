#include <Arduino.h>
#include <flow_sensor.h>

volatile int pulseCount;
volatile int totalPulseCount;
volatile float totalWaterAmount;
int hallsensor = 13;

int delayTimeMicroSeconds = 1000;
float delayTimeSeconds = delayTimeMicroSeconds/1000;
float delayTimeMinutes = delayTimeSeconds/60;

// This number is used to turn the pulse frequency in to a waterflow
float pulseFlowKoefficient = 7;

// This nober is used to adjust the final results so they correspond with reality.
// It was found by comparing how much water was actually pured to how much was 
// poured according to the program.
float weightFromTests = 1.0753;

void increasePulseCount() {
  pulseCount ++;
  totalPulseCount ++;
}

// void resetTotalWaterAmount() {
//   totalWaterAmount = 0;
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hallsensor, INPUT);
  attachInterrupt(hallsensor, increasePulseCount, RISING);
  sei();
  initTimeKeeping();
}

// Function returns the current flow in liters/minute:
float getCurrentFlow() {
  return pulseCount / (pulseFlowKoefficient * delayTimeSeconds);
}

void increaseTotalWaterAmount() {
  totalWaterAmount += getCurrentFlow() * delayTimeMinutes;
}

float getWeightedTotalAmount() {
  return totalWaterAmount * weightFromTests;
}

void loop() {
  pulseCount = 0;
  delay(delayTimeMicroSeconds);
  updatePulseCount(totalPulseCount);
  increaseTotalWaterAmount();

  Serial.print(totalWaterAmount);
  Serial.print(" L is the total amount of water according to sensor\n");
  
  Serial.print(getTotalWaterAmount());
  Serial.print(" L is the total amount of water according to library and sensor\n");
}