/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "colorpicker.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QPushButton *enterbut;
    QPushButton *varbut;
    QPushButton *clearbut;
    QTextEdit *inptxt;
    QTextBrowser *restxt;
    QGraphicsView *graphicsView;
    QPushButton *plotbut;
    QWidget *plotWidget;
    QLineEdit *inpLine;
    QLabel *label;
    QPushButton *addPlotButton;
    QPushButton *clearPlotButton;
    QCustomPlot *resPlot;
    QComboBox *lineTypeBox;
    QPushButton *savePlotButton;
    QPushButton *importPlotButton;
    QComboBox *plotTypeBox;
    gui::colorpicker::ColorPicker *colorPlotPalette;
    QMenuBar *menuBar;
    QMenu *menuEdison;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(923, 640);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 921, 581));
        enterbut = new QPushButton(widget);
        enterbut->setObjectName(QStringLiteral("enterbut"));
        enterbut->setGeometry(QRect(780, 6, 141, 55));
        varbut = new QPushButton(widget);
        varbut->setObjectName(QStringLiteral("varbut"));
        varbut->setGeometry(QRect(780, 51, 141, 55));
        clearbut = new QPushButton(widget);
        clearbut->setObjectName(QStringLiteral("clearbut"));
        clearbut->setGeometry(QRect(780, 96, 141, 55));
        inptxt = new QTextEdit(widget);
        inptxt->setObjectName(QStringLiteral("inptxt"));
        inptxt->setGeometry(QRect(10, 10, 771, 191));
        restxt = new QTextBrowser(widget);
        restxt->setObjectName(QStringLiteral("restxt"));
        restxt->setGeometry(QRect(450, 380, 391, 161));
        restxt->setReadOnly(true);
        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 210, 771, 301));
        plotbut = new QPushButton(widget);
        plotbut->setObjectName(QStringLiteral("plotbut"));
        plotbut->setGeometry(QRect(780, 141, 141, 55));
        plotWidget = new QWidget(widget);
        plotWidget->setObjectName(QStringLiteral("plotWidget"));
        plotWidget->setGeometry(QRect(-150, 10, 881, 611));
        plotWidget->setAutoFillBackground(true);
        inpLine = new QLineEdit(plotWidget);
        inpLine->setObjectName(QStringLiteral("inpLine"));
        inpLine->setGeometry(QRect(50, 20, 581, 41));
        label = new QLabel(plotWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 20, 51, 31));
        label->setTextFormat(Qt::RichText);
        addPlotButton = new QPushButton(plotWidget);
        addPlotButton->setObjectName(QStringLiteral("addPlotButton"));
        addPlotButton->setGeometry(QRect(670, 20, 171, 41));
        addPlotButton->setAutoFillBackground(false);
        addPlotButton->setStyleSheet(QLatin1String("color: #111;\n"
"border: 1px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #aaa);\n"
"min-width: 80px;"));
        addPlotButton->setCheckable(false);
        addPlotButton->setAutoDefault(false);
        addPlotButton->setFlat(false);
        clearPlotButton = new QPushButton(plotWidget);
        clearPlotButton->setObjectName(QStringLiteral("clearPlotButton"));
        clearPlotButton->setGeometry(QRect(670, 64, 171, 41));
        clearPlotButton->setStyleSheet(QLatin1String("color: #111;\n"
"border: 1px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #aaa);\n"
"min-width: 80px;"));
        resPlot = new QCustomPlot(plotWidget);
        resPlot->setObjectName(QStringLiteral("resPlot"));
        resPlot->setGeometry(QRect(10, 70, 621, 421));
        resPlot->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineTypeBox = new QComboBox(plotWidget);
        lineTypeBox->setObjectName(QStringLiteral("lineTypeBox"));
        lineTypeBox->setGeometry(QRect(680, 230, 151, 26));
        savePlotButton = new QPushButton(plotWidget);
        savePlotButton->setObjectName(QStringLiteral("savePlotButton"));
        savePlotButton->setGeometry(QRect(670, 109, 171, 41));
        savePlotButton->setStyleSheet(QLatin1String("color: #111;\n"
"border: 1px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #aaa);\n"
"min-width: 80px;"));
        importPlotButton = new QPushButton(plotWidget);
        importPlotButton->setObjectName(QStringLiteral("importPlotButton"));
        importPlotButton->setGeometry(QRect(670, 154, 171, 41));
        importPlotButton->setStyleSheet(QLatin1String("color: #111;\n"
"border: 1px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #aaa);\n"
"min-width: 80px;"));
        plotTypeBox = new QComboBox(plotWidget);
        plotTypeBox->setObjectName(QStringLiteral("plotTypeBox"));
        plotTypeBox->setGeometry(QRect(680, 200, 151, 31));
        colorPlotPalette = new gui::colorpicker::ColorPicker(plotWidget);
        colorPlotPalette->setObjectName(QStringLiteral("colorPlotPalette"));
        colorPlotPalette->setGeometry(QRect(640, 270, 231, 221));
        colorPlotPalette->setAutoFillBackground(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 923, 22));
        menuEdison = new QMenu(menuBar);
        menuEdison->setObjectName(QStringLiteral("menuEdison"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuEdison->menuAction());

        retranslateUi(MainWindow);

        addPlotButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        enterbut->setText(QApplication::translate("MainWindow", "Enter", Q_NULLPTR));
        varbut->setText(QApplication::translate("MainWindow", "Variables", Q_NULLPTR));
        clearbut->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        restxt->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        plotbut->setText(QApplication::translate("MainWindow", "Plot", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\"/><span style=\" font-size:18pt; font-weight:600;\">Y  =</span></p></body></html>", Q_NULLPTR));
        addPlotButton->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        clearPlotButton->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        savePlotButton->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        importPlotButton->setText(QApplication::translate("MainWindow", "Import", Q_NULLPTR));
        menuEdison->setTitle(QApplication::translate("MainWindow", "Edison", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
