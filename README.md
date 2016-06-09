# Project
Build automated garden beds that are watered by rain barrels using valves that open based upon moisture content and weather forecast. Also build an automated compost tumbler. Attempt to power everything with solar.

## Primary Goals
  - Create something valuable and inspiring for the community
  - Clear and open documentation intended for reproducibility



# Electronics
The electronic system is intended to record data related to the garden beds that will be transmitted to the internet and used to determine when the plants should be watered. The electronics are also used to control the automatic compost tumbler.

The electronic circuit has five major components:
  - Sensors
  - Data transmission
  - Weather queries
  - Irrigation control
  - Tumbler control

The circuit schematic can be found in VS_garden.fzz.


## Design requirements
The electronics should be able to recover from power loss without concern.


##Power Supply
We are using a 15W, 17V solar panel from MCM. 890mA peak.


| Component      | Required Voltage | Current Draw | Reference                                              |
|----------------|------------------|--------------|--------------------------------------------------------|
| Solenoid valve |   9V             |    240 mA    | http://www.mcmelectronics.com/product/28-17449         |
|                |   10V            |    270 mA    |                                                        |
|                |   11V            |    300 mA    |                                                        |
|                |   12V            |    320 mA (testing shows 500mA)    |                                                        |
| Tumbler motor  |   12V            | 500 mA stall | https://www.servocity.com/html/0_5_rpm_gear_motor.html |


## Sensors
There are four sensors being used.

  - Moisture
  - Temperature
  - pH
  - Light

### pH
pH is be measured using the Atlas Scientific sensor from Sparkfun.
https://www.sparkfun.com/products/10972

### Moisture
There is one SHT10 humidity sensor in each bed, which senses humidity and temperature. Recommended supply voltage is 3.3V.
+- 4.5%RH and +- 0.5 C accuracy.

Wiring:
GND = black
DATA = yellow
SCK = blue
VDD = brown

Sht10 guide
https://learn.sparkfun.com/tutorials/sht15-humidity-and-temperature-sensor-hookup-guide


### Solenoid Valves
The water valves have a minimum pressure requirement of .02 MPa (3 psia). With a water density of 1000 kg/m3 (62 lb/ft3), the minimum necessary water level is,

Rho * g * h = dp
H = dp / rho / g

H = 0.02 MPa * 10^6 / 1000 kg/m3 / 9.81 m/s2 = 2 m
H = 6.5 ft

### Data Transmission
Sensor data will be transmitted to the internet and stored on our local server. A scan of nearby wifi networks wasn't very promising. We've decided to instead transmit our data over LoRa.

Transmission is done using 915 MHz LoRa (rfm69hcw). There's a great introductory tutorial on Sparkfun.
https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide


#### Data format
Time, M1, M2, M3, T1, T2, T3, pH1, V1pos, V2pos, V3pos,

M = moisture
T = temperature
Vpos = valve position
