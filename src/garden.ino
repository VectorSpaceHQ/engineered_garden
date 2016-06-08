#include <Wire.h>
#include <SHT1x.h>

void setup()  {
}

void loop()  {

    h1 = get_humidity(1);
    transmit_data(h1);
}


int get_humidity(sensor) {
    return humidity;
}

int get_pH() {
    return pH;
}

int operate_valve() {

}

void transmit_data(){

}
