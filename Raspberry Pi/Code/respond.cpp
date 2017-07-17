/*
 * respond as in respond to server call
 * respond program is designed to call other program using system()
 * respond is only designed for handling server calls
*/

#include <iostream>		//to use cout
#include <stdio.h>		//to use printf()
#include <string.h>		//to used strcmp()
#include <sstream>		//to use stringstream
#include <stdlib.h>     //to use system, NULL, EXIT_FAILURE

using namespace std; // for stringstream

int ret;
float light_ref_percentage;
float light_ref_volt;
//light sid = 1
//temp sid = 3

int main(int argc, char *argv[]){
	if(argc < 3){															//the program must be always is the same format: 1: respond , 2: sid , 3: state , 4: val (optional) so if it's less than 3 arguments then it was called the wrong way
		printf("error in paragmeters.\nProgram must be called as follows: respond <sid> <state> <<val>>\n"); //state is to open or close
		return 1;
		//exit(1);
	}
	
	
	cout<<"--------------------------------------"<<endl;
	stringstream command;
	//sid stands for sensor id, you can find them in sensors.xlsx file
	//server program will call this program like thins: sudo ./server <sid> <state> <value> so map every sensor to the program that we made that control this sensor
	if(strcmp(argv[1],"3")== 0){								 			//for temp1 control, for hall
		if(strcmp(argv[2],"0")==0 && argc == 4){		   					//argv[2] is the state so if it is 0 then it's disabled in light or temperature then no need to forward it to arduino
			printf("enable is 0 for temperature, sid= %s\nignoring command.\n",argv[1]);
			return 0;														//exit the program with success, you should not execute the command is enabled is not set
		}
		
		printf("sid = 3 (temp1 in hall -living-)\n");
		cout<<"sudo ./collector_temp hall "<< argv[3]<<endl					//print the command to terminal
		command<<"sudo ./collector_temp hall "<< argv[3];					//construct the command and save it in a string stream called command to call it later
		ret = system(command.str().c_str());								//call the command that we constructed
		command.str("");													//empty the string stream named command that we used to call the command we constructed
		printf("system call return = %d\n",ret);							//print the return of the system call system(), used for debugging and to know if the program we called was not executed correctly
	}
	else if(strcmp(argv[1],"1")== 0){ 										//for light1 control, in hall
		if(strcmp(argv[2],"0")==0 && argc == 4){							//argv[2] is the state so if it is 0 then it's disabled, no need to forward it to arduino
			printf("enable is 0 for light, sid= %s\nignoring command.\n",argv[1]);
			return 0;														//exit the program with success, you should not execute the command is enabled is not set
		}
		
		light_ref_percentage = atof(argv[3]);								//convert the reference we recived to float
		light_ref_volt = light_ref_percentage*(5.0/100.0);					//convert the reference from percentage to volt (website and app use percentage to determine reference while Arduino uses the volt it reads)
		
		printf("sid = 1 light1 (in hall -living-)\n");			
		cout<<"sudo ./collector_light hall "<< light_ref_volt<<endl;		//print the command to terminal
		command<<"sudo ./collector_light hall "<< light_ref_volt;			//construct the command and save it in a string stream called command to call it later
		ret = system(command.str().c_str());								//call the command that we constructed
		command.str("");													//empty the string stream named command that we used to call the command we constructed
		printf("system call return = %d\n",ret);							//print the return of the system call system(), used for debugging and to know if the program we called was not executed correctly
	}
	else if(strcmp(argv[1],"6")== 0){ 										//tv1, in hall
		printf("sid = 6 tv1 (in hall -living-)\n");
		cout<<"sudo ./write_tv "<< argv[2]<<endl;							//print the command to terminal
		command<<"sudo ./write_tv "<< argv[2];								//construct the command and save it in a string stream called command to call it later
		ret = system(command.str().c_str());								//call the command that we constructed
		command.str("");													//empty the string stream named command that we used to call the command we constructed
		printf("system call return = %d\n",ret);							//print the return of the system call system(), used for debugging and to know if the program we called was not executed correctly
	}
	else if(strcmp(argv[1],"7")== 0){										//light2, in room1 -bedroom1-
		if(strcmp(argv[2],"0")==0 && argc == 4){							//argv[2] is the state so if it is 0 then it's disabled in light or temperature then no need to forward it to arduino
			printf("enable is 0 for light, sid= %s\nignoring command.\n",argv[1]);
			return 0;														//exit the program with success, you should not execute the command is enabled is not set
		}
		
		light_ref_percentage = atof(argv[3]);								//convert the reference we recived to float
		light_ref_volt = light_ref_percentage*(5.0/100.0);					//convert the reference from percentage to volt (website and app use percentage to determine reference while Arduino uses the volt it reads)
		
		printf("sid = 7 light2 (in room1 -bedroom1-)\n");
		cout<<"sudo ./collector_light room1 "<< light_ref_volt<<endl;		//print the command to terminal
		command<<"sudo ./collector_light room1 "<< light_ref_volt;			//construct the command and save it in a string stream called command to call it later
		ret = system(command.str().c_str());								//call the command that we constructed
		command.str("");													//empty the string stream named command that we used to call the command we constructed
		printf("system call return = %d\n",ret);							//print the return of the system call system(), used for debugging and to know if the program we called was not executed correctly
	}
	else if(strcmp(argv[1],"15")== 0){										//garage door, in hall -garage-
		printf("sid = 15 garage door (in hall -garage-)\n");
		cout<<"sudo ./write_door "<< argv[2]<<endl;							//print the command to terminal
		command<<"sudo ./write_door "<< argv[2];							//construct the command and save it in a string stream called command to call it later
		ret = system(command.str().c_str());								//call the command that we constructed
		command.str("");													//empty the string stream named command that we used to call the command we constructed
		printf("system call return = %d\n",ret);							//print the return of the system call system(), used for debugging and to know if the program we called was not executed correctly
	}
	else if(strcmp(argv[1],"18")== 0){  									//for temp_4, room1 -bedroom1-
		if(strcmp(argv[2],"0")==0 && argc == 4){							//argv[2] is the state so if it is 0 then it's disabled in light or temperature then no need to forward it to arduino
			printf("enable is 0 for temperature or light sid= %s\nignoring command.\n",argv[1]);
			return 0;														//exit the program with success, you should not execute the command is enabled is not set
		}
		
		printf("sid = 18 temp_4 (in room1 -bedroom1-)\n");
		cout<<"sudo ./collector_temp room1 "<< argv[3]<<endl;				//print the command to terminal
		command<<"sudo ./collector_temp room1 "<< argv[3];					//construct the command and save it in a string stream called command to call it later
		ret = system(command.str().c_str());								//call the command that we constructed
		command.str("");													//empty the string stream named command that we used to call the command we constructed
		printf("system call return = %d\n",ret);							//print the return of the system call system(), used for debugging and to know if the program we called was not executed correctly
	}
	else{
		printf("undefined sensor: %s\n",argv[1]);							//if the sid is not one of the above then print an error message stating that sensor is not defined or used in Arduino.
		cout<<"--------------------------------------"<<endl;
		return 1;															//exit with error flag, server sent an id for a sensor that we didn't use.
	}
	cout<<"--------------------------------------"<<endl;
	return 0;
}
