byte digital_pin_fire = 7; //connected to a digital pin on the fire sensor , if output is 1 then there is fire detected within the site of range for the sensor , if the output is 0 then there were no fire detected within the range of sight
byte led_yellow_pin  = 10; //the pin is connected to a yellow led, it will only turn on if the wavelength detected is approaching the fire wavelength
byte led_red_pin     = 11; //the pin is connected to a red led , the led will turn on when the wavelength of fire light is detected
byte analog_pin      = A0; //connected to an analog pin on the fire sensor
byte buzzer_pin      = 12; //connected to an active buzzer, the buzzer will turn on if detected any wavelength related to fire, including sunlight.
byte digital_value;        //variable to store the previous digital value read from the sensor
int  analog_value;         //variable to store the previous analog value read from the sensor

void setup() {
  pinMode(digital_pin_fire  , INPUT);
  pinMode(led_yellow_pin    ,OUTPUT);
  pinMode(led_red_pin       , OUTPUT);
}

void loop() {
  digital_value = digitalRead(digital_pin_fire);
  analog_value  = analogRead (analog_pin);


  digital_value == HIGH ? digitalWrite(buzzer_pin , HIGH) : digitalWrite(buzzer_pin,LOW); // turn on the led if the sensor digital pin is high ( the sensor detects fire )
  /*
  if(digital_value == HIGH)
    digitalWrite(buzzer_pin, HIGH);
  else
    digitalWrite(buzzer_pin, LOW);
  */
  if(analog_value >= 0 && analog_value <= 200){ // the following code is to turn on the yellow and red leds according to the analog values read from the analog pin on the sensor (according to the meaning of each value)
    digitalWrite(led_red_pin , HIGH);
    digitalWrite(led_yellow_pin , LOW);
  }
  else if( analog_value > 300 && analog_value < 600){
    digitalWrite(led_yellow_pin , HIGH);
    digitalWrite(led_red_pin , LOW);
  }
  else if(analog_value>=700){
    digitalWrite(led_red_pin , LOW);
    digitalWrite(led_yellow_pin , LOW);
  }
  
}
