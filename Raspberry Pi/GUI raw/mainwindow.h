#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "readwindow.h"
#include "writewindow.h"
#include "logwindow.h"
#include "readwindow_hall.h"
#include "writewindow_hall.h"

#include <QString>

#include <sstream>
#include <unistd.h> 		//to use usleep()
#include <stdio.h>  		//to use printf()
#include <cstdlib>  		//to use atof , atoi or atol
#include <string.h> 		//to used strcmp()

#include <fstream>			//to write to text file
#include <iostream>			//to use << and using std
#include <ctime>			//to get the time now

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_write_clicked();

    void on_pushButton_read_clicked();

    void on_pushButton_log_clicked();

private:
    Ui::MainWindow *ui;
    ReadWindow *readWindow;
    ReadWindow_Hall *readWindow_hall;
    WriteWindow *writeWindow;
    WriteWindow_Hall *writeWindow_hall;
    LogWindow *logWindow;
};

#endif // MAINWINDOW_H
