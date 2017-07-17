#include <unistd.h> 		//to use usleep()
#include <stdio.h>  		//to use printf()
#include <cstdlib>  		//to use atof , atoi or atol
#include <string.h> 		//to used strcmp()
#include "RF24/RF24.h"		//to use nRF24 module
#include <RF24/printf.h>	//to print wirless detailes
#include <fstream>			//to write to text file
#include <iostream>			//to use cout and <<
#include <ctime>			//to get the time now
#include <sstream>			//to use stringstream

using namespace std;

const uint8_t pipes[][6] = {"MSTR2","SLV2"};

//RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ); //pin numbers are physical
RF24 radio(22,0);																			// Setup for GPIO 22(#15) CE and GPIO8(#24)(CE0) CSN with SPI Speed @ 8Mhz

char Open[40] = "openGarageDoor";															//command to be sent to arduino to open the garage door (agreed upon with arduino)
char Close[40] = "closeGarageDoor";															//command to be sent to arduino to close the garage door (agreed upon with arduino)
char ACK[40] = "ACK";
char NACK[40]= "NACK";
char UC[40]  = "No such command";
char incoming[40];
float onRef;
time_t time_now = time(0);																	//get the calendar time 

int current_time;																			//for the waiting loop (wait to receive data from arduino)
bool timeout;																				//to know if Rpi waited too long for arduino to send and decided that was long enough
bool ret = false;																			//to know if Rpi wrote request to Arduino successfully or not

int num1;
int num2;
int retry = 0;
int garageState;

//guard data
int count = 0;
bool inQueue = 0;
int num_in_queue;
int time_to_wait = 1;
ifstream myfile;																			//for the guard queue file
string str[10];																				//string array of 10 elements to store lines inside the queue file

int id;																						//the id of this request to use the SPI bus (NRF24 module)
stringstream identifier_str;

void remover()																				//this function is used to remove the id of this program from the queue when finished using SPI or NRF24 module 
{
	cout<<"removing myself from queue"<<endl;
    ofstream myfile;																		//setup/make a NULL file to be used for output
    myfile.open("queue.txt", ios::out);														//open "queue.txt" file in the same directory with an input output stream mode of :: out , this mode deletes everything in the file first
    for (int i = 1; i < count; i++) {														//loop all the lines(requests) that were read except the first (id of this program is the first)
        cout << "inputing: " << str[i] << endl;												//print the lines you're inputting in the file.
        myfile << str[i] << endl;															//insert those lines back to the files without this program id
    }
    //myfile<<endl;
    myfile.close();																			//close the file
}


void setup(){
	
	radio.begin();																			//initialise the NRF24 object
	//printf_begin();
	radio.setRetries(15,15);																//set to retry writing (if failed) to max of 15 times with a wait of 15*250us between each retry
	radio.openWritingPipe(pipes[0]);														//open channel on address MSTR2 to write to slave
	radio.openReadingPipe(1,pipes[1]);														//open channel on address SLV2 to read from slave
	//radio.printDetails();
}

int loop(int garageState, int retry){		//garageState 0 means close and 1 means open
	radio.stopListening();																	//stop listening because you're about to talk
	
	ofstream logFile;																		//make an output object
	logFile.open("log_server.log", ios::app);												//open the file named "log_server.log" to write log information to it.
	
	if(retry != 0){																			//if this is not the first try to call this function to send
		if(retry == 4){																		//if this is try number 4, after last try.
			logFile<<"failed to send request to SLV1 after 4 attempts\n";					//print failed to send message to terminal
			logFile<<"runtime: "<<clock()<<endl;											//print the total execution time of this program to log file
			logFile<<"-----------------------------------------\n";
			logFile<<"*****************************************\n";
			logFile.close();																//close log file
			return 1;																		//exit program with error
		}
		logFile<<"Reattempting to send request to SLV1. attempt number: "<<retry<<endl;		//if not last try print try number in log file
		cout<<"Reattempting to send request to SLV1. attempt number: "<<retry<<endl;		//print the try number to terminal
	}
	else{																					//if this is the first try
		logFile<<ctime(&time_now);															//print the calendar time in log file
		logFile<<"*****************************************\n";
	}
	
	printf("server sent garage State: %d\n",garageState);									//print the garage state you'll sent, open or close to terminal
	logFile<<"server sent garage State: "<<garageState<<endl;								//print the garage state you'll sent, open or close to log
	
	//write to arduino
	if(garageState == 0){ //0 measns close the door											//if user wants to close door
		printf("sending mode: %s\n",Close);
		logFile<<"sending mode: "<<Close<<endl;												//print to log file that user wants to close door
		ret = radio.write(&Close,sizeof(char[40]));											//send close command to arduino
		radio.startListening();																//start listening for incoming message
	}
	else if(garageState == 1){ //1 means open the garage									//if user wants to open garage door
		printf("sending mode: %s\n",Open);
		logFile<<"sending mode: "<<Open<<endl;												//print to log file that user wants to open door
		ret = radio.write(&Open,sizeof(char[40]));											//send open command to arduino
		radio.startListening();																//start listening for incoming message
	}
	
	if(!ret){  																				//if Rpi failed to send request to arduino
		printf("failed to send request to arduino\n");										
		logFile<<"failed to send request to arduino\n";										//print in log file that Rpi failed to send request to arduino
		logFile<<"runtime: "<<clock()<<endl;												//print in log execution time of this program so far
		logFile<<"-----------------------------------------\n";
		logFile.close();																	//close log file
		return 1;																			//exit loop with error flag
	}
	
	
	//receive from arduino
	timeout = false;																		//reset timeout
	current_time = millis();																//get time from begining of execution in ms
	cout<<"entered waiting loop for 50 seconds\n";
	while(!radio.available()){																//wait for 50 seconds for arduino finish execution command and send ACK or NACK
		if(millis()-current_time > 50000){ 													//wait for 50 seconds
			printf("50 second passed\n");													//for debugging
			timeout = true;																	//if 50 second passed without ACK or NACK then set timeout
			break;
		}
	}
	cout<<"exited waiting loop\n";															//for debugging
	
	if(timeout){																			//if timeout happend then print what happend to terminal and log file
		printf("timeout, failed to receive.\n");
		logFile<<"timeout, failed to receive.\n";
		radio.read(&incoming,sizeof(char[40]));
		printf("in buffer: %s\n",incoming);
		logFile<<"in buffer: "<<incoming<<endl;
		logFile<<"runtime: "<<clock()<<endl;
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
	}
	
	else{
		while(radio.available()){
			radio.read(&incoming,sizeof(char[40])); // arduino should send us ACK if everything is ok NACK if it failed
		}
		printf("incoming: %s\n",incoming);
		logFile<<"incoming: "<<incoming<<endl;
		
		num1 = strcmp(incoming , ACK);														//if the incomming is ACK
		if(num1 != 0){																		//if incoming is not ACK
			num2 = strcmp(incoming , UC);													//check to see if it's unknowen command
			if(num2 == 0){																	//if it's unknown command
				printf("recived \"unknown command\"\n");
				logFile<<"recived \"unknown command\"\n";
			}
			else if(strcmp(incoming, NACK) == 0){											//if it's NACK
				printf("recived \"NACK\", Arduino failed to complete request\n");
				logFile<<"recived \"NACK\", Arduino failed to complete request\n";
			}
			else{																			//if it's something else
				printf("unexpected respond: %s\n",incoming);
				logFile<<"unexpected respond: "<<incoming<<endl;
			}
		}
		
	}

	logFile<<"runtime: "<<clock()<<endl;
	logFile<<"-----------------------------------------\n";
	logFile<<"*****************************************\n";
	logFile.close();
	return 0;
	
}


int main(int argc, char ** argv){
	int success=0;
	int return_slv;
	
	if(argc < 2){
		printf("wrong command.\ncommand should be the following: sudo ./write_door <door state>\n");
		printf("door state is 0 for close and 1 for open.\n");
		//exit(1);
		return 1;
	}
	
	srand(time(NULL));						//set the seed for random (it uses psudorandom), not setting the seed will always gives you the same number
	id = rand();							//generate a random number
	identifier_str<<"write_door"<<id;
	//identifier_str.str("");		//for debugging
	//identifier_str<<"write_door"; //for debugging
	
	start:
	for(int i =0; i<10; i++){
		str[i] = "";
	}
	count = 0;
    myfile.open("queue.txt", ios::in); //open test2 to read
	
    while (getline(myfile, str[count])) { //count number of lines and store them in str
        count++;
    }
	
	myfile.close();
    cout << "count is: " << count << endl;

    if (count == 0) { //if file is empty
        cout << "file is empty" << endl;
        ofstream outfile;
        outfile.open("queue.txt", ios::app); //open file for writing
        outfile << identifier_str.str().c_str()<< endl; //place yourself in the queue to tell every one else you're using spi
        //fputs(str[1],outfile);
        outfile.close();
        //do what you want
        garageState = atoi(argv[1]);
		setup();
		
		for(int retry_number = 0 ; retry_number < 5 ;retry_number++){
			return_slv = loop(garageState , retry_number);
			if(return_slv == 0){//success
				success = 1;
				break;
			}
			delay(700);
		}
		
		if(!success){ //failed to send request or receive readings
			printf("failed to send request or receive ACK from SLV2 after 4 reties, Arduino is offline or not responding.\n");
			remover();
			return 1;
			//exit(1);
		}
        //remove yourself from queue
        remover();
    }
    else { //if file is not empty
        for (int i = 1; i <= count; i++) {
            //cout<<"str is: "<<str[i-1]<<endl;
            if (strcmp(identifier_str.str().c_str(), str[i-1].c_str()) == 0) { //search for yourself in the queue
                cout << "number in queue is: " << i-1 << endl;
                num_in_queue = i-1;
                cout << "i am in the queue" << endl;
                inQueue = 1;
                break;
            }
        }


        if (!inQueue) { //if you're not in the queue
            ofstream outfile;
            outfile.open("queue.txt", ios::app); //open file for writing
            outfile << identifier_str.str().c_str()<< endl; //place yourself in the queue to tell every one else you're using spi
            outfile.close();
            cout << "i am NOT in the queue" << endl;
            goto start;
        }
        else { //if you're in the queue then check if it's your turn
            if (num_in_queue == 0) {
                cout << "my turn" << endl;
                //do what you want
                garageState = atoi(argv[1]);
				setup();
				
				for(int retry_number = 0 ; retry_number < 5 ;retry_number++){
					return_slv = loop(garageState , retry_number);
					if(return_slv == 0){//success
						success = 1;
						break;
					}
					delay(700);
				}
				
				if(!success){ //failed to send request or receive readings
					printf("failed to send request or receive ACK from SLV2 after 4 reties, Arduino is offline or not responding.\n");
					remover();
					return 1;
					//exit(1);
				}
                //remove yourself from queue
                remover();
            }
            else {
                cout << "not my turn yet" << endl;
                if (time_to_wait > 20) {
                    cout << "waited too long and still not my turn!" << endl;
                    //you should probably delete your turn in the queue
                    system("sudo rm queue.txt");
                    //remover();
                    return 1;
                }
                else {
                    sleep(time_to_wait);
                    time_to_wait *= 2;
                    printf("waiting %d\n", time_to_wait);
                    goto start;
                }
                //wait for some time then check again to see if it's your turn
                //Sleep(6000);
                //remove yourself from queue
                //remover();
            }
        }
    }
	
	//----------------------------------------------------------
	
	return 0;
}
