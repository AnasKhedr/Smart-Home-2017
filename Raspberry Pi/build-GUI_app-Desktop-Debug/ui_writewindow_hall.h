/********************************************************************************
** Form generated from reading UI file 'writewindow_hall.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITEWINDOW_HALL_H
#define UI_WRITEWINDOW_HALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WriteWindow_Hall
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_temp;
    QDial *dial_temp;
    QSpinBox *spinBox_temp;
    QLabel *label_celsuis;
    QPushButton *pushButton_send_temp;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_light;
    QSlider *horizontalSlider_light;
    QSpinBox *spinBox_light;
    QLabel *label_percentage;
    QPushButton *pushButton_send_light;
    QSplitter *splitter_2;
    QLabel *label_2;
    QSlider *tv_state;
    QSplitter *splitter;
    QLabel *label;
    QSlider *door_state;

    void setupUi(QDialog *WriteWindow_Hall)
    {
        if (WriteWindow_Hall->objectName().isEmpty())
            WriteWindow_Hall->setObjectName(QStringLiteral("WriteWindow_Hall"));
        WriteWindow_Hall->resize(519, 221);
        layoutWidget = new QWidget(WriteWindow_Hall);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 501, 121));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_temp = new QLabel(layoutWidget);
        label_temp->setObjectName(QStringLiteral("label_temp"));

        horizontalLayout->addWidget(label_temp);

        dial_temp = new QDial(layoutWidget);
        dial_temp->setObjectName(QStringLiteral("dial_temp"));
        dial_temp->setMinimum(16);
        dial_temp->setMaximum(30);

        horizontalLayout->addWidget(dial_temp);

        spinBox_temp = new QSpinBox(layoutWidget);
        spinBox_temp->setObjectName(QStringLiteral("spinBox_temp"));
        spinBox_temp->setMinimum(16);
        spinBox_temp->setMaximum(30);

        horizontalLayout->addWidget(spinBox_temp);

        label_celsuis = new QLabel(layoutWidget);
        label_celsuis->setObjectName(QStringLiteral("label_celsuis"));
        label_celsuis->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(label_celsuis);

        pushButton_send_temp = new QPushButton(layoutWidget);
        pushButton_send_temp->setObjectName(QStringLiteral("pushButton_send_temp"));

        horizontalLayout->addWidget(pushButton_send_temp);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_light = new QLabel(layoutWidget);
        label_light->setObjectName(QStringLiteral("label_light"));

        horizontalLayout_2->addWidget(label_light);

        horizontalSlider_light = new QSlider(layoutWidget);
        horizontalSlider_light->setObjectName(QStringLiteral("horizontalSlider_light"));
        horizontalSlider_light->setMaximum(100);
        horizontalSlider_light->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_light);

        spinBox_light = new QSpinBox(layoutWidget);
        spinBox_light->setObjectName(QStringLiteral("spinBox_light"));
        spinBox_light->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_light->setMaximum(100);

        horizontalLayout_2->addWidget(spinBox_light);

        label_percentage = new QLabel(layoutWidget);
        label_percentage->setObjectName(QStringLiteral("label_percentage"));

        horizontalLayout_2->addWidget(label_percentage);

        pushButton_send_light = new QPushButton(layoutWidget);
        pushButton_send_light->setObjectName(QStringLiteral("pushButton_send_light"));

        horizontalLayout_2->addWidget(pushButton_send_light);


        verticalLayout->addLayout(horizontalLayout_2);

        splitter_2 = new QSplitter(WriteWindow_Hall);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(330, 170, 122, 26));
        splitter_2->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        splitter_2->addWidget(label_2);
        tv_state = new QSlider(splitter_2);
        tv_state->setObjectName(QStringLiteral("tv_state"));
        tv_state->setMaximum(1);
        tv_state->setOrientation(Qt::Horizontal);
        splitter_2->addWidget(tv_state);
        splitter = new QSplitter(WriteWindow_Hall);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 170, 122, 26));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QStringLiteral("label"));
        splitter->addWidget(label);
        door_state = new QSlider(splitter);
        door_state->setObjectName(QStringLiteral("door_state"));
        door_state->setMaximum(1);
        door_state->setOrientation(Qt::Horizontal);
        splitter->addWidget(door_state);

        retranslateUi(WriteWindow_Hall);

        QMetaObject::connectSlotsByName(WriteWindow_Hall);
    } // setupUi

    void retranslateUi(QDialog *WriteWindow_Hall)
    {
        WriteWindow_Hall->setWindowTitle(QApplication::translate("WriteWindow_Hall", "Send Reference Window[Hall]", 0));
        label_temp->setText(QApplication::translate("WriteWindow_Hall", "Temperature Reference", 0));
        label_celsuis->setText(QApplication::translate("WriteWindow_Hall", "C", 0));
        pushButton_send_temp->setText(QApplication::translate("WriteWindow_Hall", "Send", 0));
        label_light->setText(QApplication::translate("WriteWindow_Hall", "Light Reference", 0));
        label_percentage->setText(QApplication::translate("WriteWindow_Hall", "%", 0));
        pushButton_send_light->setText(QApplication::translate("WriteWindow_Hall", "Send", 0));
        label_2->setText(QApplication::translate("WriteWindow_Hall", "TV", 0));
        label->setText(QApplication::translate("WriteWindow_Hall", "Door", 0));
    } // retranslateUi

};

namespace Ui {
    class WriteWindow_Hall: public Ui_WriteWindow_Hall {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITEWINDOW_HALL_H
