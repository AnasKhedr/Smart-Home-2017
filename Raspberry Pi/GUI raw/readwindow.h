#ifndef READWINDOW_H
#define READWINDOW_H

#include <QDialog>

namespace Ui {
class ReadWindow;
}

class ReadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReadWindow(QWidget *parent = 0);
    ~ReadWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_refresh_clicked();

private:
    Ui::ReadWindow *ui;
};

#endif // READWINDOW_H
