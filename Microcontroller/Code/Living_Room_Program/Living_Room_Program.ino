/*
 * Arduino Team:
    MOSI is connected to the digital pin 11
    MISO is connected to the digital pin 12
    SCK is connected to the digital pin 13
    CE  is connected to the digital pin 9
    CSN is connected to the digital pin 10
    IRQ is not used or connected
*/

#include "DHT.h"
//#include <AccelStepper.h>
#include <Stepper.h>
#include <SPI.h>                    //the nRF24 modules uses SIP protocol so we must include SPI library
#include "RF24.h"                   //for all nRF24 modules
#include <printf.h>                 //to print nRF24 module detailes if needed
#include "StopWatch.h"              //to allow using stopwatch function for time calculation

//defines
#define STEPS_PER_MOTOR_REVOLUTION 32  
#define HALFSTEP   8      //interface 8 means a 4 wire half stepper
#define motorPin1  2      // IN1 on the ULN2003 driver 1
#define motorPin2  3      // IN2 on the ULN2003 driver 1
#define motorPin3  4      // IN3 on the ULN2003 driver 1
#define motorPin4  5      // IN4 on the ULN2003 driver 1

#define DHTPIN 7          // what digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11

//constants
const byte pipes[][6] = {"MSTR2", "SLV2"};  //this is SLV2 and Rpi is MSTR
const char ACK[40]    = "ACK";               //ACK to be sent to RPi to inform that messease we recived and/or arduino is online
const char UC[40]     = "No such command";   //to send to Rpi if RPI didn't understand the command that was send (if Rpi didn't understand then the command was corrupted on sending)
const char NACK[40]   = "NACK";              //NACK to be sent to RPi to inform that arduino failed to do the command requested

const byte photoResistorPin = A0;            //the pin the photoresistor reads from
const byte relayPin         = 6;             //the control pin for the relay to turn light on and off
const byte tempPin          = A1;            //the pin for temperature sensor
const byte tempFanPin       = A2;            //the pin connected to the fan to enable or disable it
const byte tempHeaterPin    = A3;            //the pin connected to the heater to enable or disable it
const byte PIRPin           = A4;            //the pin connected to PIR sensors digital output read pin for pir  (active high: 0 => no living being was detected, 1 => there is a living being within range)
//const byte PIRAlarmPin      = 7;             //the pin connected to the alarm(buzzer or led) of PIR sensors 
const byte tvPin            = 8;             //the pin connected to the tv (turn on and off the tv)
const byte contactPin       = A5;            //the pin connected to the garage contact to indicate whether it's open or closed

//data
bool serial_state = 0;
char data[40] = "";                 //to store incoming string from RPi
float tempCelsius;                  //temperature in celcius
float tempReference = 25;           //to store the desired temperature the user wants
int lightState;                     //to store whether the light is turned on or off
int PIRState;                       //to store the PIR sensors digital reading
int fanState;                       //to store whether the fan is turned on or off
int heaterState;                    //to store whether the heater is turned on or off
int garageState;                    //to store whether the garage is open or closed
float photoResistorVoltage;
float onReference  = 3.0;
byte retry;                         //to print the number of retries that the program will attempt to send ACK to Rpi before giving up
int startPosition;
int tvState;
float humidityOutside;
float temperatureOutside;

bool timeout = false;               //to know when time out and stop the wait for something to happen and move on
bool ret = false;                   //the return of the attempt to write all data to Rpi (0: failed, 1: success)
bool garageRetern;

StopWatch SW;                       //initialize stopwatch
RF24 radio(9, 10);                  //initialize nrf24 module with CE connected to D9 and CSN connected to D10
//AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
Stepper stepper(STEPS_PER_MOTOR_REVOLUTION, motorPin1, motorPin3, motorPin2, motorPin4);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);                       //initialize with data rate of 115200 bit per second
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  //Serial.println("entered setup");
  radio.begin();                              //initialize nrf24 connection
  printf_begin();                             //initialize print radion details
  radio.setRetries(15, 15);                   //set to retry writing (if failed) to max of 15 times with a wait of 15*250us between each retry
  radio.openWritingPipe(pipes[1]);            //open channel on address SLV1 to write to master
  radio.openReadingPipe(1, pipes[0]);         //open channel on address 'MSTR' to read from master
  radio.startListening();                     //set the nrf24 mode to listen for incoming messages

  //Serial.println("setting up motor");
  stepper.setSpeed(400);
  /*
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(100.0);
  stepper.setSpeed(200);
  */

  dht.begin();

  //Serial.println("setting pinmode");
  //setting the mode of input and output pins according to the purpose of usage
  pinMode(tempPin,INPUT);
  pinMode(tempFanPin,OUTPUT);                 //analog pin
  pinMode(tempHeaterPin,OUTPUT);              //analog pin
  pinMode(photoResistorPin,INPUT);
  pinMode(relayPin,OUTPUT);
  pinMode(PIRPin,INPUT);
  //pinMode(PIRAlarmPin,OUTPUT);                // no need to set its mode to input since it's input by default (analog pin) but we'll do it anyways
  pinMode(tvPin,OUTPUT);
  pinMode(contactPin,INPUT);

  //Serial.println("just before findstart()");
  //findStart();                               //when uncommented causes problem with tempReference, check stepper control in general 
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void loop() {

  if(Serial){
    serial_state = 1;
  }
  else{
    serial_state = 0;
  }
  
  if(Serial.available() && serial_state){ //for printing data to serial
    Serial.println("in serial available");
    char c = toupper(Serial.read());      //just to empty serial buffer
    printData();
  }
  
  if (radio.available()){                     //if data are found in nrf24 buffer 
    //Serial.print("available radio !\n");    //for debugging
    receiver();                               //call a function called receiver to handle incoming data (line: 252)
  }

  readVoltage();                              //go ahead and read(update) the values of all sensors (line: 185)

  lightControl();                             //call the function that controls the light (on or off) (line: 102)
  tempControl();                              //call the function that controls the temperature (fan or heater or none) (line: 113)
  PIRControl();                               //call the function that controls the PIR alarm (on or off) (line: 147)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void readVoltage(){
  photoResistorVoltage = analogRead(photoResistorPin);             //read light sensors analog output
  photoResistorVoltage = photoResistorVoltage * (5.0 / 1023.0);    //convert to range 0-5V

  tempCelsius = analogRead(tempPin);                               //store voltage first then convert it to celcius
  tempCelsius = Thermistor(tempCelsius);                           //temperature in celcius (line: 174)

  PIRState  = digitalRead(PIRPin);                                 //read PIR sensors digital output
  garageState = digitalRead(contactPin);                           //read grage state (open or closed)

  temperatureOutside = dht.readTemperature();                      //read temperature in Celsius (the default)
  humidityOutside = dht.readHumidity(); 

}

//--------------------------------------------------------------------
/*
int findStart(){ //move untill you close the door
  stepper.moveTo(-20000);                                        // +ve means clockwise
  garageState = digitalRead(contactPin);

  while(!garageState){                                          //while the garage door is still open
    stepper.run();
    garageState = digitalRead(contactPin);
    
    if(stepper.distanceToGo() == 0){
      Serial.println("we couldn't close the door, something is wrong we either the switch or the motor!");
      return 1;
    }
  }

  startPosition = stepper.currentPosition();
  Serial.print("we reached start position at: "); Serial.println(startPosition);
  return 0;
}
*/
//--------------------------------------------------------------------

void lightControl(){
  //light control
  if (photoResistorVoltage < (onReference-1)) {   // some light detected
    digitalWrite(relayPin, LOW);                 //turn light off
    lightState = 0;                               //light is turend off
  }
  else if (photoResistorVoltage >= onReference) { // it's almost dark(according ro sensors datasheet) 
    digitalWrite(relayPin, HIGH);                  //turn light on
    lightState = 1;                               //light is turned on
  }// the threshold at which the light is turned on or off is chosen to satisfy the user's preferences
}

void tempControl(){
    //temperature control
  if(tempCelsius >= (tempReference+3)){           //if the current temperature(tempCelsius) is larger than the desired value+margin << the range is chosen to satisfy the user's preferences
    digitalWrite(tempFanPin,HIGH);                //turn on the fan
    fanState = 1;
    digitalWrite(tempHeaterPin,LOW);              //turn off the heater
    heaterState = 0;
  }
  else if(tempCelsius <=(tempReference-3)){       //if the current temperature(tempCelsius) is smaller than the desired value+margin
    digitalWrite(tempHeaterPin,HIGH);             //turn on heater
    heaterState = 1;
    digitalWrite(tempFanPin,LOW);                 //turn off heater
    fanState = 0;
  }
  else if(tempCelsius < (tempReference+2) && tempCelsius > (tempReference-2)){ //current temperature is within desired value + and - margin
    digitalWrite(tempHeaterPin,LOW);              //turn off heater
    heaterState = 0;
    digitalWrite(tempFanPin,LOW);                 //turn off fan
    fanState = 0;
  }
}

void PIRControl(){ //no pin for PIRAlarmPin
  //PIR Control (active high)
  if(PIRState == HIGH){                           //if a lifeform was detected
    //digitalWrite(PIRAlarmPin,HIGH);               //activate the pir alarm
    //PIRAlarm = true;
  }
  else{                                           //otherwise
    //digitalWrite(PIRAlarmPin,LOW);                //stop the pir alarm
    //PIRAlarm = false;
  }
}

void tvControl(bool state){
  digitalWrite(tvPin ,state);
  tvState = state;
}

int garageDoorControl(bool open_close){ //state == 1 means closed
  garageState = digitalRead(contactPin);
  
  if(!open_close){// open the door if it's closed otherwise, do nothing
    if(garageState){//if the garage is closed
      stepper.step(3000); //change to the number of steps that will open the door
      garageState = digitalRead(contactPin);
      
      if(garageState){//if garage is still open
        if(serial_state){
          Serial.println("failed to open garage door!");
        }
        return 1;
      }
      else{
        if(serial_state){
          Serial.println("garage door was opened successfully.");
        }
        return 0;
      }
    }
    else{//if the garage door is open
      if(serial_state){
        Serial.println("garage door is aleady open!");
      }
      return 0;
    }
  }
  
  else if(open_close){// close the door if it's opened otherwise, do nothing
    int count = 0;
    if(!garageState){//if the garage door is open
        while(!garageState && count < 2000){
          stepper.step(-10);
          count++;
          garageState = digitalRead(contactPin);
        }
      }
      if(!garageState){//if garage is still open
        if(serial_state){
          Serial.println("failed to close garage door!");
        }
        return 1;
      }
      else{
        if(serial_state){
          Serial.println("garage door was closed successfully.");
        }
        return 0;
      }
    }
    else{//if the garage door is closed
      if(serial_state){
        Serial.println("garage door is aleady closed!");
      }
      return 0;
    }
}

//--------------------------------------------------------------------

float Thermistor(int RawADC) {                  //convert the temperature sensors read to celsius
  float Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );//Temp in Kelvin
  Temp = Temp - 271.15;                           // Convert Kelvin to Celsius
  Temp = 50- Temp;
  return Temp;
}

//---------------------------------------------------------------------

bool sendData(){//write all the available sensors reading to nRF24 which in turn will sent it to Rpi
    ret = true; //this ret is a logical and between all write function (if a single one write failed then the ret will be 0, and if all succeeded then ret will be 1)
    //ret *= radio.write(&reset,sizeof(reset));
    //Serial.print("photoResistorVoltage send: "); Serial.println(ret);
    ret *= radio.write(&photoResistorVoltage,sizeof(photoResistorVoltage)); //float
    ret *= radio.write(&onReference,sizeof(onReference));
    ret *= radio.write(&lightState,sizeof(lightState));
    ret *= radio.write(&tempCelsius,sizeof(tempCelsius));
    ret *= radio.write(&tempReference,sizeof(tempReference));
    ret *= radio.write(&fanState,sizeof(fanState));
    ret *= radio.write(&heaterState,sizeof(heaterState));
    ret *= radio.write(&PIRState,sizeof(PIRState));
    ret *= radio.write(&garageState,sizeof(garageState));
    ret *= radio.write(&tvState,sizeof(tvState));
    ret *= radio.write(&humidityOutside,sizeof(humidityOutside));
    ret *= radio.write(&temperatureOutside,sizeof(temperatureOutside));
    radio.flush_tx();                                             //flush the tx buffer in case any write failed and something remained
    return ret;                                                   //return the overall result of write attempt
}

void printData(){                                                 //print data (readings) to serial (for debugging)
    if(!serial_state)
      return
    
    Serial.println("-------------------------------------------------");
    Serial.print("Photo Resistor Voltage: ");
    Serial.println(photoResistorVoltage);
    Serial.print("Photo Resistor Reference: ");
    Serial.println(onReference);
    Serial.print("light State: ");
    Serial.println(lightState);
    Serial.print("temperature: ");
    Serial.println(tempCelsius);
    Serial.print("temperature Reference: ");
    Serial.println(tempReference);
    Serial.print("fan State: ");
    Serial.println(fanState);
    Serial.print("heater State: ");
    Serial.println(heaterState);
    Serial.print("PIR sensors Digital Output: ");
    Serial.println(PIRState);
    Serial.print("Garage state is: ");
    Serial.println(garageState);
    Serial.print("TV state is: ");
    Serial.println(tvState);
    Serial.print("humidityOutside is: ");
    Serial.println(humidityOutside);
    Serial.print("temperatureOutside is: ");
    Serial.println(temperatureOutside);
    Serial.println("-------------------------------------------------");
}

//--------------------------------------------------------------------

//whenever there is data received this function will be called to handle the data
void receiver(){
  while (radio.available()) {                              //read all data in buffer
    radio.read(&data, sizeof(char[40]));                   //append all byets to string after converting (casting) them to char
  }
  if(serial_state){
    Serial.print("recevied: "); Serial.println(data);      //for debugging
  }
  reply();                                                 //call reply function to respond correctly to the message sent (line: 261)
}

//---------------------------------------------------------------------

void reply(){
  //Serial.println("------------------------------");
  //-----------------------------------------------------------
  if (strcmp(data , "readDataSLV2") == 0) { 
    
    //Serial.println("entered readDataSLV2");
    radio.stopListening();                               //stop listening because we're about to talk
    readVoltage();                                       //read latest sensors values
    ret = sendData();                                    //call senddata function to write all the readings to radio (line: 203)
    radio.startListening();                              //now that we sent the data start listening for respond (or if tha data sending failed then Rpi will probably ask us to send data again)
    printData();                                         //print all readings to serial (line: 222)
    
    if(!ret){                                           //if sending failed
      if(serial_state){
        Serial.println("Data was NOT sent successfully!");
        Serial.println("-------------------------------------------------");
      }
      return 1;                                         //exit function completlry with error (1 indicate error and 0 indicate success[standard error and success return])
    }
    else{                                               //if the write was successful
      if(serial_state){
        Serial.println("Data was sent successfully");
        Serial.println("-------------------------------------------------");
      }
      return 0;                                         //exit
    }
  }

  //-------------------------------------------------------------
  else if (strcmp(data , "lightReference") == 0){
    if(serial_state){
      Serial.println("entering light ref");               //for debugging
      Serial.println("---------------------------------------");
    }
    //send_light_data:                                  //used in previous version of this communication protocol
    radio.stopListening();                              //stop listening because we're about to talk
    
    ret = false;
    retry = 0;
    while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
      ret = radio.write(&ACK, sizeof(char[40]));               //of course, this write command already retries sending 15 times with a delay of 15*250us between every retry (like we setup before in setRetries [line: 68])
      radio.flush_tx();                                        //empty the tx buffer in case transmission failed
      retry ++;
      delay(1);
    }
    
    radio.flush_tx();                                          //empty the tx buffer just to be sure
    
    if (!ret) {                                               //if transmission fialed
      radio.startListening();                                 //start listening for incoming messages, Rpi might send some other message later on
      //radio.printDetails();
      if(serial_state){
        Serial.println("failed to send ACK");                   //print error message if module failed to send data
        Serial.println("---------------------------------------");
      }
      return 1;                                               //exit with error
      //loop();
    }

    radio.startListening();                                   //start listening for incoming messages, Rpi might send some other message later on
    if(serial_state){
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK successfully");
    }
    timeout = false;
    SW.start();                                                 //start counting time
    while(!radio.available()){                                  //while no messages in rx buffer
      if(SW.elapsed() > 400){                                   //wait for 400ms for incoming message, used to be 2000ms
        if(serial_state){
          Serial.print("time: "); Serial.println(SW.elapsed());
        }
        timeout = true;                                         //if 400ms passed and still no no icoming message
        break;                                                  //break from the while loop
      }
    }

    SW.stop();                                                 //stop the counter
    SW.reset();                                                //reset the counter
      
    if(timeout){
      if(serial_state){
        Serial.println("Timeout, no incoming data");             //print error message and then retry sending data
        Serial.println("---------------------------------------");
      }
      //goto send_data;
      return 1;                                               //exit from function with error
    }
    else{                                                     //if no error happened in reading
      radio.read(&onReference, sizeof(float));                //read the on light refrence 
      if(serial_state){
        Serial.print("onRef received: "); Serial.println(onReference);
        Serial.println("---------------------------------------");
      }
      return 0;                                               //exit function
    }
  }

  //-------------------------------------------------------------
  else if (strcmp(data , "tempReference") == 0){
    if(serial_state){
      Serial.println("entering temp ref");
      Serial.println("---------------------------------------");
    }
    //send_temp_data:
    radio.stopListening();
    //Serial.println("stopped listening");
    ret = false;
    retry = 0;
    while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
      ret = radio.write(&ACK, sizeof(char[40]));
      radio.flush_tx();
      retry ++;
      delay(1);
    }
    //Serial.println("doen writing");
    radio.flush_tx();
    
    if (!ret) {
      radio.startListening();
      //radio.printDetails();
      if(serial_state){
        Serial.println("failed to send ACK");  //print error message if module failed to send data
        Serial.println("---------------------------------------");
      }
      return 1;
      //loop();
    }

    radio.startListening();
    if(serial_state){
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK successfully");
    }
    timeout = false;
    SW.start();
    while(!radio.available()){                                  //wait for 400ms for incoming message
      if(SW.elapsed() > 2000){
        if(serial_state)
          Serial.print("time: "); Serial.println(SW.elapsed());
        timeout = true;
        break;
      }
    }

    SW.stop();
    SW.reset();
    
    if(timeout){
      if(serial_state){
       Serial.println("Timeout, no incoming data");               //print error message and then retry sending data
       Serial.println("---------------------------------------");
      }
      //goto send_data;
      return 1;
    }
    else{
      radio.read(&tempReference, sizeof(float));
      if(serial_state){
        Serial.print("tempReference received: "); Serial.println(tempReference);
        Serial.println("---------------------------------------");
      }
      return 0;
    }
  }

  //-------------------------------------------------------------
  else if(strcmp(data , "tvOn") == 0){
    if(serial_state){
      Serial.println("entering tvOn");
      Serial.println("---------------------------------------");
    }

    Serial.println("enter tv control");
    tvControl(1);
    Serial.println("exit tv control");
    radio.stopListening();
    
    ret = false;
    retry = 0;
    while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
      ret = radio.write(&ACK, sizeof(char[40]));
      radio.flush_tx();
      retry ++;
      delay(1);
    }

    radio.flush_tx();
    
    if (!ret) {
      radio.startListening();
      //radio.printDetails();
      if(serial_state){
        Serial.println("failed to send ACK");  //print error message if module failed to send data
        Serial.println("---------------------------------------");
      }
      return 1;
      //loop();
    }

    radio.startListening();
    if(serial_state){
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK successfully");
    }
    //Serial.println("exit tv on");
  }

  //-------------------------------------------------------------
  else if(strcmp(data , "tvOff") == 0){
    if(serial_state){
      Serial.println("entering tvOff");
      Serial.println("---------------------------------------");
    }
    
    tvControl(0);                                             //turn off tv
    radio.stopListening();
    
    ret = false;
    retry = 0;
    while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
      ret = radio.write(&ACK, sizeof(char[40]));
      radio.flush_tx();
      retry ++;
      delay(1);
    }

    radio.flush_tx();
    
    if (!ret) {
      radio.startListening();
      //radio.printDetails();
      if(serial_state){
        Serial.println("failed to send ACK");  //print error message if module failed to send data
        Serial.println("---------------------------------------");
      }
      return 1;
      //loop();
    }

    radio.startListening();
    if(serial_state){
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK successfully");
    }
  }

  //-------------------------------------------------------------
  else if(strcmp(data , "openGarageDoor") == 0){
    if(serial_state){
      Serial.println("---------------------------------------");
      Serial.println("entering openGarageDoor");
    }
    
    garageRetern = garageDoorControl(0);                                             //open garage door
    radio.stopListening();
    
    ret = false;
    retry = 0;
    
    if(garageRetern == 0){//success
      while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
        ret = radio.write(&ACK, sizeof(char[40]));
        radio.flush_tx();
        retry ++;
        delay(1);
      }
      if (!ret) {
        radio.startListening();
        //radio.printDetails();
        if(serial_state){
          Serial.println("failed to send ACK");  //print error message if module failed to send data
          Serial.println("---------------------------------------");
        }
        return 1;
        //loop();
      }
    }
    else{//failed
      while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
        ret = radio.write(&NACK, sizeof(char[40]));
        radio.flush_tx();
        retry ++;
        delay(1);
      }

      if (!ret) {
        radio.startListening();
        //radio.printDetails();
        if(serial_state){
          Serial.println("failed to send NACK");  //print error message if module failed to send data
          Serial.println("---------------------------------------");
        }
        return 1;
        //loop();
      }
    }

    radio.flush_tx();  

    radio.startListening();
    if(serial_state){
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK/NACK successfully");
      Serial.println("---------------------------------------");
    }
    return 0;
  }

  //-------------------------------------------------------------
  else if(strcmp(data , "closeGarageDoor") == 0){
    if(serial_state){
    Serial.println("---------------------------------------");
    Serial.println("entering closeGarageDoor");
    }
    
    garageRetern = garageDoorControl(1);                                             //close garage door
    radio.stopListening();
    
    ret = false;
    retry = 0;

    if(garageRetern == 0){//success
      while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
        ret = radio.write(&ACK, sizeof(char[40]));
        radio.flush_tx();
        retry ++;
        delay(1);
      }
      if (!ret) {
        radio.startListening();
        //radio.printDetails();
        if(serial_state){
          Serial.println("failed to send ACK");  //print error message if module failed to send data
          Serial.println("---------------------------------------");
        }
        return 1;
        //loop();
      }
    }
    else{//failed
      while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
        ret = radio.write(&NACK, sizeof(char[40]));
        radio.flush_tx();
        retry ++;
        delay(1);
      }
      if (!ret) {
        radio.startListening();
        //radio.printDetails();
        if(serial_state){
          Serial.println("failed to send NACK");  //print error message if module failed to send data
          Serial.println("---------------------------------------");
        }
        return 1;
        //loop();
      }
    }
    
    radio.flush_tx();
    
    radio.startListening();
    if(serial_state){
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK/NACK successfully");
      Serial.println("---------------------------------------");
    }
    return 0;
  }

  else{
    radio.stopListening();                                      //stop listening because we're about to send UC
    if(serial_state){
      Serial.println("---------------------------------------");
      Serial.println("unknown command!");
      Serial.print("command is: "); Serial.print(data); Serial.print(", or: "); Serial.println((atof(data)));
      Serial.println("---------------------------------------");
    }
    radio.write(&UC, sizeof(char[40]));                        //send unknowen command
    radio.startListening();                                    //start listening for incoming messages, Rpi probably will send the command again since we didn't understand it
    //radio.printDetails();
  }
}

