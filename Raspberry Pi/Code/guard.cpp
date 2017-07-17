#include <iostream>			//to use << and using std
#include <fstream>			//to write to text file
#include <ctime>			//to get the time now
#include <stdio.h>			//to use printf()
#include <string.h>			//to used strcmp()
#include <unistd.h>			//to use usleep()
#include <cstdlib> 			//to use system, NULL, EXIT_FAILURE
#include <stdlib.h>			//header of cstdlib (update: unnecessary include)
#include <sstream>			//to use string stream

using namespace std;

//guard data
int count = 0;
bool inQueue = 0;
int num_in_queue;
int time_to_wait = 1;
ifstream myfile;
string str[10];

int id;
stringstream identifier_str;
bool nRF_state;

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

int main()
{
	srand(time(NULL));						//set the seed for random (it uses psudorandom), not setting the seed will always gives you the same number
	id = rand();							//generate a random number
	identifier_str<<"sensor x"<<id;
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
        outfile.open("queue.txt", ios::app); 			//open file for writing
        outfile << identifier_str.str().c_str()<< endl; //place yourself in the queue to tell every one else you're using spi
        //fputs(str[1],outfile);
        outfile.close();
        //do what you want
        sleep(6);
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
                sleep(6);
                //remove yourself from queue
                remover();
            }
            else {
                cout << "not my turn yet" << endl;
                if (time_to_wait > 20) {
                    cout << "waited too long and still not my turn!" << endl;
                    //you should probably delete your turn in the queue
					//system("sudo rm queue.txt");
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
    cout << "exiting" << endl;
    return 0;
}
