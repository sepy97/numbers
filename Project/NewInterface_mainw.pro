#-------------------------------------------------
#
# Project created by QtCreator 2015-08-08T20:54:16
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

#QMAKE_MAC_SDK = macosx10.11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewInterface_mainw
TEMPLATE = app
include (../jkqtmathtext_with_xits.pri)
INCLUDEPATH += Kernel

SOURCES += main.cpp\
        mainwindow.cpp\
    qcustomplot.cpp \
    Kernel/VarTable.cpp \
    Kernel/SmallNumber.cpp \
    Kernel/Test.cpp \
    Kernel/Tree.cpp \
    Kernel/RationalNumber.cpp \
    Kernel/Primes.cpp \
    Kernel/PrimeFactoring.cpp \
    Kernel/NumberException.cpp \
    Kernel/LexicalScanner.cpp \
    Kernel/LargeNumber.cpp \
    Kernel/fast_deque.cpp \
    Kernel/GrammarTree.cpp \
    Kernel/DoubleNumber.cpp \
    Kernel/Number.cpp \
    Kernel/fontrenderer.cpp \
  # history.cpp \
    Kernel/Optimizer.cpp \
    Kernel/Executor.cpp \
    history.cpp \
    Kernel/Random.cpp \
    colorpicker.cpp

HEADERS  += mainwindow.h\
    qcustomplot.h \
    Kernel/VarTable.h \
    Kernel/RealNumber.h \
    Kernel/SmallNumber.h \
    Kernel/SparseVector.h \
    Kernel/Test.h \
    Kernel/Tree.h \
    Kernel/Variable.h \
    Kernel/RationalNumber.h \
    Kernel/Primes.h \
    Kernel/PrimeFactoring.h \
    Kernel/NumberException.h \
    Kernel/LexicalScaner.h \
    Kernel/LargeNumber.h \
    Kernel/fast_deque.h \
    Kernel/GrammarTree.h \
    Kernel/Executor.h \
    Kernel/DoubleNumber.h \
    Kernel/number.h \
    Kernel/fontrenderer.h \
  # history.h \
    Kernel/Optimizer.h \
    history.h \
    Kernel/Random.h \
    colorpicker.h

FORMS    += mainwindow.ui

DISTFILES += \
    style.qss
