# Ölands Köksmejeri 


## Mål
- Autamtisera flödet så att man kan schemalägga pastörisering som är väldigt tidsödande till nattetid när strömmen är billig. 
- Programmera hela recept på olika ystningar.
- Få grytan att larma vid vissa uppnådda värden som temperatur, tid och PH-värde för att säkra kvaliten i produktionen
- Få grytan att skicka loggdata till databas för att kunna knyta ihop all info om varje batch. Val av databas/presentation.

## Arkitektur
![](https://hackmd.io/_uploads/ry9WGLz6h.png)


## Hårdvara 
![](https://hackmd.io/_uploads/rkgJ9XSfp2.png)

-  [ESP32 PLC 38R](https://www.industrialshields.com/shop/034001000300-esp32-plc-38r-2906?product=product.template%282906%2C%29#attr=142,2244,2245,3729,2246,4064,3806)
-  Övrig hårdvara:

| Funktion |	Relä	|Analog in	|Digital in|	Analog ut |	Digital ut|
| -------- | -------- | -------- |-------- |-------- |-------- |
|Värmare 1                          |X| || |X|
|Värmare 2                          |X| || |X|
|Omrörning vänster	                |X| || |X|
|Omrörning höger	                |X| || |X|
|Omrörning hastighet                | | ||X| |
|Temperaturgivare PT100	            | |X|| | |		
|Nivågivare vatten i manteln	    | | || | |				
|Magnetventil vatten in (kallt)	    |X| || | |		
|Magnetventil vatten ut (kallt/hett)|X| || | |		
|**Övriga grejer på önskelistan** 					
|Flödesgivare vatten                | |X|| | |			
|PH-mätare mjölk                    | |X|| | |				
|Dispenser för kultur, flytande     |X| || | |			
|Dispenser för löpe, flytande	    |X| || | |				

## Node-Red

![](https://hackmd.io/_uploads/SJkabkrp3.png)


### PLC Code 

```cpp
/*
   Copyright (c) 2018 Boot&Work Corp., S.L. All rights reserved

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Ethernet.h>
#include <ModbusTCPSlave.h>

// Ethernet configuration values
uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
IPAddress ip(192, 168, 1, 170);
const uint16_t port = 502;

// Modbus registers mapping
// This example uses the M-Duino21+ mapping
int digitalOutputsPins[] = {
  R0_1, R0_2, R0_3, R0_4, R0_5, R0_6, R0_7, R0_8, R1_1, R1_2, R1_3, R1_4, R1_5, R1_6, R1_7, R1_8
};


#define numDigitalOutputs int(sizeof(digitalOutputsPins) / sizeof(int))
#define numAnalogOutputs int(20)

bool digitalOutputs[numDigitalOutputs];
uint16_t analogOutputs[numAnalogOutputs];

// Define the ModbusTCPSlave object
ModbusTCPSlave modbus(port);

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600UL);

  // Init variables, inputs and outputs
  for (int i = 0; i < numDigitalOutputs; ++i) {
    digitalOutputs[i] = false;
    digitalWrite(digitalOutputsPins[i], digitalOutputs[i]);
  }

  // Init Ethernet
  Ethernet.begin(mac, ip);
  Serial.println(Ethernet.localIP());

  // Init ModbusTCPSlave object
  modbus.begin();

  modbus.setCoils(digitalOutputs, numDigitalOutputs);
  modbus.setHoldingRegisters(analogOutputs, numAnalogOutputs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  // Process modbus requests
  modbus.update();

  // Update outputs
  for (int i = 0; i < numDigitalOutputs; ++i) {
    digitalWrite(digitalOutputsPins[i], digitalOutputs[i]);
  }
  for (int i = 0; i < numAnalogOutputs; ++i) {
    Serial.print(analogOutputs[i]);
    Serial.print(" ");
  }
  Serial.println();
}
```
