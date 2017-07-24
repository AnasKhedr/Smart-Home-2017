/********************************************************************************
** Form generated from reading UI file 'readwindow_hall.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READWINDOW_HALL_H
#define UI_READWINDOW_HALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReadWindow_Hall
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_35;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_photo_resistor_volt;
    QLabel *label_photo_resistor_ref;
    QLabel *label_light_state;
    QLabel *label_room_temp;
    QLabel *label_temp_ref;
    QLabel *label_fan_state;
    QLabel *label_heater_state;
    QLabel *label_pir_state;
    QLabel *label_garage_state;
    QLabel *label_tv_state;
    QLabel *label_humidity_outside_house;
    QLabel *label_temperature_outside_house;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_39;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_30;
    QLabel *label_29;
    QLabel *label_23;
    QLabel *label_33;
    QLabel *label_v_gas;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_34;
    QLabel *label_40;
    QFrame *line;
    QPushButton *pushButton_refresh;

    void setupUi(QDialog *ReadWindow_Hall)
    {
        if (ReadWindow_Hall->objectName().isEmpty())
            ReadWindow_Hall->setObjectName(QStringLiteral("ReadWindow_Hall"));
        ReadWindow_Hall->resize(435, 489);
        layoutWidget = new QWidget(ReadWindow_Hall);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 11, 282, 324));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout->addWidget(label_10);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout->addWidget(label_11);

        label_35 = new QLabel(layoutWidget);
        label_35->setObjectName(QStringLiteral("label_35"));

        verticalLayout->addWidget(label_35);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_photo_resistor_volt = new QLabel(layoutWidget);
        label_photo_resistor_volt->setObjectName(QStringLiteral("label_photo_resistor_volt"));

        verticalLayout_2->addWidget(label_photo_resistor_volt);

        label_photo_resistor_ref = new QLabel(layoutWidget);
        label_photo_resistor_ref->setObjectName(QStringLiteral("label_photo_resistor_ref"));

        verticalLayout_2->addWidget(label_photo_resistor_ref);

        label_light_state = new QLabel(layoutWidget);
        label_light_state->setObjectName(QStringLiteral("label_light_state"));

        verticalLayout_2->addWidget(label_light_state);

        label_room_temp = new QLabel(layoutWidget);
        label_room_temp->setObjectName(QStringLiteral("label_room_temp"));

        verticalLayout_2->addWidget(label_room_temp);

        label_temp_ref = new QLabel(layoutWidget);
        label_temp_ref->setObjectName(QStringLiteral("label_temp_ref"));

        verticalLayout_2->addWidget(label_temp_ref);

        label_fan_state = new QLabel(layoutWidget);
        label_fan_state->setObjectName(QStringLiteral("label_fan_state"));

        verticalLayout_2->addWidget(label_fan_state);

        label_heater_state = new QLabel(layoutWidget);
        label_heater_state->setObjectName(QStringLiteral("label_heater_state"));

        verticalLayout_2->addWidget(label_heater_state);

        label_pir_state = new QLabel(layoutWidget);
        label_pir_state->setObjectName(QStringLiteral("label_pir_state"));

        verticalLayout_2->addWidget(label_pir_state);

        label_garage_state = new QLabel(layoutWidget);
        label_garage_state->setObjectName(QStringLiteral("label_garage_state"));

        verticalLayout_2->addWidget(label_garage_state);

        label_tv_state = new QLabel(layoutWidget);
        label_tv_state->setObjectName(QStringLiteral("label_tv_state"));

        verticalLayout_2->addWidget(label_tv_state);

        label_humidity_outside_house = new QLabel(layoutWidget);
        label_humidity_outside_house->setObjectName(QStringLiteral("label_humidity_outside_house"));

        verticalLayout_2->addWidget(label_humidity_outside_house);

        label_temperature_outside_house = new QLabel(layoutWidget);
        label_temperature_outside_house->setObjectName(QStringLiteral("label_temperature_outside_house"));

        verticalLayout_2->addWidget(label_temperature_outside_house);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_39 = new QLabel(layoutWidget);
        label_39->setObjectName(QStringLiteral("label_39"));

        verticalLayout_3->addWidget(label_39);

        label_27 = new QLabel(layoutWidget);
        label_27->setObjectName(QStringLiteral("label_27"));

        verticalLayout_3->addWidget(label_27);

        label_28 = new QLabel(layoutWidget);
        label_28->setObjectName(QStringLiteral("label_28"));

        verticalLayout_3->addWidget(label_28);

        label_30 = new QLabel(layoutWidget);
        label_30->setObjectName(QStringLiteral("label_30"));

        verticalLayout_3->addWidget(label_30);

        label_29 = new QLabel(layoutWidget);
        label_29->setObjectName(QStringLiteral("label_29"));

        verticalLayout_3->addWidget(label_29);

        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        verticalLayout_3->addWidget(label_23);

        label_33 = new QLabel(layoutWidget);
        label_33->setObjectName(QStringLiteral("label_33"));

        verticalLayout_3->addWidget(label_33);

        label_v_gas = new QLabel(layoutWidget);
        label_v_gas->setObjectName(QStringLiteral("label_v_gas"));

        verticalLayout_3->addWidget(label_v_gas);

        label_25 = new QLabel(layoutWidget);
        label_25->setObjectName(QStringLiteral("label_25"));

        verticalLayout_3->addWidget(label_25);

        label_26 = new QLabel(layoutWidget);
        label_26->setObjectName(QStringLiteral("label_26"));

        verticalLayout_3->addWidget(label_26);

        label_34 = new QLabel(layoutWidget);
        label_34->setObjectName(QStringLiteral("label_34"));

        verticalLayout_3->addWidget(label_34);

        label_40 = new QLabel(layoutWidget);
        label_40->setObjectName(QStringLiteral("label_40"));

        verticalLayout_3->addWidget(label_40);


        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        line = new QFrame(ReadWindow_Hall);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(-10, 351, 441, 20));
        line->setLineWidth(5);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_refresh = new QPushButton(ReadWindow_Hall);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        pushButton_refresh->setEnabled(true);
        pushButton_refresh->setGeometry(QRect(140, 400, 131, 51));

        retranslateUi(ReadWindow_Hall);

        QMetaObject::connectSlotsByName(ReadWindow_Hall);
    } // setupUi

    void retranslateUi(QDialog *ReadWindow_Hall)
    {
        ReadWindow_Hall->setWindowTitle(QApplication::translate("ReadWindow_Hall", "Read Window[Hall]", 0));
        label->setText(QApplication::translate("ReadWindow_Hall", "Photo resistor voltage", 0));
        label_2->setText(QApplication::translate("ReadWindow_Hall", "Photo Resistor Reference", 0));
        label_3->setText(QApplication::translate("ReadWindow_Hall", "Light State", 0));
        label_4->setText(QApplication::translate("ReadWindow_Hall", "Room Temperture", 0));
        label_5->setText(QApplication::translate("ReadWindow_Hall", "Temperature Reference", 0));
        label_6->setText(QApplication::translate("ReadWindow_Hall", "Fan State", 0));
        label_7->setText(QApplication::translate("ReadWindow_Hall", "Heater State", 0));
        label_8->setText(QApplication::translate("ReadWindow_Hall", "PIR State", 0));
        label_9->setText(QApplication::translate("ReadWindow_Hall", "Garage State", 0));
        label_10->setText(QApplication::translate("ReadWindow_Hall", "TV State", 0));
        label_11->setText(QApplication::translate("ReadWindow_Hall", "Humidity Outside House", 0));
        label_35->setText(QApplication::translate("ReadWindow_Hall", "Temperature Outside House", 0));
        label_photo_resistor_volt->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_photo_resistor_ref->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_light_state->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_room_temp->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_temp_ref->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_fan_state->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_heater_state->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_pir_state->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_garage_state->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_tv_state->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_humidity_outside_house->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_temperature_outside_house->setText(QApplication::translate("ReadWindow_Hall", ".................", 0));
        label_39->setText(QApplication::translate("ReadWindow_Hall", "V", 0));
        label_27->setText(QApplication::translate("ReadWindow_Hall", "V", 0));
        label_28->setText(QString());
        label_30->setText(QApplication::translate("ReadWindow_Hall", "C", 0));
        label_29->setText(QApplication::translate("ReadWindow_Hall", "C", 0));
        label_23->setText(QString());
        label_33->setText(QString());
        label_v_gas->setText(QApplication::translate("ReadWindow_Hall", "V", 0));
        label_25->setText(QString());
        label_26->setText(QApplication::translate("ReadWindow_Hall", "V", 0));
        label_34->setText(QString());
        label_40->setText(QString());
        pushButton_refresh->setText(QApplication::translate("ReadWindow_Hall", "Refresh", 0));
    } // retranslateUi

};

namespace Ui {
    class ReadWindow_Hall: public Ui_ReadWindow_Hall {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READWINDOW_HALL_H
