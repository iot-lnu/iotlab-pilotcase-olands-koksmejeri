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

### Flödesgivare Vatten

![Bild på flödesgivare och pastöriseringsgryta](/images/patörisering.png)

I projektet ingår en flödesgivare vars syfte kommer vara att mäta mängden vatten som pumpats in i manteln på grytan där pastöriseringen sker. Detta vill man göra för att kunna tappa ut vattnet mellan pastöriseringar utan att behöva oroa sig för att värmeelementen startas när det inte finns vatten i manteln, något som skulle kunna få katastrofala följder. Genom att tappa ut vattnet mellan pastöriseringar hoppas man kunna öka livslängden på värmeelementen. Elementen blir igensatta med kalk när de får stå i vatten. Flödesgivaren är försedd med en turbin. Turbinen roterar på grund av rörelsen hos den passerande vätskan. Varje rotation genererar en elektrisk puls. Genom att räkna dessa pulser under en viss tid får vi ut en frekvens som är proportionell mot flödeshastigheten. Tester utfördes där man använde givaren för att beräkna den totala mängden vatten som passerat. Mängden jämfördes med hur mycket det var i verkligheten.

Uppställning försök 1                           | Uppställning försök 2                            | Uppställning Försök 3-5
:----------------------------------------------:|:------------------------------------------------:|:-----------------------------------------------------:
![Uppställning försök 1](/images/sink_setup.png)|![Uppställning försök 2](/images/garden_setup.png)|![Uppställning försök 3-5](/images/garden_setup_2.jpg)

| Beskrivning| antal mätningar | tid för mätning av frekvens (s) | flödesgivare/faktisk mängd (medelvärde) Det förväntade värdet är 1 | flödesgivare/faktisk mängd (standardavvikelse)|
|---------------------------------|-----------------|---------------------------------|-----------------------------------------|-----------------------------------------------|
| Små mängder vatten mättes upp (0.75L). Slang och givare hölls ihop manuellt . Slang och givare manipulerades mycket mellan varje mätning (sattes ihop på nytt mellan varje försök)                                                                                                                                                                     | 10              | 1                               | 0.95                                    | 0.45                                          |
| Stora mängder vatten mättes upp (ca 10L) Slang och givare satt ihop med adapter. Slang och givare manipulerades mellan varje mätning (hängdes ur och i hink)                                                                               | 10              | 1                               | 0.93                                    | 0.016                                         |
| Stora mängder vatten mättes upp (ca 10L) Slang och givare satt ihop med adapter. Slang och givare manipulerades lite mellan varje mätning. (slang permanent upphängd på stol) Uppmätta värden skalades om utifrån resultat från föregående försök | 5               | 1                               | 1.039                                   | 0.016                                         |
| Stora mängder vatten mättes upp (ca 10L) Slang och givare satt ihop med adapter. Slang och givare manipulerades lite mellan varje mätning. (slang permanent upphängd på stol)                                                                     | 10              | 10                              | 0.97                                    | 0.0069                                        |
| Försök 3 utan skalade värden                                                                                                                                                                                                                     | 5               | 1                              | 0.964                                   | 0.015                                         |

Det första försöket har den största standardavvikelsen, detta skulle kunna förklaras av hur man hanterade givaren och slangen mellan mätningar, men också av att man mätte upp små mängder vätska i detta försök. Det verkar som att resultatet påverkas av hur givaren och slangen/röret sitter ihop, samt hur de är placerade i förhålllande till varandera, detta kan vara anledningen till att medelvärdet varierar mellan olika försök, samt att standardavvikelsen verkar bli mindre ju mindre man rör slangen och givaren mellan mätningarna i samma försök. Detta indikerar att sensorn behöver kalibreras varje gång den installeras på ett nytt ställe. Enligt dessa tester verkar det som att en längre tid för att mäta pulser gör standardavvikelsen mindre, dock måste man komma ihåg att det gjordes hälften så många mätningar vid försöket där pulserna räknas under kortare tid med samma uppställning av utrustningen. Har det råkat komma med ett avvikande värde i försöket med kortare pulsräkningstid, så kan detta ha stor påverkan på standardavvikelsen. Se [water-flow-sensor](/water-flow-sensor/) för att läsa mer om testerna som utförts. det verkar som att det går att mäta upp en mängd vatten med en felmarginal som är mindre än 10%. 

## Mjukvara 

Tillståndsmaskinen nedan visar vilka tillstånd PLC har. 

![Alt text](/images/olands_statem.png)
 
## Modbus 
### Input Registers
| Register | Description | Measurement Units | Type | Implemented |
| --- | --- | --- | --- | --- |
| 0 | Current State | - | uint16_t | Yes |
| 1 | Time Left | - | uint16_t | Yes |
| 2 | Temperature | Celsius | float | No |
| 3 | Flow | LPM | float | No |
| 4 | Liters in Mantle | Liters | float | No |


### Holding Registers
| Register | Description | Units | Type | Implemented |
| --- | --- | --- | --- | --- |
| 0 | Start or stop | on/off (0 or 1) | uint16_t | Yes |
| 1 | State the PLC should be put into prior to starting | See states table below | uint16_t | Yes |
| 2 | Fill water duration | Minutes | uint16_t | Yes |
| 3 | Set water volume | Liters | uint16_t | No |
| 4 | Stirring speed | RPM | uint16_t | No |
| 5 | Set heating temperature | Celsius | uint16_t | Yes |
| 6 | Set cooling temperature | Celsius | uint16_t | No |
| 7 | Hold temperature duration | Minutes | uint16_t | Yes |
| 8 | Register C | - | uint16_t | No |
| 9 | Register D | - | uint16_t | No |
| 10 | Register E | - | uint16_t | No |
| 11 | Register F | - | uint16_t | No |
| 12 | Register G | - | uint16_t | No |
| 13 | Register H | - | uint16_t | No |
| 14 | Register I | - | uint16_t | No |
| 15 | Register J |- | uint16_t | No |
| 16 | Register K | - | uint16_t | No |
| 17 | Register L | - | uint16_t | No |
| 18 | Register M (End of pasteurization setting) | - | uint16_t | No |

| State | Number | Description |
| --- | --- | --- |
| Idle state | 1 | The system is not active and waiting for an action. LED: constant green LED |
| Fill water state | 2 | The system is in the process of filling water. LED: blinking green LED|
| Pasteurization state | 3 | The system is in pasteurization process. LED: constant yellow LED |
| Error state | 99 | The system is in Error State. LED: constant red LED |

## Node-Red

![](https://hackmd.io/_uploads/SJkabkrp3.png)


## Länkar
- PT100 transmitter datasheet - https://www.deltaacdrives.com/Delta-DTC-User-Manual.pdf
- VFD datasheet - http://www.realimpeks.co.rs/download/delta_vfd_el.pdf 
- Flowmeter - https://wiki.seeedstudio.com/G1_Water_Flow_Sensor/
- PLC datasheet - https://www.industrialshields.com/web/content/513741 