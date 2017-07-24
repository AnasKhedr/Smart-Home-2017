#include "readwindow.h"
#include "ui_readwindow.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <string>
#include <QTextStream>

using namespace  std ;
/*
int fifo_state;
FILE *fp;
char fifo_name[] = "readings_file";
char read_buffer[40];
char temp[40];
*/


ifstream data_file;
//QFile data_file("/home/pi/Desktop/data_on_zero/New/'C++ GPIO'/nRF24/guiReadings.txt");

ReadWindow::ReadWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadWindow)
{
    ui->setupUi(this);

//    QFile data_file("/home/pi/Desktop/data_on_zero/New/'C++ GPIO'/nRF24/guiReadings.txt");
//    data_file.open(QIODevice::ReadOnly | QIODevice::Text);

}

ReadWindow::~ReadWindow()
{
    delete ui;
}

void ReadWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->pushButton_refresh->setEnabled(false);
/*
//        printf("entered condition for change index to 1\n");
//        system("cd /home/pi/Desktop/data_on_zero/New/'C++ GPIO'/nRF24");
//        fifo_state = mkfifo(fifo_name,0666);

////        if(fifo_state < 0){ //file already exists
////            unlink(fifo_name);//delete the file
////        }

//        fp = fopen(fifo_name , "r"); //fopen returns null if error happend, else it returns the pointer


////        while(1){
//            if(ui->comboBox->currentIndex() != 1){
//                printf("exiting for if\n");
//                fclose(fp);
//                unlink(fifo_name);
//                //break;
//            }

//            printf("getting data from buffer\n");
//            fgets(read_buffer,40,fp);
//            printf("data: %s\n",read_buffer);
//            fclose(fp);
//            ui->label_photo_resistor_volt->setText(read_buffer);

////        }
*/
    }
    else if(index == 1){
        ui->pushButton_refresh->setEnabled(true);
    }
}

void ReadWindow::on_pushButton_refresh_clicked()
{
    /*
    //system("cat /home/pi/Desktop/data_on_zero/New/'C++ GPIO'/nRF24/guiReadings.txt");
    //system("cd /home/pi/Desktop/data_on_zero/New/'C++ GPIO'/nRF24/");
    //ifstream data_file;
//    QFile data_file("guiReadings.txt");
//    if(!data_file.open(QIODevice::ReadOnly | QIODevice::Text))
//        cout<<"fialed to open\n";
//    QTextStream stream(&data_file);
    //stream << "something";

//    while(!stream.atEnd()){
//        QString line =stream.readLine();
//        ui->label_photo_resistor_volt->setText(line);
//    }
*/
    //system("cd /var/www/html/rpi/ && sudo ./collector_get_readings");
    system("yes | cp /var/www/html/rpi/guiReadings.txt /home/pi/build-GUI_app-Desktop-Debug/");
    data_file.open("guiReadings.txt",ios::in | ios::out);

    string line_;
    QString line;
    for(int linenum = 0; linenum <= 11 ; linenum ++){
        getline(data_file,line_);
        line = QString::fromStdString(line_); //convert string to Qstring cuz label only accepts Qsting (stupid rule qt!!)
        //cout<<line_<<endl;
        switch (linenum){
        case 0:
            ui->label_photo_resistor_volt->setText(line);
            break;
        case 1:
            ui->label_photo_resistor_ref->setText(line);

            break;
        case 2:
            ui->label_gas_volt->setText(line);

            break;
        case 3:
            ui->label_light_state->setText(line);

            break;
        case 4:
            ui->label_room_temp->setText(line);

            break;
        case 5:
            ui->label_temp_ref->setText(line);

            break;
        case 6:
            ui->label_fan_state->setText(line);

            break;
        case 7:
            ui->label_heater_state->setText(line);

            break;
        case 8:
            ui->label_gas_danger_level->setText(line);

            break;
        case 9:
            ui->label_fire_volt->setText(line);

            break;
        case 10:
            ui->label_fire_state->setText(line);

            break;
        case 11:
            ui->label_water_state->setText(line);

            break;
        }

    }
    data_file.close();
}
