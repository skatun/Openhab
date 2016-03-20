const byte whPerPulse = 1;  // K factor or pulse constant (Wh/pulse)
const int pulsePin = 3;
double power;

volatile byte printFlag = 0;
volatile unsigned long pulseState = 0xAAAAAAAA, pulseCount = 0, pulseTime = 0, lastTime = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(pulsePin, INPUT_PULLUP);
  attachInterrupt(1, onPulse, FALLING); // pin 3
}

void loop()
{
  pulseState = pulseState << 1 | digitalRead(pulsePin);
  if (printFlag) {
    printFlag = 0;
    power = double((3600000000.0 / (pulseTime - lastTime)) * whPerPulse); // calculate power
    Serial.print(power);
    Serial.print(' ');
    Serial.println(pulseCount * whPerPulse);  // watt hour elapsed
  }
}

void onPulse()
{
  pulseState = pulseState << 1 | digitalRead(pulsePin);
  if (pulseState == 0xFFFFFFFE) { // if previously high for 31 reads, then falling
    lastTime = pulseTime;
    pulseTime = micros();
    if (pulseTime - lastTime > 10000) { // limit to 100Hz maximum pulse rate
      pulseCount++;
      printFlag = 1;
    }
  }
}
