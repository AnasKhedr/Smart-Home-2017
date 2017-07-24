#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //this->setWindowIcon("/home/pi/build-GUI_app-Desktop-Debug/gui_app_icon.ico");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_exit_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_write_clicked()
{
    int room = ui->comboBox->currentIndex();
    if(room == 0){//room 1
        writeWindow = new WriteWindow;
        writeWindow->show();
    }
    else if(room == 1){//hall
        writeWindow_hall = new WriteWindow_Hall;
        writeWindow_hall->show();
    }
}

void MainWindow::on_pushButton_read_clicked()
{
    int room = ui->comboBox->currentIndex();
    if(room == 0){//room 1
        readWindow = new ReadWindow;
        readWindow->show();
    }
    else if(room == 1){//hall
        readWindow_hall = new ReadWindow_Hall;
        readWindow_hall->show();
    }

}

void MainWindow::on_pushButton_log_clicked()
{

     logWindow = new LogWindow;
     logWindow->show();

}
