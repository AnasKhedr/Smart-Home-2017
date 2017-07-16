byte temp_sensor_pin = A0;  //for the sensor's output pin
float sensor_read;          //analog value read from the sensor
double temp_cel;            //temperature in celsius
byte fan_pin = 8;           //for the fan's enable
byte heater_pin = 9;        //for the heater's enable

double Thermistor(float RawADC) { //convert the sensor's read to celcius
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );//Temp in Kelvin
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  return Temp;
}

void setup() {
  pinMode(fan_pin,OUTPUT);
  pinMode(heater_pin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensor_read = analogRead(temp_sensor_pin);
  temp_cel = Thermistor(sensor_read);

  if(temp_cel >= 29){          //the range is chosen to satisfy the user's preferences
    digitalWrite(fan_pin,HIGH);
    digitalWrite(heater_pin,LOW);
  }
  else if(temp_cel <=23){
    digitalWrite(heater_pin,HIGH);
    digitalWrite(fan_pin,LOW);
  }
  else if(temp_cel < 27 && temp_cel > 21){
    digitalWrite(heater_pin,LOW);
    digitalWrite(fan_pin,LOW);
  }
}
