/*
 * Main Control Team
 * Arduino Control: Sultan Ibrahim Ibrahim
 * commented commands are used for debugging 
 * NRF24l01+ connections:
    MOSI is connected to the digital pin 11
    MISO is connected to the digital pin 12
    SCK is connected to the digital pin 13
    CE  is connected to the digital pin 9
    CSN is connected to the digital pin 10
    IRQ is not used or connected
*/

#include <SPI.h>                    //the nRF24 modules uses SIP protocol so we must include SPI library
#include "RF24.h"                   //for all nRF24 modules
#include <printf.h>                 //to print nRF24 module detailes if needed
#include "StopWatch.h"              //to allow using stopwatch function for time calculation

const byte pipes[][6] = {"MSTR", "SLV1"};    //this is SLV1 and Rpi is MSTR
const char ACK[40]    = "ACK";               //ACK to be sent to RPi to inform that messease we recived and/or arduino is online
const char UC[40]     = "No such command";   //to send to Rpi if RPI didn't understand the command that was send (if Rpi didn't understand then the command was corrupted on sending)
const char NACK[40]   = "NACK";              //not used
const int  reset      = -1;                  //not used
const byte photoResistorPin = A0;            //the pin the photoresistor reads from
const byte relayPin       = 8;               //the control pin for the relay to turn light on and off
const byte tempPin        = A3;              //the pin for temperature sensor
const byte tempFanPin     = A4;              //the pin connected to the fan to enable or disable it
const byte tempHeaterPin  = A5;              //the pin connected to the heater to enable or disable it
const byte fireDigitalPin = 2;               //read pin for fire (active high: 0 => no fire, 1 => fire detected )
const byte fireAnalogPin  = A1;              //the pin connected to the analog output of the fire sensor
const byte waterLeakagePin= 3;               //the pin connected to PIR sensors digital output read pin for pir  (active high: 0 => no living being was detected, 1 => there is a living being within range)
const byte gasDigitalPin  = 4;               //the pin connected to gas sensors digital output read pin for gas  (active low : 0 => gas within normal levels  , 1 => gas consintration is high )
const byte gasAnalogPin   = A2;              //the pin connected to gas sensors analog output
const byte gasAlarmPin    = 5;               //the pin connected to the alarm(buzzer or led) of gas sensors 
const byte fireAlarmPin   = 6;               //the pin connected to the alarm(buzzer or led) of fire sensors 
const byte waterLeakageAlarm = 7;            //the pin connected to the alarm(buzzer or led) of PIR sensors 

//data
//bool state;                       //if true then lights are on, otherwire lights are off
bool serial_state = 0;              //to store whether there is a serial connection or not
char data[40] = "";                 //to store incoming string from RPi
float photoResistorVoltage;         //to store the voltage from the photoresistor
float tempCelsius;                  //in celsius
float tempReference = 25;           //to store the desired temperature the user wants
float gasVoltage;                   //to store the gas sensors analog reading
float fireVoltage;                  //to store the fire sensors analog reading
int  fireState;                     //to store the fire sensors digital reading
int  waterLeakageState;             //to store the PIR sensors digital reading
int  gasState;                      //to store the gas sensors digital reading
byte retry;                         //to print the number of retries that the program will attempt to send ACK to Rpi before giving up
int current_time;                   //to store the time at point in the program
int lightState;                     //to stores whether the light is turned on or off
int fanState;                       //to stores whether the fan is turned on or off
int heaterState;                    //to stores whether the heater is turned on or off

bool enable = true;                 //enable or disable automatic light control
float onReference  = 3.0;           //referenc voltage to turn light off if below it
bool timeout = false;               //to know when time out and stop the wait for something to happen and move on
bool ret = false;                   //the return of the attempt to write all data to Rpi (0: failed, 1: success)

StopWatch SW;                       //initialize stopwatch
RF24 radio(9, 10);                  //initialize nrf24 module with CE connected to D9 and CSN connected to D10

void setup() {
  Serial.begin(115200);                       //initialize with data rate of 115200 bit per second
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  radio.begin();                              //initialize nrf24 connection
  printf_begin();                             //initialize print radion details
  radio.setRetries(15, 15);                   //set to retry writing (if failed) to max of 15 times with a wait of 15*250us between each retry
  radio.openWritingPipe(pipes[1]);            //open channel on address SLV1 to write to master
  radio.openReadingPipe(1, pipes[0]);         //open channel on address 'MSTR' to read from master
  radio.startListening();                     //set the nrf24 mode to listen for incoming messages

  //set the mode of input and output pins according to the purpose of usage
  pinMode(tempFanPin,OUTPUT);                 //analog pin
  pinMode(tempHeaterPin,OUTPUT);              //analog pin
  pinMode(gasAlarmPin,OUTPUT);
  pinMode(fireAlarmPin,OUTPUT);
  pinMode(waterLeakageAlarm,OUTPUT);
  pinMode(photoResistorPin,INPUT);
  pinMode(relayPin,OUTPUT);
  pinMode(fireDigitalPin,INPUT);
  pinMode(waterLeakagePin,INPUT);
  pinMode(gasDigitalPin,INPUT);
  pinMode(tempPin,INPUT);                     // no need to set its mode to input since it's input by default (analog pin) but we'll do it anyways
}

void loop() {

  //check is serial bus is connected
  if(Serial){
    serial_state = 1;                         //set the serial state to 1 (true) if serial is connected
  }
  else{
    serial_state = 0;                         //set the serial state to 0 (false) if serial is NOT connected
  }

  if(Serial.available() && serial_state){ //for printing data to serial, check is serial bus is connected before printing
    //Serial.println("in serial available");
    char c = toupper(Serial.read());      //just to empty serial buffer
    printData();                          //print the readings of all the sensors
  }

  if (radio.available()){                     //if data are found in nrf24 buffer 
    //Serial.print("available radio !\n");    //for debugging
    receiver();                               //call a function called receiver to handle incoming data (line: 252)
  }

  readVoltage();                              //go ahead and read(update) the values of all sensors (line: 185)

  lightControl();                             //call the function that controls the light (on or off) (line: 102)
  tempControl();                              //call the function that controls the temperature (fan or heater or none) (line: 113)
  gasControl();                               //call the function that controls the gas alarm (on or off) (line: 135)
  waterLeakageControl();                      //call the function that controls the PIR alarm (on or off) (line: 147)
  fireControl();                              //call the function that controls the fire alarm (on or off) (line: 159)
}

//----------------------------------------------

void lightControl(){
  //light control
  if (photoResistorVoltage < (onReference-1)) {   // it's almost dark(according ro sensors datasheet)
    digitalWrite(relayPin, LOW);                  //turn light off
    lightState = 0;                               //light is turend off
  }
  else if (photoResistorVoltage >= onReference) { // some light detected
    digitalWrite(relayPin, HIGH);                 //turn light on
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

void gasControl(){
  //gas control (active low)
  if(gasState == LOW){                            //if gas level is high (sensor is active low)
    digitalWrite(gasAlarmPin,HIGH);               //activate the alarm
    //gasAlarm = true;
  }
  else{                                           //otherwise 
    digitalWrite(gasAlarmPin,LOW);                //stop the alarm
    //gasAlarm = false;
  }
}

void waterLeakageControl(){
    //water leakage Control (active low)
  if(waterLeakageState == HIGH){                 //if no water was detected
    digitalWrite(waterLeakageAlarm,LOW);         //stop the water alarm
    //waterAlarm = true;
  }
  else{                                           //otherwise
    digitalWrite(waterLeakageAlarm,HIGH);         //activate the water alarm
    //waterAlarm = false;
  }
}

void fireControl(){
     //fire control
  if(fireState == HIGH){                          //if fire was detected by the sensor
    digitalWrite(fireAlarmPin,HIGH);              //activate the fire alarm
    //fireAlarm = true;
  }
  else{                                           //otherwise
    digitalWrite(fireAlarmPin,LOW);               //stop the fire alarm
    //fireAlarm = false;
  }
}

//--------------------------------------------------

//conversion is according to the sensors datasheet
float Thermistor(float RawADC) {                  //convert the temperature sensors read to celsius
  float Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );//Temp in Kelvin
  Temp = Temp - 275.15;                           // Convert Kelvin to Celsius
  //Temp = 50- Temp;
  return Temp;
}

//--------------------------------------------------

//read all the sensors readings
void readVoltage() {                                               
  photoResistorVoltage = analogRead(photoResistorPin);             //read light sensors analog output
  photoResistorVoltage = photoResistorVoltage * (5.0 / 1023.0);    //convert to range 0-5V

  tempCelsius = analogRead(tempPin);                               //store voltage first then convert it to celcius
  tempCelsius = Thermistor(tempCelsius);                           //temperature in celcius (line: 174)

  gasVoltage = analogRead(gasAnalogPin);                           //read gas sensors analog output (just for show)
  gasVoltage = gasVoltage * (5.0 / 1023.0);                        //convert to range 0-5V

  fireVoltage = analogRead(fireAnalogPin);                         //read fire sensors analog output (just for show)
  fireVoltage = fireVoltage * (5.0 / 1023.0);                      //convert to range 0-5V
  
  fireState = digitalRead(fireDigitalPin);                         //read fire sensors digital output (the one we use)
  waterLeakageState  = digitalRead(waterLeakagePin);                                 //read PIR sensors digital output
  gasState  = digitalRead(gasDigitalPin);                          //read gas sensors digital output (the one we use) (active low)
}
//---------------------------------------------------
bool sendData(){//write all the available sensors reading to nRF24 which in turn will sent it to Rpi
    ret = true; //this ret is a logical and between all write function (if a single one write failed then the ret will be 0, and if all succeeded then ret will be 1)
    //ret *= radio.write(&reset,sizeof(reset));
    ret *= radio.write(&photoResistorVoltage,sizeof(photoResistorVoltage));
    ret *= radio.write(&onReference,sizeof(onReference));
    ret *= radio.write(&lightState,sizeof(lightState));
    ret *= radio.write(&tempCelsius,sizeof(tempCelsius));
    ret *= radio.write(&tempReference,sizeof(tempReference));
    ret *= radio.write(&fanState,sizeof(fanState));
    ret *= radio.write(&heaterState,sizeof(heaterState));
    ret *= radio.write(&gasVoltage,sizeof(gasVoltage));
    ret *= radio.write(&gasState,sizeof(gasState));
    ret *= radio.write(&fireVoltage,sizeof(fireVoltage));
    ret *= radio.write(&fireState,sizeof(fireState));
    ret *= radio.write(&waterLeakageState,sizeof(waterLeakageState));
    radio.flush_tx();                                             //flush the tx buffer in case any write failed and something remained
    return ret;                                                   //return the overall result of write attempt
}

void printData(){                                                 //print data (readings) to serial (for debugging)
    if(!serial_state){                                            //check to see if serial bus is not connected
      return;                                                     //if not connected then exit the function. there is no one to print to.
    }
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
    Serial.print("Gas sensors Analog Output: ");
    Serial.println(gasVoltage);
    Serial.print("Gas sensors Digital Output: ");
    Serial.println(gasState);
    Serial.print("Fire analog output: ");
    Serial.println(fireVoltage);
    Serial.print("Fire sensors Digital output: ");
    Serial.println(fireState);
    Serial.print("water Leakage State: ");
    Serial.println(waterLeakageState);
    Serial.println("-------------------------------------------------");
}

//whenever there is data received this function will be called to handle the data
void receiver() {
  while (radio.available()) {                              //read all data in buffer
    radio.read(&data, sizeof(char[40]));                   //append all byets to string after converting (casting) them to char
  }
  //Serial.print("recevied: "); Serial.println(data);      //for debugging
  reply();                                                 //call reply function to respond correctly to the message sent (line: 261)
}


int reply() {
  //Serial.println("------------------------------");
  //-----------------------------------------------------------
  if (strcmp(data , "readDataSLV1") == 0) {              //if the received message is readDataSLV1 (indicate that Rpi want to read sensors)
    
    radio.stopListening();                               //stop listening because we're about to talk
    readVoltage();                                       //read latest sensors values
    ret = sendData();                                    //call senddata function to write all the readings to radio (line: 203)
    radio.startListening();                              //now that we sent the data start listening for respond (or if tha data sending failed then Rpi will probably ask us to send data again)
    printData();                                         //print all readings to serial (line: 222)
    
    if(!ret){                                           //if sending failed
      if(serial_state){                                 //check to see if serial bus is connected
        Serial.println("Data was not sent successfully!");
        Serial.println("-------------------------------------------------");
      }
      return 1;                                         //exit function completlry with error (1 indicate error and 0 indicate success[standard error and success return])
    }
    else{                                               //if the write was successful
      /*
      ret = false;
      retry = 0;
      while (!ret && retry <= 5) {                               //if sending failed retry sending again in 1ms for 5 times
        ret = sendData();
        radio.flush_tx();
        retry ++;
        delay(1);
      }
      */
      if(serial_state && !ret){
        Serial.println("Data was sent successfully");
        Serial.println("-------------------------------------------------");
      }
      return 0;                                         //exit
    }
  }
  
  //-------------------------------------------------------------
  else if (strcmp(data , "lightReference") == 0) {      //indicate that Rpi wants to set light reference to a new value
    if(serial_state){                                   //check to see if serial bus is connected
      Serial.println("entering light ref");             //for debugging
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
    
    if (!ret) {                                               //if transmission failed
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
      if(serial_state){                                          //check to see if serial bus is connected
        Serial.println("Timeout, no incoming data");             //print error message and then retry sending data
        Serial.println("---------------------------------------");
      }
      //goto send_data;
      return 1;                                               //exit from function with error
    }
    else{                                                     //if no error happened in reading
      radio.read(&onReference, sizeof(float));                //read the on light refrence 
      if(serial_state){                                       //check to see if serial bus is connected
        Serial.print("onRef received: "); Serial.println(onReference);
        Serial.println("---------------------------------------");
      }
      return 0;                                               //exit function
    }
  }

//--------------------------------------*****************************************************************
  else if (strcmp(data , "tempReference") == 0) {             //incoming message indicate that Rpi wants to set light reference to a new value, do the same as before
    if(serial_state){                                         //check to see if serial bus is connected
      Serial.println("entering temp ref");
      Serial.println("---------------------------------------");
    }
    //send_temp_data:
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
    
    if (!ret) {                                               //if transmission fialed
      radio.startListening();                                 //start listening for incoming messages, Rpi might send some other message later on
      //radio.printDetails();
      if(serial_state){                                       //check to see if serial bus is connected
        Serial.println("failed to send ACK");                 //print error message if module failed to send data
        Serial.println("---------------------------------------");
      }
      return 1;                                               //exit with error
      //loop();
    }

    radio.startListening();
    if(serial_state){                                        //check to see if serial bus is connected
      Serial.print("number of retries: "); Serial.println(retry);
      Serial.println("sent ACK successfully");
    }
    timeout = false;
    SW.start();
    while(!radio.available()){                                 //wait for 400ms for incoming message
      if(SW.elapsed() > 400){
        if(serial_state){                                      //check to see if serial bus is connected
          Serial.print("time: "); Serial.println(SW.elapsed());
        }
        timeout = true;
        break;
      }
    }

    SW.stop();
    SW.reset();
    
    if(timeout){
      if(serial_state){                                             //check to see if serial bus is connected
        Serial.println("Timeout, no incoming data");               //print error message and then retry sending data
        Serial.println("---------------------------------------");
      }
      //goto send_data;
      return 1;
    }
    else{
      radio.read(&tempReference, sizeof(float));
      if(serial_state){                                           //check to see if serial bus is connected
        Serial.print("tempReference received: "); Serial.println(tempReference);
        Serial.println("---------------------------------------");
      }
      return 0;
    }
  }
//----------------------------------------------------**********************************************************
  else {                                                        //if the incoming message is non of what we and Rpi team agreed upon then some error happened during transmission, send unknown command back
    radio.stopListening();                                      //stop listening because we're about to send UC
    if(serial_state){                                           //check to see if serial bus is connected
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
