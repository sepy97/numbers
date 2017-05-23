/********************************************************************************
** Form generated from reading UI file 'testform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTFORM_H
#define UI_TESTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "../../../jkqtmathtext.h"

QT_BEGIN_NAMESPACE

class Ui_TestForm
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTextBrowser *textBrowserSource;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *cmbTestset;
    QLabel *label_4;
    QComboBox *cmbFont;
    QLabel *label_2;
    QLineEdit *edtSizes;
    QCheckBox *chkBoxes;
    QCheckBox *chkAntiAlias;
    QCheckBox *chkAntiAliasHQ;
    QCheckBox *chkAntiAliasText;
    QCheckBox *chkSmoothTransform;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *edtLatexPrefix;
    QLineEdit *edtLatexPostfix;
    QLabel *label_6;
    QFontComboBox *cmbUnicodeSerif;
    QFontComboBox *cmbUnicodeSans;
    QFontComboBox *cmbUnicodeFixed;
    QLabel *label_7;
    QFontComboBox *cmbUnicodeSymbol;
    QSpacerItem *horizontalSpacer_2;
    QTreeWidget *tree;
    QTextBrowser *textBrowser;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_11;
    JKQTMathTextLabel *labMath;

    void setupUi(QWidget *TestForm)
    {
        if (TestForm->objectName().isEmpty())
            TestForm->setObjectName(QStringLiteral("TestForm"));
        TestForm->resize(1238, 742);
        gridLayout = new QGridLayout(TestForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scrollArea = new QScrollArea(TestForm);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 605, 628));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 4, 0, 5, 1);

        textBrowserSource = new QTextBrowser(TestForm);
        textBrowserSource->setObjectName(QStringLiteral("textBrowserSource"));
        textBrowserSource->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(textBrowserSource, 4, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(TestForm);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        cmbTestset = new QComboBox(TestForm);
        cmbTestset->setObjectName(QStringLiteral("cmbTestset"));
        cmbTestset->setMaxVisibleItems(30);

        horizontalLayout_2->addWidget(cmbTestset);

        label_4 = new QLabel(TestForm);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        cmbFont = new QComboBox(TestForm);
        cmbFont->setObjectName(QStringLiteral("cmbFont"));

        horizontalLayout_2->addWidget(cmbFont);

        label_2 = new QLabel(TestForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        edtSizes = new QLineEdit(TestForm);
        edtSizes->setObjectName(QStringLiteral("edtSizes"));

        horizontalLayout_2->addWidget(edtSizes);

        chkBoxes = new QCheckBox(TestForm);
        chkBoxes->setObjectName(QStringLiteral("chkBoxes"));
        chkBoxes->setChecked(true);

        horizontalLayout_2->addWidget(chkBoxes);

        chkAntiAlias = new QCheckBox(TestForm);
        chkAntiAlias->setObjectName(QStringLiteral("chkAntiAlias"));
        chkAntiAlias->setChecked(true);

        horizontalLayout_2->addWidget(chkAntiAlias);

        chkAntiAliasHQ = new QCheckBox(TestForm);
        chkAntiAliasHQ->setObjectName(QStringLiteral("chkAntiAliasHQ"));

        horizontalLayout_2->addWidget(chkAntiAliasHQ);

        chkAntiAliasText = new QCheckBox(TestForm);
        chkAntiAliasText->setObjectName(QStringLiteral("chkAntiAliasText"));
        chkAntiAliasText->setChecked(true);

        horizontalLayout_2->addWidget(chkAntiAliasText);

        chkSmoothTransform = new QCheckBox(TestForm);
        chkSmoothTransform->setObjectName(QStringLiteral("chkSmoothTransform"));

        horizontalLayout_2->addWidget(chkSmoothTransform);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(3, 2);
        horizontalLayout_2->setStretch(6, 1);

        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(TestForm);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        edtLatexPrefix = new QLineEdit(TestForm);
        edtLatexPrefix->setObjectName(QStringLiteral("edtLatexPrefix"));

        horizontalLayout_3->addWidget(edtLatexPrefix);

        edtLatexPostfix = new QLineEdit(TestForm);
        edtLatexPostfix->setObjectName(QStringLiteral("edtLatexPostfix"));

        horizontalLayout_3->addWidget(edtLatexPostfix);

        label_6 = new QLabel(TestForm);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        cmbUnicodeSerif = new QFontComboBox(TestForm);
        cmbUnicodeSerif->setObjectName(QStringLiteral("cmbUnicodeSerif"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        cmbUnicodeSerif->setCurrentFont(font);

        horizontalLayout_3->addWidget(cmbUnicodeSerif);

        cmbUnicodeSans = new QFontComboBox(TestForm);
        cmbUnicodeSans->setObjectName(QStringLiteral("cmbUnicodeSans"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        cmbUnicodeSans->setCurrentFont(font1);

        horizontalLayout_3->addWidget(cmbUnicodeSans);

        cmbUnicodeFixed = new QFontComboBox(TestForm);
        cmbUnicodeFixed->setObjectName(QStringLiteral("cmbUnicodeFixed"));
        QFont font2;
        font2.setFamily(QStringLiteral("Courier New"));
        cmbUnicodeFixed->setCurrentFont(font2);

        horizontalLayout_3->addWidget(cmbUnicodeFixed);

        label_7 = new QLabel(TestForm);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7);

        cmbUnicodeSymbol = new QFontComboBox(TestForm);
        cmbUnicodeSymbol->setObjectName(QStringLiteral("cmbUnicodeSymbol"));
        QFont font3;
        font3.setFamily(QStringLiteral("Symbol"));
        cmbUnicodeSymbol->setCurrentFont(font3);

        horizontalLayout_3->addWidget(cmbUnicodeSymbol);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        tree = new QTreeWidget(TestForm);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        tree->setHeaderItem(__qtreewidgetitem);
        tree->setObjectName(QStringLiteral("tree"));
        tree->setHeaderHidden(true);

        gridLayout->addWidget(tree, 8, 1, 1, 1);

        textBrowser = new QTextBrowser(TestForm);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 6, 1, 1, 1);

        label_9 = new QLabel(TestForm);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 5, 1, 1, 1);

        label_10 = new QLabel(TestForm);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 7, 1, 1, 1);

        label_8 = new QLabel(TestForm);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 1, 1, 1);

        label_11 = new QLabel(TestForm);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 3, 0, 1, 1);

        labMath = new JKQTMathTextLabel(TestForm);
        labMath->setObjectName(QStringLiteral("labMath"));

        gridLayout->addWidget(labMath, 9, 0, 1, 2);


        retranslateUi(TestForm);
        QObject::connect(cmbTestset, SIGNAL(currentIndexChanged(int)), TestForm, SLOT(updateMath()));
        QObject::connect(cmbFont, SIGNAL(currentIndexChanged(int)), TestForm, SLOT(updateMath()));
        QObject::connect(chkBoxes, SIGNAL(clicked()), TestForm, SLOT(updateMath()));
        QObject::connect(chkAntiAlias, SIGNAL(clicked()), TestForm, SLOT(updateMath()));
        QObject::connect(chkAntiAliasHQ, SIGNAL(clicked()), TestForm, SLOT(updateMath()));
        QObject::connect(chkAntiAliasText, SIGNAL(clicked()), TestForm, SLOT(updateMath()));
        QObject::connect(edtSizes, SIGNAL(textChanged(QString)), TestForm, SLOT(updateMath()));
        QObject::connect(edtLatexPrefix, SIGNAL(textChanged(QString)), TestForm, SLOT(updateMath()));
        QObject::connect(edtLatexPostfix, SIGNAL(textChanged(QString)), TestForm, SLOT(updateMath()));
        QObject::connect(cmbUnicodeSerif, SIGNAL(currentFontChanged(QFont)), TestForm, SLOT(updateMath()));
        QObject::connect(cmbUnicodeSans, SIGNAL(currentFontChanged(QFont)), TestForm, SLOT(updateMath()));
        QObject::connect(cmbUnicodeFixed, SIGNAL(currentFontChanged(QFont)), TestForm, SLOT(updateMath()));
        QObject::connect(cmbUnicodeSymbol, SIGNAL(currentFontChanged(QFont)), TestForm, SLOT(updateMath()));
        QObject::connect(chkSmoothTransform, SIGNAL(clicked()), TestForm, SLOT(updateMath()));

        cmbTestset->setCurrentIndex(-1);
        cmbFont->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TestForm);
    } // setupUi

    void retranslateUi(QWidget *TestForm)
    {
        TestForm->setWindowTitle(QApplication::translate("TestForm", "Form", 0));
        label->setText(QApplication::translate("TestForm", "TextLabel", 0));
        label_3->setText(QApplication::translate("TestForm", "testset:", 0));
        label_4->setText(QApplication::translate("TestForm", "fonts:", 0));
        cmbFont->clear();
        cmbFont->insertItems(0, QStringList()
         << QApplication::translate("TestForm", "Symbol", 0)
         << QApplication::translate("TestForm", "XITS", 0)
         << QApplication::translate("TestForm", "STIX", 0)
         << QApplication::translate("TestForm", "Unicode", 0)
         << QApplication::translate("TestForm", "LaTeX", 0)
         << QApplication::translate("TestForm", "ASANA", 0)
        );
        label_2->setText(QApplication::translate("TestForm", "size:", 0));
        edtSizes->setText(QApplication::translate("TestForm", "90,30,20,10", 0));
        chkBoxes->setText(QApplication::translate("TestForm", "boxes", 0));
        chkAntiAlias->setText(QApplication::translate("TestForm", "anti-aliase", 0));
        chkAntiAliasHQ->setText(QApplication::translate("TestForm", "HQ anti-aliase", 0));
        chkAntiAliasText->setText(QApplication::translate("TestForm", "Text anti-aliase", 0));
        chkSmoothTransform->setText(QApplication::translate("TestForm", "smooth transform", 0));
        label_5->setText(QApplication::translate("TestForm", "latex prefix/postfix:", 0));
        label_6->setText(QApplication::translate("TestForm", "Symbol/Unicode fonts:", 0));
        label_7->setText(QApplication::translate("TestForm", "symbol font:", 0));
        label_9->setText(QApplication::translate("TestForm", "HTML output:", 0));
        label_10->setText(QApplication::translate("TestForm", "node tree:", 0));
        label_8->setText(QApplication::translate("TestForm", "LaTeX source:", 0));
        label_11->setText(QApplication::translate("TestForm", "rendered result:", 0));
        labMath->setText(QApplication::translate("TestForm", "left(left[sqrt{2picdotint_{-infty}^infty f(x);mathrm{d}x}right]right) ", 0));
    } // retranslateUi

};

namespace Ui {
    class TestForm: public Ui_TestForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTFORM_H
