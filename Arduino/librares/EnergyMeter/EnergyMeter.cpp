#include "EnergyMeter.h" //include the declaration for this class


#include <SPI.h>
#include <MySensor.h>  

long PULSE_FACTOR       // Nummber of blinks per KWH of your meeter
boolean SLEEP_MODE        // Watt-value can only be reported when sleep mode is false.
long MAX_WATT          // Max watt value to report. This filetrs outliers.
int DIGITAL_INPUT_SENSOR // Usually the interrupt = pin -2 (on uno/nano anyway)
int CHILD_ID              // Id of the sensor child
unsigned long SEND_FREQUENCY
double ppwh

boolean pcReceived = false;
volatile unsigned long pulseCount = 0;   
volatile unsigned long lastBlink = 0;
volatile unsigned long watt = 0;
unsigned long oldPulseCount = 0;   
unsigned long oldWatt = 0;
double oldKwh;
unsigned long lastSend;


//<<constructor>> setup the LED, make pin 13 an OUTPUT
EnergyMeter::EnergyMeter(int _CHILD_ID){
	CHILD_ID   = _CHILD_ID;           // Id of the sensor child
	
	/* Optional Arguments */
	SEND_FREQUENCY = 20000; // Minimum time between send (in milliseconds). We don't wnat to spam the gateway.
	PULSE_FACTOR =1000;       // Nummber of blinks per KWH of your meeter
	SLEEP_MODE =  false ;       // Watt-value can only be reported when sleep mode is false.
	MAX_WATT = 10000;          // Max watt value to report. This filetrs outliers.
	DIGITAL_INPUT_SENSOR = 0; // Usually the interrupt = pin -2 (on uno/nano anyway)
	

	/*Starting the setup algorithm */
	ppwh = ((double)PULSE_FACTOR)/1000; // Pulses per watt hour
	
	MyMessage wattMsg(CHILD_ID,V_WATT);
	MyMessage kwhMsg(CHILD_ID,V_KWH);
	MyMessage pcMsg(CHILD_ID,V_VAR1);
	
	// Fetch last known pulse count value from gw
	request(CHILD_ID, V_VAR1);

	// Use the internal pullup to be able to hook up this sketch directly to an energy meter with S0 output
	// If no pullup is used, the reported usage will be too high because of the floating pin
	pinMode(DIGITAL_INPUT_SENSOR,INPUT_PULLUP);
	  
	attachInterrupt(INTERRUPT, onPulse, RISING);
	lastSend=millis();
}

//<<destructor>>
EnergyMeter::~EnergyMeter(){/*nothing to destruct*/}

//present it
void ENERGYMETER::present(){
    // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Energy Meter", "1.0");

  // Register this device as power sensor
  present(CHILD_ID, S_POWER);
}


//update the reading of the power
void ENERGYMETER::update(){
 
  unsigned long now = millis();
  // Only send values at a maximum frequency or woken up from sleep
  bool sendTime = now - lastSend > SEND_FREQUENCY;
  if (pcReceived && (SLEEP_MODE || sendTime)) {
    // New watt value has been calculated  
    if (!SLEEP_MODE && watt != oldWatt) {
      // Check that we dont get unresonable large watt value. 
      // could hapen when long wraps or false interrupt triggered
      if (watt<((unsigned long)MAX_WATT)) {
        send(wattMsg.set(watt));  // Send watt value to gw 
      }  
      Serial.print("Watt:");
      Serial.println(watt);
      oldWatt = watt;
    }
  
    // Pulse cout has changed
    if (pulseCount != oldPulseCount) {
      send(pcMsg.set(pulseCount));  // Send pulse count value to gw 
      double kwh = ((double)pulseCount/((double)PULSE_FACTOR));     
      oldPulseCount = pulseCount;
      if (kwh != oldKwh) {
        send(kwhMsg.set(kwh, 4));  // Send kwh value to gw 
        oldKwh = kwh;
      }
    }    
    lastSend = now;
  } else if (sendTime && !pcReceived) {
    // No count received. Try requesting it again
    request(CHILD_ID, V_VAR1);
    lastSend=now;
  }
  
  if (SLEEP_MODE) {
    sleep(SEND_FREQUENCY);
  }
}

}


void receive(const MyMessage &message) {
  if (message.type==V_VAR1) {  
    pulseCount = oldPulseCount = message.getLong();
    Serial.print("Received last pulse count from gw:");
    Serial.println(pulseCount);
    pcReceived = true;
  }
}

void onPulse()     
{ 
  if (!SLEEP_MODE) {
    unsigned long newBlink = micros();  
    unsigned long interval = newBlink-lastBlink;
    if (interval<10000L) { // Sometimes we get interrupt on RISING
      return;
    }
    watt = (3600000000.0 /interval) / ppwh;
    lastBlink = newBlink;
  } 
  pulseCount++;
}