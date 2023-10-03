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

| Water poured (L) | Water YF-S201 (L) | YF-S201/poured |
|------------------|--------------------|------------------------|
| 0.75             | 0.38               | 0.5067 |
| 0.75             | 0.8                | 1.067 |
| 0.75             | 0.4                | 0.5333 |
| 0.75             | 0.77               | 1.027 |
| 0.75             | 1.53               | 2.04 |
| 0.75             | 0.78               | 1.04 |
| 0.75             | 0.8                | 1.067 |
| 0.75             | 0.47               | 0.6267 |
| 0.75             | 0.4                | 0.5333 |
| 0.75             | 0.8                | 1.067 |

| Mean YF-S201/poured | Standard deviation YF-S201/poured |
|------|--------------------|
|0.9508  | 0.45               |



while measuring I am holding the meater and the hose together with my hand. A lot can vary between each test, this could affect the dramatic difference between results.

![image depicting how flow meater was held during test](../images/sink_setup.png)

### Several tests with larger volumes of water

| Water weight (kg) | Water YF-S201 (L) | YF-S201/weighed |
|-------------------|--------------------|--------------------------------|
| 9.4               | 8.68               | 0.9234                         |
| 9.9               | 9.3                | 0.9394                         |
| 10.7              | 9.98               | 0.9327                         |
| 10.7              | 10.02              | 0.9364                         |
| 9.6               | 9.10               | 0.9479                         |
| 9.7               | 9.08               | 0.9360                         |
| 10.2              | 9.63               | 0.9441                         |
| 9.8               | 9.25               | 0.9439                         |
| 10.2              | 9.65               | 0.9461                         |
| 10.2              | 9.38               | 0.8933                         |

| Mean YF-S201/weighed | Standard deviation YF-S201/weighed |
|------|--------------------|
|0.93432  | 0.016152317     |