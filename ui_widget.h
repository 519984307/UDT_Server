/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_agreement_type;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ip_addr;
    QComboBox *comboBox_ip_addr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_port;
    QSpinBox *spinBox_port;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_log_auto_del_time;
    QSpinBox *spinBox_log_save_time;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_old_file_del_time;
    QSpinBox *spinBox_file_del_time;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_select_log_file_path;
    QLineEdit *lineEdit_log_save_path;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_select_rx_file_path;
    QLineEdit *lineEdit_recv_file_save_path;
    QPushButton *pushButton_del_all;
    QPushButton *pushButton_del_all_log;
    QPushButton *pushButton_save_log;
    QPushButton *pushButton_start_udp;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit_log;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_current_time;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1139, 643);
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_agreement_type = new QLabel(groupBox);
        label_agreement_type->setObjectName(QString::fromUtf8("label_agreement_type"));

        horizontalLayout->addWidget(label_agreement_type);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_ip_addr = new QLabel(groupBox);
        label_ip_addr->setObjectName(QString::fromUtf8("label_ip_addr"));

        horizontalLayout_3->addWidget(label_ip_addr);

        comboBox_ip_addr = new QComboBox(groupBox);
        comboBox_ip_addr->addItem(QString());
        comboBox_ip_addr->setObjectName(QString::fromUtf8("comboBox_ip_addr"));
        comboBox_ip_addr->setEditable(true);

        horizontalLayout_3->addWidget(comboBox_ip_addr);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_port = new QLabel(groupBox);
        label_port->setObjectName(QString::fromUtf8("label_port"));

        horizontalLayout_2->addWidget(label_port);

        spinBox_port = new QSpinBox(groupBox);
        spinBox_port->setObjectName(QString::fromUtf8("spinBox_port"));
        spinBox_port->setMinimum(1024);
        spinBox_port->setMaximum(65535);
        spinBox_port->setValue(6666);

        horizontalLayout_2->addWidget(spinBox_port);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_log_auto_del_time = new QLabel(groupBox);
        label_log_auto_del_time->setObjectName(QString::fromUtf8("label_log_auto_del_time"));

        horizontalLayout_9->addWidget(label_log_auto_del_time);

        spinBox_log_save_time = new QSpinBox(groupBox);
        spinBox_log_save_time->setObjectName(QString::fromUtf8("spinBox_log_save_time"));
        spinBox_log_save_time->setMinimum(1);
        spinBox_log_save_time->setMaximum(999);
        spinBox_log_save_time->setValue(10);

        horizontalLayout_9->addWidget(spinBox_log_save_time);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_old_file_del_time = new QLabel(groupBox);
        label_old_file_del_time->setObjectName(QString::fromUtf8("label_old_file_del_time"));

        horizontalLayout_7->addWidget(label_old_file_del_time);

        spinBox_file_del_time = new QSpinBox(groupBox);
        spinBox_file_del_time->setObjectName(QString::fromUtf8("spinBox_file_del_time"));
        spinBox_file_del_time->setMinimum(1);
        spinBox_file_del_time->setMaximum(999);
        spinBox_file_del_time->setValue(20);
        spinBox_file_del_time->setDisplayIntegerBase(10);

        horizontalLayout_7->addWidget(spinBox_file_del_time);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_select_log_file_path = new QPushButton(groupBox);
        pushButton_select_log_file_path->setObjectName(QString::fromUtf8("pushButton_select_log_file_path"));

        horizontalLayout_4->addWidget(pushButton_select_log_file_path);

        lineEdit_log_save_path = new QLineEdit(groupBox);
        lineEdit_log_save_path->setObjectName(QString::fromUtf8("lineEdit_log_save_path"));

        horizontalLayout_4->addWidget(lineEdit_log_save_path);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_select_rx_file_path = new QPushButton(groupBox);
        pushButton_select_rx_file_path->setObjectName(QString::fromUtf8("pushButton_select_rx_file_path"));

        horizontalLayout_5->addWidget(pushButton_select_rx_file_path);

        lineEdit_recv_file_save_path = new QLineEdit(groupBox);
        lineEdit_recv_file_save_path->setObjectName(QString::fromUtf8("lineEdit_recv_file_save_path"));

        horizontalLayout_5->addWidget(lineEdit_recv_file_save_path);


        verticalLayout_2->addLayout(horizontalLayout_5);

        pushButton_del_all = new QPushButton(groupBox);
        pushButton_del_all->setObjectName(QString::fromUtf8("pushButton_del_all"));

        verticalLayout_2->addWidget(pushButton_del_all);

        pushButton_del_all_log = new QPushButton(groupBox);
        pushButton_del_all_log->setObjectName(QString::fromUtf8("pushButton_del_all_log"));

        verticalLayout_2->addWidget(pushButton_del_all_log);

        pushButton_save_log = new QPushButton(groupBox);
        pushButton_save_log->setObjectName(QString::fromUtf8("pushButton_save_log"));

        verticalLayout_2->addWidget(pushButton_save_log);

        pushButton_start_udp = new QPushButton(groupBox);
        pushButton_start_udp->setObjectName(QString::fromUtf8("pushButton_start_udp"));

        verticalLayout_2->addWidget(pushButton_start_udp);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_10->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit_log = new QPlainTextEdit(groupBox_2);
        plainTextEdit_log->setObjectName(QString::fromUtf8("plainTextEdit_log"));
        plainTextEdit_log->setEnabled(true);
        plainTextEdit_log->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit_log);


        horizontalLayout_10->addWidget(groupBox_2);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        label_current_time = new QLabel(Widget);
        label_current_time->setObjectName(QString::fromUtf8("label_current_time"));

        horizontalLayout_11->addWidget(label_current_time);


        verticalLayout_3->addLayout(horizontalLayout_11);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label_agreement_type->setText(QCoreApplication::translate("Widget", "\345\215\217\350\256\256\347\261\273\345\236\213:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "UDP", nullptr));

        label_ip_addr->setText(QCoreApplication::translate("Widget", "IP\345\234\260\345\235\200:", nullptr));
        comboBox_ip_addr->setItemText(0, QCoreApplication::translate("Widget", "127.0.0.1", nullptr));

        label_port->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267:", nullptr));
        label_log_auto_del_time->setText(QCoreApplication::translate("Widget", "\346\227\245\345\277\227\350\207\252\345\212\250\346\270\205\347\251\272\345\271\266\344\277\235\345\255\230\347\232\204\346\227\266\351\227\264(\345\210\206\351\222\237):", nullptr));
        label_old_file_del_time->setText(QCoreApplication::translate("Widget", "\346\227\247\346\226\207\344\273\266\345\210\240\351\231\244\346\227\266\351\227\264(\345\210\206\351\222\237):", nullptr));
        pushButton_select_log_file_path->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\227\245\345\277\227\346\226\207\344\273\266\345\255\230\345\202\250\344\275\215\347\275\256:", nullptr));
        pushButton_select_rx_file_path->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\216\245\346\224\266\346\226\207\344\273\266\345\255\230\345\202\250\344\275\215\347\275\256:", nullptr));
        pushButton_del_all->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\226\207\344\273\266\346\216\245\346\224\266\347\233\256\345\275\225", nullptr));
        pushButton_del_all_log->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\227\245\345\277\227\344\277\235\345\255\230\347\233\256\345\275\225", nullptr));
        pushButton_save_log->setText(QCoreApplication::translate("Widget", "\346\211\213\345\212\250\346\270\205\347\251\272\345\271\266\344\277\235\345\255\230\346\227\245\345\277\227", nullptr));
        pushButton_start_udp->setText(QCoreApplication::translate("Widget", "\345\220\257\345\212\250UDP\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        plainTextEdit_log->setDocumentTitle(QString());
        label_current_time->setText(QCoreApplication::translate("Widget", "2021/04/22", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
