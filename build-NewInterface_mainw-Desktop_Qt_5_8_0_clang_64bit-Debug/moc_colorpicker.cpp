/****************************************************************************
** Meta object code from reading C++ file 'colorpicker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Project/colorpicker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'colorpicker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gui__colorpicker__ColorPicker_t {
    QByteArrayData data[14];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gui__colorpicker__ColorPicker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gui__colorpicker__ColorPicker_t qt_meta_stringdata_gui__colorpicker__ColorPicker = {
    {
QT_MOC_LITERAL(0, 0, 29), // "gui::colorpicker::ColorPicker"
QT_MOC_LITERAL(1, 30, 20), // "selectedColorChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 1), // "c"
QT_MOC_LITERAL(4, 54, 18), // "paletteItemChanged"
QT_MOC_LITERAL(5, 73, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(6, 91, 7), // "current"
QT_MOC_LITERAL(7, 99, 8), // "previous"
QT_MOC_LITERAL(8, 108, 19), // "setPaletteSelection"
QT_MOC_LITERAL(9, 128, 10), // "redChanged"
QT_MOC_LITERAL(10, 139, 1), // "v"
QT_MOC_LITERAL(11, 141, 12), // "greenChanged"
QT_MOC_LITERAL(12, 154, 11), // "blueChanged"
QT_MOC_LITERAL(13, 166, 12) // "alphaChanged"

    },
    "gui::colorpicker::ColorPicker\0"
    "selectedColorChanged\0\0c\0paletteItemChanged\0"
    "QTableWidgetItem*\0current\0previous\0"
    "setPaletteSelection\0redChanged\0v\0"
    "greenChanged\0blueChanged\0alphaChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gui__colorpicker__ColorPicker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   52,    2, 0x09 /* Protected */,
       8,    0,   57,    2, 0x09 /* Protected */,
       9,    1,   58,    2, 0x09 /* Protected */,
      11,    1,   61,    2, 0x09 /* Protected */,
      12,    1,   64,    2, 0x09 /* Protected */,
      13,    1,   67,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void gui::colorpicker::ColorPicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ColorPicker *_t = static_cast<ColorPicker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectedColorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->paletteItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTableWidgetItem*(*)>(_a[2]))); break;
        case 2: _t->setPaletteSelection(); break;
        case 3: _t->redChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->greenChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->blueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->alphaChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ColorPicker::*_t)(QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ColorPicker::selectedColorChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject gui::colorpicker::ColorPicker::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__colorpicker__ColorPicker.data,
      qt_meta_data_gui__colorpicker__ColorPicker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *gui::colorpicker::ColorPicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gui::colorpicker::ColorPicker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_gui__colorpicker__ColorPicker.stringdata0))
        return static_cast<void*>(const_cast< ColorPicker*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::colorpicker::ColorPicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void gui::colorpicker::ColorPicker::selectedColorChanged(QColor _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
