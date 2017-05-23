/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Project/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "on_enterbut_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "on_varbut_clicked"
QT_MOC_LITERAL(4, 50, 19), // "on_clearbut_clicked"
QT_MOC_LITERAL(5, 70, 8), // "makePlot"
QT_MOC_LITERAL(6, 79, 10), // "inpformula"
QT_MOC_LITERAL(7, 90, 12), // "range_x_left"
QT_MOC_LITERAL(8, 103, 13), // "range_x_right"
QT_MOC_LITERAL(9, 117, 12), // "range_y_left"
QT_MOC_LITERAL(10, 130, 13), // "range_y_right"
QT_MOC_LITERAL(11, 144, 31), // "on_inptxt_cursorPositionChanged"
QT_MOC_LITERAL(12, 176, 18), // "on_plotbut_clicked"
QT_MOC_LITERAL(13, 195, 24), // "on_addPlotButton_clicked"
QT_MOC_LITERAL(14, 220, 26), // "on_clearPlotButton_clicked"
QT_MOC_LITERAL(15, 247, 34), // "on_lineTypeBox_currentIndexCh..."
QT_MOC_LITERAL(16, 282, 5), // "index"
QT_MOC_LITERAL(17, 288, 25) // "on_savePlotButton_clicked"

    },
    "MainWindow\0on_enterbut_clicked\0\0"
    "on_varbut_clicked\0on_clearbut_clicked\0"
    "makePlot\0inpformula\0range_x_left\0"
    "range_x_right\0range_y_left\0range_y_right\0"
    "on_inptxt_cursorPositionChanged\0"
    "on_plotbut_clicked\0on_addPlotButton_clicked\0"
    "on_clearPlotButton_clicked\0"
    "on_lineTypeBox_currentIndexChanged\0"
    "index\0on_savePlotButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    5,   67,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,
      15,    1,   82,    2, 0x08 /* Private */,
      17,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_enterbut_clicked(); break;
        case 1: _t->on_varbut_clicked(); break;
        case 2: _t->on_clearbut_clicked(); break;
        case 3: _t->makePlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 4: _t->on_inptxt_cursorPositionChanged(); break;
        case 5: _t->on_plotbut_clicked(); break;
        case 6: _t->on_addPlotButton_clicked(); break;
        case 7: _t->on_clearPlotButton_clicked(); break;
        case 8: _t->on_lineTypeBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_savePlotButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
