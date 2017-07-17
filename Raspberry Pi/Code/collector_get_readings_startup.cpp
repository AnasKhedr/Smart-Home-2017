#include <unistd.h>			//to use usleep()
#include <stdio.h>			//to use printf()
#include <RF24/RF24.h>		//to use nRF24 module
#include <iostream>			//to use << and using std
#include <ctime>			//to get the time now
#include <fstream>			//to write to text file
#include <string.h>			//to used strcmp()
#include <sstream>			//to use string stream
#include <stdlib.h>     	//to use system, NULL, EXIT_FAILURE

//#include <sys/stat.h>     //for mkfifo()

using namespace std;

/*
//fifo creation
int fifo_state;
FILE *fp;
char fifo_name[] = "readings_file";
char read_buffer[40];
char temp[40];


//----------------
 */

char send[40]  = "readDataSLV1";
char send2[40] = "readDataSLV2";
int current_time;
bool timeout;
bool ret;
time_t time_now = time(0);

//SLV2 variables 
float lightVoltage;	//the voltage of the reading of the photo resistor
float refVoltage;	//the reference of the reference of the light in voltage
float gasVoltage; 	//variable to store the voltage of analog output of gas sensor after beeing converted from (1024 to 5.0). 
int lightState;   	//whether light is turned on or off
float tempCelsius;	//current temp of room in celsius
float tempRef;		//temp refernce set by user
int fanState;		//the fan state, is it on or off
int heaterState;	//the heater state. is it on or off
int gasState;		//whether gas alarm is on or off (1 is fine 0 means gas level is high) active low
float fireVoltage;	//the voltage reading of the fire sensor (5V is no any file, 0V too much fire)
int fireState;		//whether there is fire or no
int waterLeakageState;
//data of SLV2
int PIRState2; 		//whether the PIR sensor detected someone or not
float lightVoltage2;
float refVoltage2;
int lightState2;
float tempCelsius2;	//current temp of room in celsius
float tempRef2;		//temp refernce set by user
int fanState2;		//the fan state, is it on or off
int heaterState2;	//the heater state. is it on or off
int garageState2;
int tvState2;
float humidityOutside2;
float temperatureOutside2;

//---------------------------------------------------- 

// CE , CSN , speed = 8MHZ 
//RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ); //physical pin 15 and 24
RF24 radio(22,0); //GPIO22 and CE0
uint8_t pipes[][6]  = {"MSTR" ,"SLV1"};
uint8_t pipes2[][6] = {"MSTR2" , "SLV2" };

using namespace std;
																			   
int readSLV(int retry){
	ofstream logFile;
	logFile.open("safty_readings.log", ios::app);
	
	if(retry != 0){
		if(retry == 4){
			logFile<<"failed to send request to SLV1 after 4 attempts\n";
			logFile<<"runtime: "<<clock()<<endl;
			logFile<<"-----------------------------------------\n";
			logFile<<"*****************************************\n";
			logFile.close();
			return 1;
		}
		logFile<<"Reattempting to send request to SLV1. attempt number: "<<retry<<endl;
		cout<<"Reattempting to send request to SLV1. attempt number: "<<retry<<endl;
	}
	else{
		logFile<<ctime(&time_now);
		logFile<<"*****************************************\n";
	}
	
	ret = radio.write(&send,sizeof(char[40]));
	if(ret == false){
		printf("failed to send request to SLV1\n");
		logFile<<"failed to send request to SLV1\n";
		logFile<<"runtime: "<<clock()<<endl;
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//exit(1);
	}
	else{
		printf("read request was sent to SLV1\n");
		logFile<<"read request was sent to SLV1\n";
	}
	radio.startListening();
	//reset:
	
	// get lightVoltage
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&lightVoltage,sizeof(lightVoltage));
		printf("light Voltage = %f\n",lightVoltage);
		logFile << "light Voltage: " <<lightVoltage<<endl;
	}
	else{
		printf("failed to rececive light Voltage (timeout)\n");
		logFile<<"failed to rececive light Voltage (timeout)\n";
		//perror("failed to rececive light Voltage (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get reference voltage
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&refVoltage,sizeof(refVoltage));
		printf("reference Voltage = %f\n",refVoltage);
		logFile << "reference Voltage: " <<refVoltage<<endl;
	}
	else{
		printf("failed to rececive reference Voltage (timeout)\n");
		logFile<<"failed to rececive reference Voltage (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive reference Voltage (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get light state
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&lightState,sizeof(lightState));
		printf("light State = %d\n",lightState);
		logFile << "light State: " <<lightState<<endl;
	}
	else{
		printf("failed to rececive light State (timeout)\n");
		logFile<<"failed to rececive light State (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive light State (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get temp Celcius
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&tempCelsius,sizeof(tempCelsius));
		printf("tempreature Celcius = %f\n",tempCelsius);
		logFile << "tempreature Celcius: " <<tempCelsius<<endl;
	}
	else{
		printf("failed to rececive tempreature Celcius (timeout)\n");
		logFile<<"failed to rececive tempreature Celcius (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive tempreature Celcius (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get temp Reference
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&tempRef,sizeof(tempRef));
		printf("tempreature Reference = %f\n",tempRef);
		logFile << "tempreature Reference: " <<tempRef<<endl;
	}
	else{
		printf("failed to rececive tempreature Reference (timeout)\n");
		logFile<<"failed to rececive tempreature Reference (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive tempreature Reference (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get fan State
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&fanState,sizeof(fanState));
		printf("fan State = %d\n",fanState);
		logFile << "fan State: " <<fanState<<endl;
	}
	else{
		printf("failed to rececive fan State (timeout)\n");
		logFile<<"failed to rececive fan State (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive fan State (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get heater State
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&heaterState,sizeof(heaterState));
		printf("heater State = %d\n",heaterState);
		logFile << "heater State: " <<heaterState<<endl;
	}
	else{
		printf("failed to rececive heater State (timeout)\n");
		logFile<<"failed to rececive heater State (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive heater State (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get gasVoltage
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&gasVoltage,sizeof(gasVoltage));
		printf("gas voltage = %f\n",gasVoltage);
		logFile << "gas Voltage: " <<gasVoltage<<endl;
	}
	else{
		printf("failed to rececive gas voltage (timeout)\n");
		logFile<<"failed to rececive gas voltage (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive gas voltage (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	
	//get gasState
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&gasState,sizeof(gasState));
		printf("gas state = %d\n",gasState);
		logFile << "gas state: " <<gasState<<endl;
	}
	else{
		printf("failed to rececive gas state (timeout)\n");
		logFile<<"failed to rececive gas state (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive gas state (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get fireVoltage
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&fireVoltage,sizeof(fireVoltage));
		printf("fire Voltage= %f\n",fireVoltage);
		logFile << "fire Voltage: " <<fireVoltage<<endl;
	}
	else{
		printf("failed to rececive fire Voltage (timeout)\n");
		logFile<<"failed to rececive fire Voltage (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive fire Voltage (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get fireState
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&fireState,sizeof(fireState));
		printf("fire State = %d\n",fireState);
		logFile << "fire State: " <<fireState<<endl;
	}
	else{
		printf("failed to rececive fire State (timeout)\n");
		logFile<<"failed to rececive fire State (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive fire State (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get waterleakage State
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	//cout<<"entering water"<<endl;
	if(!timeout){
		radio.read(&waterLeakageState,sizeof(waterLeakageState));
		printf("waterleakage State = %d\n",waterLeakageState);
		logFile << "waterleakage State: " <<waterLeakageState<<endl;
	}
	else{
		printf("failed to rececive waterleakage State (timeout)\n");
		logFile<<"failed to rececive waterleakage State (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive waterleakage State (timeout)\n");
		//exit(1);
		//goto reset;
	}
	//cout<<"exited water"<<endl;

	
	//logFile<<"runtime: "<<clock()<<endl;
	logFile<<"-----------------------------------------\n";
	logFile.close();
	return 0;
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

int readSLV2(int retry){
	radio.stopListening();
	radio.closeReadingPipe(1);
	//radio.openReadingPipe(2,pipes2[1]);
	radio.openWritingPipe(pipes2[0]);
	radio.openReadingPipe(1,pipes2[1]);
	
	ofstream logFile;
	logFile.open("safty_readings.log", ios::app);
	if(retry != 0){
		if(retry == 4){
			logFile<<"failed to send request to SLV2\n";
			logFile<<"runtime: "<<clock()<<endl;
			logFile<<"-----------------------------------------\n";
			logFile<<"*****************************************\n";
			logFile.close();
			return 1;
		}
		logFile<<"Reattempting to send request to SLV2. attempt number: "<<retry<<endl;
		cout<<"Reattempting to send request to SLV2. attempt number: "<<retry<<endl;
	}
	else
		logFile<<ctime(&time_now);
	
	ret = radio.write(&send2,sizeof(char[40]));
	//radio.startListening();
	if(ret == false){
		printf("failed to send request to SLV2\n");
		logFile<<"failed to send request to SLV2\n";
		logFile<<"runtime: "<<clock()<<endl;
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//exit(1);
	}
	else{
		printf("read request was sent to SLV2\n");
		logFile<<"read request was sent to SLV2\n";
	}
	radio.startListening();
	
	// get lightVoltage2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&lightVoltage2,sizeof(lightVoltage2));
		printf("light Voltage 2 = %f\n",lightVoltage2);
		logFile << "light Voltage 2: " <<lightVoltage2<<endl;
	}
	else{
		printf("failed to rececive light Voltage 2 (timeout)\n");
		logFile<<"failed to rececive light Voltage 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive light Voltage 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get reference voltage 2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&refVoltage2,sizeof(refVoltage2));
		printf("reference Voltage 2 = %f\n",refVoltage2);
		logFile << "reference Voltage 2: " <<refVoltage2<<endl;
	}
	else{
		printf("failed to rececive reference Voltage 2 (timeout)\n");
		logFile<<"failed to rececive reference Voltage 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive reference Voltage 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get light state 2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&lightState2,sizeof(lightState2));
		printf("light State 2 = %d\n",lightState2);
		logFile << "light State 2: " <<lightState2<<endl;
	}
	else{
		printf("failed to rececive light State 2 (timeout)\n");
		logFile<<"failed to rececive light State 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive light State 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get temp Celcius 2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&tempCelsius2,sizeof(tempCelsius2));
		printf("tempreature Celcius 2 = %f\n",tempCelsius2);
		logFile << "tempreature Celcius 2: " <<tempCelsius2<<endl;
	}
	else{
		printf("failed to rececive tempreature Celcius 2 (timeout)\n");
		logFile<<"failed to rececive tempreature Celcius 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive tempreature Celcius 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get temp Reference 2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&tempRef2,sizeof(tempRef2));
		printf("tempreature Reference 2 = %f\n",tempRef2);
		logFile << "tempreature Reference 2: " <<tempRef2<<endl;
	}
	else{
		printf("failed to rececive tempreature Reference 2 (timeout)\n");
		logFile<<"failed to rececive tempreature Reference 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive tempreature Reference 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get fan State 2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&fanState2,sizeof(fanState2));
		printf("fan State 2 = %d\n",fanState2);
		logFile << "fan State 2: " <<fanState2<<endl;
	}
	else{
		printf("failed to rececive fan State 2 (timeout)\n");
		logFile<<"failed to rececive fan State 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive fan State 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	// get heater State 2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&heaterState2,sizeof(heaterState2));
		printf("heater State 2 = %d\n",heaterState2);
		logFile << "heater State 2: " <<heaterState2<<endl;
	}
	else{
		printf("failed to rececive heater State 2 (timeout)\n");
		logFile<<"failed to rececive heater State 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive heater State 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get PIRState2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&PIRState2,sizeof(PIRState2));
		printf("PIR State = %d\n",PIRState2);
		logFile << "PIR State: " <<PIRState2<<endl;
	}
	else{
		printf("failed to rececive PIR State (timeout)\n");
		logFile<<"failed to rececive PIR State (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive PIR State (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get garageState2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&garageState2,sizeof(garageState2));
		printf("garage State 2 = %d\n",garageState2);
		logFile << "garage State 2: " <<garageState2<<endl;
	}
	else{
		printf("failed to rececive garage State 2 (timeout)\n");
		logFile<<"failed to rececive garage State 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive garage State 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get tvState2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&tvState2,sizeof(tvState2));
		printf("tv State 2 = %d\n",tvState2);
		logFile << "tv State 2: " <<tvState2<<endl;
	}
	else{
		printf("failed to rececive tv State 2 (timeout)\n");
		logFile<<"failed to rececive tv State 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive tv State 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get humidityOutside2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&humidityOutside2,sizeof(humidityOutside2));
		printf("humidity Outside 2 = %d %%\n",(int)humidityOutside2);
		logFile << "humidity Outside 2: " <<humidityOutside2<<"%"<<endl;
	}
	else{
		printf("failed to rececive humidity Outside 2 (timeout)\n");
		logFile<<"failed to rececive humidity Outside 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive humidity Outside 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	//get temperatureOutside2
	current_time = millis();
	timeout = false;
	while(!radio.available()){
		if(millis() - current_time > 500){
			timeout = true;
			break;
		}
	}
	
	if(!timeout){
		radio.read(&temperatureOutside2,sizeof(temperatureOutside2));
		printf("temperature Outside 2 = %d C\n",(int)temperatureOutside2);
		logFile << "temperature Outside 2: " <<temperatureOutside2<<"C"<<endl;
	}
	else{
		printf("failed to rececive temperature Outside 2 (timeout)\n");
		logFile<<"failed to rececive temperature Outside 2 (timeout)\n";
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
		//perror("failed to rececive temperature Outside 2 (timeout)\n");
		//exit(1);
		//goto reset;
	}
	
	logFile<<"runtime: "<<clock()<<endl;
	logFile<<"-----------------------------------------\n";
	logFile<<"*****************************************\n";
	logFile.close();
	return 0;
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setGUIReadings(){ //updating the file that GUI program uses to update its readings
	ofstream gui;		//to store readings of SLV1
	ofstream gui2;		//to store readings of SLV2
	gui.open("guiReadings.txt", ios::in | ios::out);
	gui2.open("guiReadings2.txt", ios::in | ios::out);
	//for SLV1
	gui<<lightVoltage<<endl;
	gui<<refVoltage<<endl;
	gui<<gasVoltage<<endl;
	gui<<lightState<<endl;
	gui<<tempCelsius<<endl;
	gui<<tempRef<<endl;
	gui<<fanState<<endl;
	gui<<heaterState<<endl;
	gui<<gasState<<endl;
	gui<<fireVoltage<<endl;
	gui<<fireState<<endl;
	gui<<waterLeakageState<<endl;	
	gui.close();
	
	//for SLV2
	gui2<<lightVoltage2<<endl;
	gui2<<refVoltage2<<endl;
	gui2<<lightState2<<endl;
	gui2<<tempCelsius2<<endl;
	gui2<<tempRef2<<endl;
	gui2<<fanState2<<endl;
	gui2<<heaterState2<<endl;
	gui2<<PIRState2<<endl;
	gui2<<garageState2<<endl;
	gui2<<tvState2<<endl;
	gui2<<humidityOutside2<<endl;
	gui2<<temperatureOutside2<<endl;
	gui2.close();
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
void sendAllToServer(){ //send all reading to server
	
	stringstream command;
	
	cout<<"----------------------------------------\n";
	cout<<"begin to send to server"<<endl;
	//command<<"\"";
	command<<"php temp.php 3 ";			//id of temp sensor 1
	command<<tempCelsius;				//current temp
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	command.str("");
	//command<<"\"";
	command<<"php temp.php 18 ";			//id of temp sensor 4
	command<<tempCelsius;				//current temp
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	
	command.str("");
	//command<<"\"";
	command<<"php update.php 2 ";           //sid = 2 if for sensor fire_1
	command<<fireState;             	      
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	
	command.str("");
	//command<<"\"";
	command<<"php update.php 4 ";			//pir sensor
	command<<PIRState2;					//pir state, found someone or nor
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	command.str("");
	//command<<"\"";
	command<<"php update.php 6 ";			//tv state
	command<<tvState2;						//open or closed
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	command.str("");
	//command<<"\"";
	command<<"php update.php 9 ";			//gasLeakage
	command<<!gasState;						//reverse the state for server and becasue the sensor is active low
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	command.str("");
	//command<<"\"";
	command<<"php update.php 10 ";			//waterLeakage
	command<<!waterLeakageState;			//reverse the reading for server and becasue the sensor is active low
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	
	command.str("");
	//command<<"\"";
	command<<"php update.php 15 ";			//garage door
	command<<garageState2;			
	//command<<"\"";
	system(command.str().c_str());
	cout<<"command: "<<command.str().c_str()<<endl;
	cout<<"exit send all to server"<<endl;
	
	/*
	command<<"php update.php 7 ";			//light_2
	command<<"0";
	command<<"&sid=8 ";			//fire_2
	command<<"0";
	command<<"&sid=9 ";
	command<<"0";
	command<<"&sid=10 ";
	command<<"0";
	command<<"&sid=11 ";
	command<<"0";
	command<<"&sid=12 ";
	command<<"0";
	command<<"&sid=13 ";
	command<<"0";
	command<<"&sid=14 ";
	command<<"0";
	command<<"&sid=15 ";
	command<<"0";
	command<<"&sid=16 ";
	command<<"0";
	command<<"&sid=17 ";
	command<<"0";
	command<<"&sid=18 ";
	command<<"0";
	command<<"&sid=19 ";
	command<<"0";
	command<<"&sid=20 ";
	command<<"0";
	command<<"&sid=21 ";
	command<<"0";
	command<<"&sid=22 ";
	command<<"0";
	command<<"&sid=23 ";
	command<<"0";
	command<<"&sid=24 ";
	command<<"0";
	command<<"&sid=25 ";
	command<<"0";
	command<<"&sid=26 ";
	command<<"0";
	command<<"&sid=27 ";
	command<<"0";
	command<<"&sid=28 ";
	command<<"0";
	command<<"&sid=29 ";
	command<<"0";
	command<<"&sid=30 ";
	command<<"0";
	command<<"&sid=31 ";
	command<<"0";
	
	cout<<"command: "<<command.str().c_str()<<endl
	*/
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void setup(){
	
	radio.begin(); //startup the nRF24 module
	radio.setRetries(15,15);
	radio.openWritingPipe(pipes[0]); 	//for Rpi to write on, for SLV1 
	//radio.openWritingPipe(pipes2[0]);	//for Rpi to write on, for SLV2
	radio.openReadingPipe(1,pipes[1]);  //for reading from ARD1, SLV1
	//radio.openReadingPipe(2,pipes2[1]);	//for reading from ARD2, SLV2
	radio.stopListening();
}
/*
int fifo_stuff(){
	
	printf("entered\n");
	fifo_state = mkfifo(fifo_name,0666);
	
	if(fifo_state < 0){ //file already exists
		unlink(fifo_name);//delete the file
	}
	
	//printf("waiting to open file\n");
	//fp = fopen(fifo_name , "w"); //fopen returns null if error happend, else it returns the pointer
	
	if(fp == NULL){
		perror("failed to open fifo file: ");
		unlink(fifo_name);
		exit(1);
	}
	 
	 
	printf("opend file\n");
	sprintf(temp,"%f",lightVoltage);
	fputs("anas",fp);
	fclose(fp);
	printf("close file\n");
	return 0;
	//usleep(3000);
	//unlink(fifo_name);
}
*/


int main(int argc, char* argv[]){
	int return_slv;
	bool success = 0;
	
	setup();
	
	for(int retry_slv = 0 ; retry_slv < 5 ;retry_slv++){
		return_slv = readSLV(retry_slv);
		if(return_slv == 0){//success
			success = 1;
			break;
		}
		delay(700);
	}
	
	if(!success){ //failed to send request or receive readings
		printf("failed to send request or receive readings from SLV1 after 4 reties, Arduino is offline or not responding.\n");
		exit(1);
	}
	
	cout<<"--------------------------------------------"<<endl;
	success = 0;
	
	for(int retry_slv = 0 ; retry_slv < 5 ;retry_slv++){
		return_slv = readSLV2(retry_slv);
		if(return_slv == 0){//success
			success = 1;
			break;
		}
		delay(700);
	}
	
	if(!success){ //failed to send request or receive readings
		printf("failed to send request or receive readings from SLV2 after 4 reties, Arduino is offline or not responding.\n");
		exit(1);
	}
	
	setGUIReadings();
	sendAllToServer();
	
	return 0;
}

