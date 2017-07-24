#ifndef WRITEWINDOW_H
#define WRITEWINDOW_H

#include <QDialog>

namespace Ui {
class WriteWindow;
}

class WriteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WriteWindow(QWidget *parent = 0);
    ~WriteWindow();

private slots:
    void on_dial_temp_valueChanged(int value);

    void on_spinBox_temp_valueChanged(int arg1);

    void on_horizontalSlider_light_valueChanged(int value);

    void on_spinBox_light_valueChanged(int arg1);

    void on_pushButton_send_light_clicked();

    void on_pushButton_send_temp_clicked();

private:
    Ui::WriteWindow *ui;
};

#endif // WRITEWINDOW_H
