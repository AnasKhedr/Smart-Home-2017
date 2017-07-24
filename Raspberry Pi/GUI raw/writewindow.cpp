#include "writewindow.h"
#include "ui_writewindow.h"
#include <sstream>

WriteWindow::WriteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteWindow)
{
    ui->setupUi(this);
}

WriteWindow::~WriteWindow()
{
    delete ui;
}

void WriteWindow::on_dial_temp_valueChanged(int value)
{
    ui->spinBox_temp->setValue(value);
}

void WriteWindow::on_spinBox_temp_valueChanged(int arg1)
{
    ui->dial_temp->setValue(arg1);
}

void WriteWindow::on_horizontalSlider_light_valueChanged(int value)
{
    ui->spinBox_light->setValue(value);
}

void WriteWindow::on_spinBox_light_valueChanged(int arg1)
{
    ui->horizontalSlider_light->setValue(arg1);
}

void WriteWindow::on_pushButton_send_light_clicked()
{
    std::stringstream stream;
    int val_percentag = ui->spinBox_light->value();                                                                 //get the value in the spin Box of light
    float val_voltage = val_percentag * (5.0/100.0);                                                                //the light is represented in this GUI as percentage but the program that called arduino takes the parameter as voltage
    stream << "cd /var/www/html/rpi/ && sudo ./collector_light room1 "<<val_voltage;                                //this is pushing the command to a string that will be then sent to the terminal(using system()) to be executed. the first command is changing the current directory to the directory of the program then && to indicate there is another command which calls the write program with the reference we want
    system(stream.str().c_str());                                                                                   //first convert the stream to string [.str()] then convert the string to character array (char[]) [c_str()] because system() only take char[] as a parameter
}

void WriteWindow::on_pushButton_send_temp_clicked()
{
    std::stringstream stream;
    float val_celsius = ui->spinBox_temp->value();
    stream<< "cd /var/www/html/rpi/ && sudo ./collector_temp room1 "<<val_celsius;
    system(stream.str().c_str());
}
