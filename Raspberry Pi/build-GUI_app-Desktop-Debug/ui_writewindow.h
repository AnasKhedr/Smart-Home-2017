/********************************************************************************
** Form generated from reading UI file 'writewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITEWINDOW_H
#define UI_WRITEWINDOW_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WriteWindow
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

    void setupUi(QDialog *WriteWindow)
    {
        if (WriteWindow->objectName().isEmpty())
            WriteWindow->setObjectName(QStringLiteral("WriteWindow"));
        WriteWindow->resize(519, 180);
        layoutWidget = new QWidget(WriteWindow);
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


        retranslateUi(WriteWindow);

        QMetaObject::connectSlotsByName(WriteWindow);
    } // setupUi

    void retranslateUi(QDialog *WriteWindow)
    {
        WriteWindow->setWindowTitle(QApplication::translate("WriteWindow", "Send Reference Window[Room1]", 0));
        label_temp->setText(QApplication::translate("WriteWindow", "Temperature Reference", 0));
        label_celsuis->setText(QApplication::translate("WriteWindow", "C", 0));
        pushButton_send_temp->setText(QApplication::translate("WriteWindow", "Send", 0));
        label_light->setText(QApplication::translate("WriteWindow", "Light Reference", 0));
        label_percentage->setText(QApplication::translate("WriteWindow", "%", 0));
        pushButton_send_light->setText(QApplication::translate("WriteWindow", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class WriteWindow: public Ui_WriteWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITEWINDOW_H
