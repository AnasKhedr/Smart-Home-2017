#include <string.h> 		//to used strcmp()
#include <fstream>			//to write to text file
#include <iostream>			//to use << and using std

using namespace std;

int count = 0;
bool inQueue = 0;
int num_in_queue;
int time_to_wait = 1;

ifstream myfile;
string str[10];

int main(){
	myfile.open("queue.txt", ios::in); //open test2 to read
    while (getline(myfile, str[count])) { //count number of lines and store them in str
        count++;
    }
	
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
