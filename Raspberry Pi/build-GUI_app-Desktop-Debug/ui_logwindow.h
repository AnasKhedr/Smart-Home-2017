/********************************************************************************
** Form generated from reading UI file 'logwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWINDOW_H
#define UI_LOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWindow
{
public:
    QTextBrowser *textBrowser_log;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_mode;
    QComboBox *comboBox_mode;
    QCheckBox *checkBox_autoscroll;
    QPushButton *pushButton_refresh;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_log;
    QComboBox *comboBox_log;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_refresh_every;
    QSpinBox *spinBox_refresh_every;
    QComboBox *comboBox_refresh_every;

    void setupUi(QDialog *LogWindow)
    {
        if (LogWindow->objectName().isEmpty())
            LogWindow->setObjectName(QStringLiteral("LogWindow"));
        LogWindow->resize(563, 430);
        textBrowser_log = new QTextBrowser(LogWindow);
        textBrowser_log->setObjectName(QStringLiteral("textBrowser_log"));
        textBrowser_log->setGeometry(QRect(10, 80, 541, 192));
        widget = new QWidget(LogWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 290, 106, 129));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_mode = new QLabel(widget);
        label_mode->setObjectName(QStringLiteral("label_mode"));

        verticalLayout->addWidget(label_mode);

        comboBox_mode = new QComboBox(widget);
        comboBox_mode->setObjectName(QStringLiteral("comboBox_mode"));

        verticalLayout->addWidget(comboBox_mode);

        checkBox_autoscroll = new QCheckBox(widget);
        checkBox_autoscroll->setObjectName(QStringLiteral("checkBox_autoscroll"));

        verticalLayout->addWidget(checkBox_autoscroll);

        pushButton_refresh = new QPushButton(widget);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        pushButton_refresh->setEnabled(false);

        verticalLayout->addWidget(pushButton_refresh);

        widget1 = new QWidget(LogWindow);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(190, 10, 136, 60));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_log = new QLabel(widget1);
        label_log->setObjectName(QStringLiteral("label_log"));
        label_log->setEnabled(true);

        verticalLayout_2->addWidget(label_log);

        comboBox_log = new QComboBox(widget1);
        comboBox_log->setObjectName(QStringLiteral("comboBox_log"));

        verticalLayout_2->addWidget(comboBox_log);

        widget2 = new QWidget(LogWindow);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(260, 330, 249, 33));
        horizontalLayout = new QHBoxLayout(widget2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_refresh_every = new QLabel(widget2);
        label_refresh_every->setObjectName(QStringLiteral("label_refresh_every"));

        horizontalLayout->addWidget(label_refresh_every);

        spinBox_refresh_every = new QSpinBox(widget2);
        spinBox_refresh_every->setObjectName(QStringLiteral("spinBox_refresh_every"));
        spinBox_refresh_every->setMinimum(1);
        spinBox_refresh_every->setMaximum(1000);

        horizontalLayout->addWidget(spinBox_refresh_every);

        comboBox_refresh_every = new QComboBox(widget2);
        comboBox_refresh_every->setObjectName(QStringLiteral("comboBox_refresh_every"));

        horizontalLayout->addWidget(comboBox_refresh_every);


        retranslateUi(LogWindow);

        QMetaObject::connectSlotsByName(LogWindow);
    } // setupUi

    void retranslateUi(QDialog *LogWindow)
    {
        LogWindow->setWindowTitle(QApplication::translate("LogWindow", "Dialog", 0));
        label_mode->setText(QApplication::translate("LogWindow", "MODE", 0));
        comboBox_mode->clear();
        comboBox_mode->insertItems(0, QStringList()
         << QApplication::translate("LogWindow", "auto", 0)
         << QApplication::translate("LogWindow", "manual", 0)
        );
        checkBox_autoscroll->setText(QApplication::translate("LogWindow", "auto-scroll", 0));
        pushButton_refresh->setText(QApplication::translate("LogWindow", "Refresh", 0));
        label_log->setText(QApplication::translate("LogWindow", "log", 0));
        comboBox_log->clear();
        comboBox_log->insertItems(0, QStringList()
         << QApplication::translate("LogWindow", "log_server", 0)
         << QApplication::translate("LogWindow", "safty_readings", 0)
        );
        label_refresh_every->setText(QApplication::translate("LogWindow", "Refresh Every", 0));
        comboBox_refresh_every->clear();
        comboBox_refresh_every->insertItems(0, QStringList()
         << QApplication::translate("LogWindow", "Sec", 0)
         << QApplication::translate("LogWindow", "mSec", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class LogWindow: public Ui_LogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
