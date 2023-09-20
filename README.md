# Ölands Köksmejeri 

Ölands Köksmejeri, ett företag specialiserat på osttillverkning, strävar efter att optimera sina processer genom att implementera automatisering. Detta inkluderar schemaläggning av pastörisering under lågkostnadsperioder, programmering av olika ostrecept och inkorporering av larm i grytan för att övervaka avgörande värden som temperatur, tid och pH. För att säkerställa högkvalitativ produktion, strävar företaget efter att låta potten skicka loggdata till en databas, vilket möjliggör sömlös batchinformationshämtning och erbjuder flexibilitet i valet av databas och dess presentation.

* [Ölands Köksmejeri](#ölands-köksmejeri)
   * [Mål](#mål)
   * [Arkitektur](#arkitektur)
   * [Hårdvara](#hårdvara)
   * [Node-Red](#node-red)
      * [PLC Code](#plc-code)
   * [Länkar](#länkar)

      
## Mål
- Autamtisera flödet så att man kan schemalägga pastörisering som är väldigt tidsödande till nattetid när strömmen är billig. 
- Programmera hela recept på olika ystningar.
- Få grytan att larma vid vissa uppnådda värden som temperatur, tid och PH-värde för att säkra kvaliten i produktionen
- Få grytan att skicka loggdata till databas för att kunna knyta ihop all info om varje batch. Val av databas/presentation.

## Arkitektur
![Alt text](/images/image.png)


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
#include <ModbusTCPSlave.h>
#include "PLC.h"
#include "Constants.h"
#include "Holding.h"
#include "Input.h"


byte mac[] = {0x84, 0x42, 0x8B, 0xBA, 0xB2, 0x31};

IPAddress ip(192, 168, 50, 220);

ModbusTCPSlave slave;

Holding holdingRegisters;
Input inputRegisters;
PLC plc;

String strBuffer = "";

void setup() {
  Serial.begin(115200);

  // Init the Ethernet
  Ethernet.begin(mac, ip);
  Serial.println(Ethernet.localIP());


  slave.setHoldingRegisters(holdingRegisters.m, holdingRegisters.m.size());
  slave.setInputRegisters(inputRegisters, inputRegisters.size());

  // Init the ModbusTCPSlave object
  slave.begin();

  // Set all relay pins to output
  pinMode(R0_1, OUTPUT);
  pinMode(R0_2, OUTPUT);
  pinMode(R0_3, OUTPUT);
  pinMode(R0_4, OUTPUT);
  pinMode(R0_5, OUTPUT);
  pinMode(R0_6, OUTPUT);
  pinMode(R0_7, OUTPUT);
  pinMode(R0_8, OUTPUT);

  pinMode(R1_1, OUTPUT);
  pinMode(R1_2, OUTPUT);
  pinMode(R1_3, OUTPUT);
  pinMode(R1_4, OUTPUT);
  pinMode(R1_5, OUTPUT);
  pinMode(R1_6, OUTPUT);
  pinMode(R1_7, OUTPUT);
  pinMode(R1_8, OUTPUT);
  
}


void loop() {
  const float time = millis();

  // Temporary code to read user input from serial monitor
  if (Serial.available()) {
    strBuffer = Serial.readString();
    // strBuffer.trim();
    Serial.println("User input was: " + strBuffer);
  }


  slave.update();

  // now we have all the input and holding registers do run the control logic
  int status = plc.doControlLogic(inputRegisters, holdingRegisters, millis());
}
```


## Länkar
- PT100 transmitter datasheet - https://www.deltaacdrives.com/Delta-DTC-User-Manual.pdf
- VFD datasheet - http://www.realimpeks.co.rs/download/delta_vfd_el.pdf 
- Flowmeter - https://wiki.seeedstudio.com/G1_Water_Flow_Sensor/
- PLC datasheet - https://www.industrialshields.com/web/content/513741 