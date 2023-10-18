#include <Arduino.h>
#include <flow_sensor.h>

namespace{
  int referencePulseCount = 0;
  int referenceTime = 0;
  float totalWaterAmount = 0;

  // Based on available sensor data. 
  float pulseFlowKoefficient = 7;
  float calibration = 1;
}

void updatePulseCount(int pulseCount){
  int currentTime = millis();
  float timeDelta = currentTime - referenceTime;

  if( timeDelta >  10000){
    int pulseDelta = pulseCount - referencePulseCount;
    timeDelta = timeDelta / 1000; // converting to seconds
    float frequency = pulseDelta / timeDelta;
    float flowRate = frequency / pulseFlowKoefficient;

    timeDelta = timeDelta / 60; // converting to minutes
    totalWaterAmount += flowRate * timeDelta;

    referencePulseCount = pulseCount;
    referenceTime = currentTime;
  }
}

float getTotalWaterAmount(){
  return totalWaterAmount * calibration;
}

void resetTotalWaterAmount(){
 totalWaterAmount = 0; 
}

void initTimeKeeping(){
  referenceTime = millis();
}