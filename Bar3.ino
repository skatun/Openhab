// constants won't change. They're used here to
// set pin numbers:
const int buttonPinSpritOpp = 9;     // the number of the pushbutton pin
const int buttonPinSpritNed = 12;     // the number of the pushbutton pin
const int buttonPinVinOpp = 10;     // the number of the pushbutton pin
const int buttonPinVinNed = 11;     // the number of the pushbutton pin

const int ledPinSpritOpp = 4;     // the number of the pushbutton pin
const int ledPinSpritNed = 8;     // the number of the pushbutton pin
const int ledPinVinOpp = 7;     // the number of the pushbutton pin
const int ledPinVinNed = 3;     // the number of the pushbutton pin

const int motorPinVin =  A3;      // the number of the motor pin
const int motorPinOnVin =A1;
const int motorPinOnSprit = A2;//
const int motorPinSprit =  A0;      // the number of the motor pin

//const int debugPin = A1;


int intCode =-1;

long startTime = 0;
void setup() {
  // initialize the LED pin as an output:
 
  pinMode(motorPinSprit, OUTPUT);
  pinMode(motorPinVin, OUTPUT);
  pinMode(motorPinOnSprit, OUTPUT);
  pinMode(motorPinOnVin, OUTPUT);
  
  //pinMode(debugPin, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPinSpritOpp, INPUT_PULLUP);
  pinMode(buttonPinSpritNed, INPUT_PULLUP);
  pinMode(buttonPinVinOpp, INPUT_PULLUP);
  pinMode(buttonPinVinNed, INPUT_PULLUP);
  
  

  digitalWrite(motorPinSprit,HIGH);
  digitalWrite(motorPinVin,HIGH);
  digitalWrite(motorPinOnSprit, HIGH);
  digitalWrite(motorPinOnVin, HIGH);

  //digitalWrite(debugPin, HIGH);
  
  Serial.begin(9600);
  Serial.println("starting now...");
  
  
}

void loop() {

  
  if ( Serial.available()) // Check to see if at least one character is available
  {
    startTime = millis();
    char ch = Serial.read();
    if( isDigit(ch) ) // is this an ascii digit between 0 and 9?
    {
       intCode = (ch - '0');      // ASCII value converted to numeric value
    }
  }

  if (millis() -startTime> 12000 ){
    intCode=-1;
}
  
  if ((digitalRead(buttonPinSpritOpp) == HIGH && digitalRead(buttonPinSpritNed) == LOW) || intCode==1) {
    
    digitalWrite(motorPinSprit,LOW);
    digitalWrite(motorPinOnSprit,LOW);
    
    digitalWrite(ledPinSpritOpp,HIGH);
    digitalWrite(ledPinSpritNed,LOW);
    
    Serial.println("Sprit opp");
  }
 
  
  else if ((digitalRead(buttonPinSpritOpp) == LOW && digitalRead(buttonPinSpritNed) == HIGH)|| intCode==2) {    
    digitalWrite(motorPinSprit,HIGH);
    digitalWrite(motorPinOnSprit,LOW);
    digitalWrite(ledPinSpritNed,HIGH);
    digitalWrite(ledPinSpritOpp,LOW);
    Serial.println("Sprit ned");
  }

  else{
    digitalWrite(motorPinSprit,HIGH); 
    digitalWrite(motorPinOnSprit,HIGH);  
    digitalWrite(ledPinSpritOpp,LOW);
    digitalWrite(ledPinSpritNed,LOW);
  }

  if ((digitalRead(buttonPinVinOpp) == HIGH && digitalRead(buttonPinVinNed) == LOW) || intCode==3) {
    
    
    digitalWrite(motorPinOnVin,LOW);
    digitalWrite(motorPinVin,LOW);
    
    
    digitalWrite(ledPinVinOpp,HIGH);
    digitalWrite(ledPinVinNed,LOW);
    
    Serial.println("Vin opp");
  }
 
  
  else if ((digitalRead(buttonPinVinOpp) == LOW && digitalRead(buttonPinVinNed) == HIGH)|| intCode==4) {
    
    digitalWrite(motorPinVin,HIGH);
    digitalWrite(motorPinOnVin,LOW);
    
    digitalWrite(ledPinVinNed,HIGH);
    digitalWrite(ledPinVinOpp,LOW);
    Serial.println("Vin ned");
  }

  else {  
    digitalWrite(motorPinVin,HIGH); 
    digitalWrite(motorPinOnVin,HIGH);  

    digitalWrite(ledPinVinOpp,LOW);
    digitalWrite(ledPinVinNed,LOW);
  }
  
  if (intCode==0){
    digitalWrite(motorPinOnVin,HIGH); 
    digitalWrite(motorPinOnSprit,HIGH);  
    digitalWrite(ledPinSpritOpp,LOW);
    digitalWrite(ledPinSpritNed,LOW);
    digitalWrite(ledPinVinOpp,LOW);
    digitalWrite(ledPinVinNed,LOW);
    Serial.println("Shutting off");
  }
  
  
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          


