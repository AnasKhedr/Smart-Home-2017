#include "readwindow_hall.h"
#include "ui_readwindow_hall.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <string>
#include <QTextStream>

using namespace  std ;

ifstream data_file_h;

ReadWindow_Hall::ReadWindow_Hall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadWindow_Hall)
{
    ui->setupUi(this);
}

ReadWindow_Hall::~ReadWindow_Hall()
{
    delete ui;
}

void ReadWindow_Hall::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->pushButton_refresh->setEnabled(false);
    }
    else if(index == 1){
        ui->pushButton_refresh->setEnabled(true);
    }
}

void ReadWindow_Hall::on_pushButton_refresh_clicked()
{
    //system("cd /var/www/html/rpi/ && sudo ./collector_get_readings");
    system("yes | cp /var/www/html/rpi/guiReadings2.txt /home/pi/build-GUI_app-Desktop-Debug/");
    data_file_h.open("guiReadings2.txt",ios::in | ios::out); //open hall readings file

    string line_;
    QString line;
    for(int linenum = 0; linenum <= 11 ; linenum ++){
        getline(data_file_h,line_);
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
            ui->label_light_state->setText(line);

            break;
        case 3:
            ui->label_room_temp->setText(line);

            break;
        case 4:
            ui->label_temp_ref->setText(line);

            break;
        case 5:
            ui->label_fan_state->setText(line);

            break;
        case 6:
            ui->label_heater_state->setText(line);

            break;
        case 7:
            ui->label_pir_state->setText(line);

            break;
        case 8:
            ui->label_garage_state->setText(line);

            break;
        case 9:
            ui->label_tv_state->setText(line);

            break;
        case 10:
            ui->label_humidity_outside_house->setText(line);

            break;
        case 11:
            ui->label_temperature_outside_house->setText(line);

            break;
        }

    }
    data_file_h.close();
}
