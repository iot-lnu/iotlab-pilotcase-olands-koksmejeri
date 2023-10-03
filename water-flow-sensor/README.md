# YF-S201 tests

Below is a summary of [Sensor informmation](https://components101.com/sensors/yf-s201-water-flow-measurement-sensor) found online.
|Flow(L/H)|Frequency(Hz)|
---|---
|120|16|
|240|32.5|
|360|49.3|
|480|65.5|
|600|82|
|720|90.2|

![Graph of flow VS frequency](../images/Flow_Frequency.png)
Green line: Freqiency = Flow x 8.2

Orange line: Freqiency = Flow x 7.5
## Water through sensor using a funnel


| Water poured (L) | Water measured (L) | Pulse flow formula     |
|------------------|--------------------|------------------------|
| 0.75             | 0.63               | Freqiency = Flow x 7.5 |
| 0.75             | 0.5                | Freqiency = Flow x 8.2 |

Funnel is to big and water can't be poured without spilling

## Test with hose

Freqiency = Flow x 8.2. Measure pulse s for 1 s at a time. The sensor was attatched to a hose. Around 25 L of water was poured. Sensor reported 20.58 L.

###  Freqiency = Flow x 7.5

This is the recomended value according to google. If 7.5 was used in the previous test, the ressult would have been 20.58 x 8.2/7.5 = 22.5
doing several tests to see cositancy. The fact that Im pumping a very small amount each try could throw the ressults off.

| Water poured (L) | Water measured (L) | Pulse flow formula     |
|------------------|--------------------|------------------------|
| 0.75             | 0.38               | Freqiency = Flow x 7.5 |
| 0.75             | 0.8                | Freqiency = Flow x 7.5 |
| 0.75             | 0.4                | Freqiency = Flow x 7.5 |
| 0.75             | 0.77               | Freqiency = Flow x 7.5 |
| 0.75             | 1.53               | Freqiency = Flow x 7.5 |
| 0.75             | 0.78               | Freqiency = Flow x 7.5 |
| 0.75             | 0.8                | Freqiency = Flow x 7.5 |
| 0.75             | 0.47               | Freqiency = Flow x 7.5 |
| 0.75             | 0.4                | Freqiency = Flow x 7.5 |
| 0.75             | 0.8                | Freqiency = Flow x 7.5 |

| Mean | Standard deviation |
|------|--------------------|
|0.71  | 0.34               |



while measuring I am holding the meater and the hose together with my hand. A lot can vary between each test, this could affect the dramatic difference between results.

![image depicting how flow meater was held during test](../images/sink_setup.png)