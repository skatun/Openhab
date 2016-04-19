#include <EnergyMeter.h>

EnergyMeter power1(2);//initialize an instance of the class on node ID 2

void setup(){
  power1.present();

}

void loop(){
  power1.update();
}
