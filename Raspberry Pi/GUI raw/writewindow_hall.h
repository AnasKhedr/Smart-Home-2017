#ifndef WRITEWINDOW_HALL_H
#define WRITEWINDOW_HALL_H

#include <QDialog>

namespace Ui {
class WriteWindow_Hall;
}

class WriteWindow_Hall : public QDialog
{
    Q_OBJECT

public:
    explicit WriteWindow_Hall(QWidget *parent = 0);
    ~WriteWindow_Hall();

private slots:
    void on_pushButton_send_temp_clicked();

    void on_pushButton_send_light_clicked();

    void on_dial_temp_valueChanged(int value);

    void on_spinBox_temp_valueChanged(int arg1);

    void on_horizontalSlider_light_valueChanged(int value);

    void on_spinBox_light_valueChanged(int arg1);

    void on_tv_state_valueChanged(int value);

    void on_door_state_valueChanged(int value);

private:
    Ui::WriteWindow_Hall *ui;
};

#endif // WRITEWINDOW_HALL_H
