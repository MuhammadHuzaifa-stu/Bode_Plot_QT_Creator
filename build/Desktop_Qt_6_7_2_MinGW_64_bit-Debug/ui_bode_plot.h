/********************************************************************************
** Form generated from reading UI file 'bode_plot.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BODE_PLOT_H
#define UI_BODE_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_bode_plot
{
public:
    QWidget *centralwidget;
    QCustomPlot *custom_plot;
    QPushButton *pushButton;
    QCustomPlot *custom_plot_2;
    QLineEdit *numerator_input;
    QLabel *label_2;
    QLineEdit *denominator_input;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *saveButton;
    QPushButton *saveButton_2;
    QLabel *stabilityLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *bode_plot)
    {
        if (bode_plot->objectName().isEmpty())
            bode_plot->setObjectName("bode_plot");
        bode_plot->resize(780, 700);
        bode_plot->setMinimumSize(QSize(780, 700));
        bode_plot->setMaximumSize(QSize(780, 700));
        centralwidget = new QWidget(bode_plot);
        centralwidget->setObjectName("centralwidget");
        custom_plot = new QCustomPlot(centralwidget);
        custom_plot->setObjectName("custom_plot");
        custom_plot->setGeometry(QRect(110, 100, 541, 211));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 20, 80, 24));
        pushButton->setMouseTracking(true);
        custom_plot_2 = new QCustomPlot(centralwidget);
        custom_plot_2->setObjectName("custom_plot_2");
        custom_plot_2->setGeometry(QRect(110, 360, 541, 211));
        numerator_input = new QLineEdit(centralwidget);
        numerator_input->setObjectName("numerator_input");
        numerator_input->setGeometry(QRect(220, 20, 191, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 20, 91, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        label_2->setFont(font);
        denominator_input = new QLineEdit(centralwidget);
        denominator_input->setObjectName("denominator_input");
        denominator_input->setGeometry(QRect(220, 50, 190, 23));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 50, 91, 20));
        label_3->setFont(font);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(570, 50, 80, 24));
        pushButton_2->setMouseTracking(true);
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(570, 580, 80, 24));
        saveButton->setMouseTracking(true);
        saveButton_2 = new QPushButton(centralwidget);
        saveButton_2->setObjectName("saveButton_2");
        saveButton_2->setGeometry(QRect(570, 320, 80, 24));
        saveButton_2->setMouseTracking(true);
        stabilityLabel = new QLabel(centralwidget);
        stabilityLabel->setObjectName("stabilityLabel");
        stabilityLabel->setGeometry(QRect(110, 610, 541, 31));
        QFont font1;
        font1.setStrikeOut(false);
        stabilityLabel->setFont(font1);
        stabilityLabel->setMouseTracking(false);
        stabilityLabel->setAutoFillBackground(false);
        stabilityLabel->setTextFormat(Qt::AutoText);
        bode_plot->setCentralWidget(centralwidget);
        menubar = new QMenuBar(bode_plot);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 780, 21));
        bode_plot->setMenuBar(menubar);
        statusbar = new QStatusBar(bode_plot);
        statusbar->setObjectName("statusbar");
        bode_plot->setStatusBar(statusbar);

        retranslateUi(bode_plot);

        QMetaObject::connectSlotsByName(bode_plot);
    } // setupUi

    void retranslateUi(QMainWindow *bode_plot)
    {
        bode_plot->setWindowTitle(QCoreApplication::translate("bode_plot", "bode_plot", nullptr));
        pushButton->setText(QCoreApplication::translate("bode_plot", "Plot", nullptr));
        label_2->setText(QCoreApplication::translate("bode_plot", "Numerator", nullptr));
        label_3->setText(QCoreApplication::translate("bode_plot", "Denominator", nullptr));
        pushButton_2->setText(QCoreApplication::translate("bode_plot", "Clear", nullptr));
        saveButton->setText(QCoreApplication::translate("bode_plot", "Save", nullptr));
        saveButton_2->setText(QCoreApplication::translate("bode_plot", "Save", nullptr));
        stabilityLabel->setText(QCoreApplication::translate("bode_plot", "Output Console", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bode_plot: public Ui_bode_plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BODE_PLOT_H
