const byte gasAnalogPin  = A0; //GAS sensor Analog output pin (high voltage indicate high concentration)
const byte gasDigitalPin = 2; //Gas sensor Digital output pin (active Low), trigger value can be adjusted by the potentiometer on the back of the module.
const byte PIRPin        = 3; //PIR sensor Digital output pin (active High), if a moving object detected (human or animal) then the sensor will output high.

const byte gasAlarm      = 4; //outupt high when Gas Detected
const byte PIRAlarm      = 5; //output high while object detected within sensors range.

float GasVoltage;             //variable to store the voltage of analog output of gas sensor.

void setup()
{
 Serial.begin(9600); //Initialize serial port 9600 bps
}

void loop()
{
  //Gas Control
  if(digitalRead(gasDigitalPin) == LOW){
    digitalWrite(gasAlarm,HIGH);
  }
  else{
    digitalWrite(gasAlarm,LOW);
  }
  //PIR Control
  if(digitalRead(PIRPin) == HIGH){
    digitalWrite(PIRAlarm,HIGH);
  }
  else{
    digitalWrite(PIRAlarm,LOW);
  }

  GasVoltage = (float)analogRead(gasAnalogPin)*5/(float)1024;
  Serial.println("-------------------------------------------------");
  Serial.print("Gas sensors Digital Output: ");
  Serial.println(digitalRead(gasDigitalPin));
  Serial.print("Gas sensors Analog Output: ");
  Serial.println(GasVoltage);
  Serial.print("PIR sensors Digital Output: ");
  Serial.println(digitalRead(PIRPin));
  delay(1000); // Print value every 1 sec.
}
