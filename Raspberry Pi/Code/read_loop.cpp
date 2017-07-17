#include <stdlib.h>     //to use system, NULL, EXIT_FAILURE
#include <unistd.h>		//to use sleep

int main(){

	while(1){
		sleep(5);
		system("sudo ./collector_get_readings server");
		system("yes | cp /var/www/html/rpi/guiReadings.txt /home/pi/build-GUI_app-Desktop-Debug/");
	}
}
