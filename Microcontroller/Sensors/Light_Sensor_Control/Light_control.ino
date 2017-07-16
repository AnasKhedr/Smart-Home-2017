float photo_resistor_voltage;  //to store the voltage from the photoresistor
byte photo_resistor_pin = A0;  //the pin the photoresistor reads from
byte relay_pin = 8;            //the control pin for the relay

void setup() {
}

void loop() {
 photo_resistor_voltage= analogRead(photo_resistor_pin);
 photo_resistor_voltage=photo_resistor_voltage*(5.0/1023.0);//convert to range 0-5V
 
 if(photo_resistor_voltage >= 2.6){ // it's almost dark
  digitalWrite(relay_pin,LOW);
 }
 else if(photo_resistor_voltage <= 2.4){ // some light detected
  digitalWrite(relay_pin,HIGH);
 }// the threshold at which the light is turned on or off is chosen to satisfy the user's preferences
}
