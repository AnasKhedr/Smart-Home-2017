#include "writewindow_hall.h"
#include "ui_writewindow_hall.h"
#include <sstream>

WriteWindow_Hall::WriteWindow_Hall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteWindow_Hall)
{
    ui->setupUi(this);
}

WriteWindow_Hall::~WriteWindow_Hall()
{
    delete ui;
}

void WriteWindow_Hall::on_pushButton_send_temp_clicked()
{
    std::stringstream stream;
    float val_celsius = ui->spinBox_temp->value();
    stream<< "cd /var/www/html/rpi/ && sudo ./collector_temp hall "<<val_celsius;
    system(stream.str().c_str());
}

void WriteWindow_Hall::on_pushButton_send_light_clicked()
{
    std::stringstream stream;
    int val_percentag = ui->spinBox_light->value();                                                                 //get the value in the spin Box of light
    float val_voltage = val_percentag * (5.0/100.0);                                                                //the light is represented in this GUI as percentage but the program that called arduino takes the parameter as voltage
    stream << "cd /var/www/html/rpi/ && sudo ./collector_light hall "<<val_voltage;     //this is pushing the command to a string that will be then sent to the terminal(using system()) to be executed. the first command is changing the current directory to the directory of the program then && to indicate there is another command which calls the write program with the reference we want
    system(stream.str().c_str());
}

void WriteWindow_Hall::on_dial_temp_valueChanged(int value)
{
    ui->spinBox_temp->setValue(value);
}

void WriteWindow_Hall::on_spinBox_temp_valueChanged(int arg1)
{
    ui->dial_temp->setValue(arg1);
}

void WriteWindow_Hall::on_horizontalSlider_light_valueChanged(int value)
{
    ui->spinBox_light->setValue(value);
}

void WriteWindow_Hall::on_spinBox_light_valueChanged(int arg1)
{
    ui->horizontalSlider_light->setValue(arg1);
}

void WriteWindow_Hall::on_tv_state_valueChanged(int value)
{
    std::stringstream stream;
    stream << "cd /var/www/html/rpi/ && sudo ./write_tv "<<value;
    system(stream.str().c_str());
}

void WriteWindow_Hall::on_door_state_valueChanged(int value)
{
    std::stringstream stream;
    stream << "cd /var/www/html/rpi/ && sudo ./write_door "<<value;
    system(stream.str().c_str());
}
