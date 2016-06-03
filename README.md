#Project
Build automated garden beds that are watered by rain barrels using valves that open based upon moisture content and weather forecast. Also build an automated compost tumbler. Attempt to power everything with solar.

##Primary Goals
  - Create something valuable and inspiring for the community
  - Clear and open documentation intended for reproducibility



#Electronics
The electronic system is intended to record data related to the garden beds that will be transmitted to the internet and used to determine when the plants should be watered. The electronics are also used to control the automatic compost tumbler.

Because this project requires internet communication for data transmission and for querying of weather forecasts, the Raspberry Pi is  used as opposed to a microcontroller.

The Raspberry Pi will have five major components
  - Sensors
  - Data transmission
  - Weather queries
  - Irrigation control
  - Tumbler control


##Design requirements
The electronics should be able to recover from power loss without concern.


##Power Supply
We are using a 15W, 17V solar panel from MCM. 890mA peak.


| Component      | Required Voltage | Current Draw | Reference                                              |
|----------------|------------------|--------------|--------------------------------------------------------|
| Solenoid valve |   9V             |    240 mA    | http://www.mcmelectronics.com/product/28-17449         |
|                |   10V            |    270 mA    |                                                        |
|                |   11V            |    300 mA    |                                                        |
|                |   12V            |    320 mA    |                                                        |
| Tumbler motor  |   12V            | 500 mA stall | https://www.servocity.com/html/0_5_rpm_gear_motor.html |


##Sensors
There are four sensors being  used.

  - Moisture
  - Temperature
  - pH
  - Light

apt-get install python3-rpi.gpio
Moisture and Temperature
pip3 install pi-sht1x


###Moisture
There are two SHT10 humidity sensors in each bed, which sense moisture and temperature. Recommended supply voltage is 3.3V.
+- 4.5%RH and +- 0.5 C accuracy.

Raspberry Pi library for SHT1x can be found here. Tutorial here.

Wiring:
GND = black
DATA = yellow
SCK = blue
VDD = brown

Sht10 guide
https://learn.sparkfun.com/tutorials/sht15-humidity-and-temperature-sensor-hookup-guide


###Data Transmission
Sensor data will be transmitted to the internet and stored on our own server. The nearest wifi access point is about 100 yards away in the Yoder Center. We’ll test wireless range extenders to make the connection.

Data format
Time, M1, M2, M3, T1, T2, T3, pH1, V1pos, V2pos, V3pos,


Transmission is done using 433MHz LoRa. 433MHz chosen for urban environment.


###Solenoid Valves
The water valves have a minimum pressure requirement of .02 MPa (3 psia). With a water density of 1000 kg/m3 (62 lb/ft3), the minimum necessary water level is,

Rho * g * h = dp
H = dp / rho / g

H = 0.02 MPa * 10^6 / 1000 kg/m3 / 9.81 m/s2 = 2 m
H = 6.5 ft



