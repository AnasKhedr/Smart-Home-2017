#include <unistd.h> 		//to use usleep()
#include <stdio.h>  		//to use printf()
#include <cstdlib>  		//to use atof , atoi or atol also use rand()
#include <string.h> 		//to used strcmp()
#include "RF24/RF24.h"		//to use nRF24 module
#include <RF24/printf.h>	//to print wirless detailes
#include <fstream>			//to write to text file
#include <iostream>			//to use cout and <<
#include <ctime>			//to get the time now
#include <unistd.h>			//to use sleep()
#include <sstream>			//to use stringstream
//#include <math.h>

using namespace std;

const uint8_t pipes[][6] = {"MSTR2","SLV2"};

// Setup for GPIO 22(#15) CE and CE0 (#24) CSN with SPI Speed @ 8Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ); //pin numbers are physical
RF24 radio(22,0);

char Open[40] = "tvOn";
char Close[40] = "tvOff";
char ACK[40] = "ACK";
//char NACK[40]= "NACK";				//not used
char UC[40]  = "No such command";
char incoming[40];
float onRef;
time_t time_now = time(0);

int current_time;
bool timeout;
bool ret = false;			//to know if Rpi wrote reqest to arduino successfully or not

int num1;
int num2;
int retry = 0;
int tvState;

//guard data
int count = 0;
bool inQueue = 0;
int num_in_queue;
int time_to_wait = 1;
//int identifier = rand();
ifstream myfile;
string str[10];

int id;
stringstream identifier_str;

void remover()
{
	cout<<"removing myself from queue"<<endl;
    ofstream myfile;
    myfile.open("queue.txt", ios::out);
    for (int i = 1; i < count; i++) {
        cout << "inputing: " << str[i] << endl;
        myfile << str[i] << endl;
    }
    //myfile<<endl;
    myfile.close();
}

void setup(){
	
	radio.begin();
	//printf_begin();
	radio.setRetries(15,15);
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);
	//radio.printDetails();
}

int loop(int tvState, int retry){
	radio.stopListening();
	//sleep(1); //for debugging
	ofstream logFile;
	logFile.open("log_server.log", ios::app);
	
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
	
	printf("server sent tv State: %d\n",tvState);
	logFile<<"server sent tv State: "<<tvState<<endl;
	
	//write to arduino
	if(tvState == 0){ //0 measns close the tv
		printf("sending mode: %s\n",Close);
		logFile<<"sending mode: "<<Close<<endl;
		ret = radio.write(&Close,sizeof(char[40]));
		radio.startListening();
	}
	else if(tvState == 1){ //1 means open the tv
		printf("sending mode: %s\n",Open);
		logFile<<"sending mode: "<<Open<<endl;
		ret = radio.write(&Open,sizeof(char[40]));
		radio.startListening();
	}
	
	if(!ret){  					//if Rpi failed to send request to arduino
		printf("failed to send request to arduino\n");
		logFile<<"failed to send request to arduino\n";
		logFile<<"runtime: "<<clock()<<endl;
		logFile<<"-----------------------------------------\n";
		logFile.close();
		return 1;
	}
	
	
	//receive from arduino
	timeout = false;
	current_time = millis();
	while(!radio.available()){
		if(millis()-current_time > 400){ //wait for 400ms
			timeout = true;
			break;
		}
	}
	
	if(timeout){
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
			radio.read(&incoming,sizeof(char[40])); // arduino should send us ACK if everything
		}
		printf("incoming: %s\n",incoming);
		logFile<<"incoming: "<<incoming<<endl;
		
		num1 = strcmp(incoming , ACK);
		if(num1 != 0){
			num2 = strcmp(incoming , UC);
			if(num2 == 0){
				printf("recived \"unknown command\"\n");
				logFile<<"recived \"unknown command\"\n";
			}
			else{
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
		printf("wrong command.\ncommand should be the following: sudo ./write_tv <tv state>\n");
		printf("tv state is 0 for close and 1 for open.\n");
		//exit(1);
		return 1;
	}
	
	srand(time(NULL));						//set the seed for random (it uses psudorandom), not setting the seed will always gives you the same number
	id = rand();							//generate a random number
	identifier_str<<"write_tv"<<id;
	//identifier_str.str("");		//for debugging
	//identifier_str<<"write_tv"; //for debugging
	
	start:
	for(int i =0; i<10; i++){
		str[i] = "";
	}
	count = 0;
	
    myfile.open("queue.txt", ios::in); //open test2 to read
    while (getline(myfile, str[count])) { //count number of lines and store them in str
        count++;
    }

	cout<<"my id: "<<identifier_str.str()<<endl;
    cout << "count is: " << count << endl;

    if (count == 0) { //if file is empty
        cout << "file is empty" << endl;
        myfile.close();
        ofstream outfile;
        outfile.open("queue.txt", ios::app); //open file for writing
        outfile << identifier_str.str().c_str() << endl; //place yourself in the queue to tell every one else you're using spi
        //fputs(str[1],outfile);
        outfile.close();
        //do what you want
        tvState = atoi(argv[1]);
		setup();
		
		for(int retry_number = 0 ; retry_number < 5 ;retry_number++){
			return_slv = loop(tvState , retry_number);
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
            if (strcmp(identifier_str.str().c_str(), str[i - 1].c_str()) == 0) { //search for yourself in the queue
                cout << "number in queue is: " << i - 1 << endl;
                num_in_queue = i - 1;
                cout << "i am in the queue" << endl;
                inQueue = 1;
                break;
            }
        }

        myfile.close();

        if (!inQueue) { //if you're not in the queue
            ofstream outfile;
            outfile.open("queue.txt", ios::app); //open file for writing
            outfile << identifier_str.str().c_str() << endl; //place yourself in the queue to tell every one else you're using spi
            outfile.close();
            cout << "i am NOT in the queue" << endl;
            goto start;
        }
        else { //if you're in the queue then check if it's your turn
            if (num_in_queue == 0) {
                cout << "my turn" << endl;
                //do what you want
                tvState = atoi(argv[1]);
				setup();
				
				for(int retry_number = 0 ; retry_number < 5 ;retry_number++){
					return_slv = loop(tvState , retry_number);
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
	
	
	//----------------------------------------------------------------------------------
	
	return 0;
}
