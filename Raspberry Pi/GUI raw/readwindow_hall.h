#ifndef READWINDOW_HALL_H
#define READWINDOW_HALL_H

#include <QDialog>

namespace Ui {
class ReadWindow_Hall;
}

class ReadWindow_Hall : public QDialog
{
    Q_OBJECT

public:
    explicit ReadWindow_Hall(QWidget *parent = 0);
    ~ReadWindow_Hall();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_refresh_clicked();

private:
    Ui::ReadWindow_Hall *ui;
};

#endif // READWINDOW_HALL_H
