/****************************************************************************
** Meta object code from reading C++ file 'jkqtmathtext.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jkqtmathtext.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jkqtmathtext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JKQTmathText_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JKQTmathText_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JKQTmathText_t qt_meta_stringdata_JKQTmathText = {
    {
QT_MOC_LITERAL(0, 0, 12) // "JKQTmathText"

    },
    "JKQTmathText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JKQTmathText[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void JKQTmathText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject JKQTmathText::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JKQTmathText.data,
      qt_meta_data_JKQTmathText,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JKQTmathText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JKQTmathText::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JKQTmathText.stringdata0))
        return static_cast<void*>(const_cast< JKQTmathText*>(this));
    return QObject::qt_metacast(_clname);
}

int JKQTmathText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_JKQTMathTextLabel_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JKQTMathTextLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JKQTMathTextLabel_t qt_meta_stringdata_JKQTMathTextLabel = {
    {
QT_MOC_LITERAL(0, 0, 17) // "JKQTMathTextLabel"

    },
    "JKQTMathTextLabel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JKQTMathTextLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void JKQTMathTextLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject JKQTMathTextLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_JKQTMathTextLabel.data,
      qt_meta_data_JKQTMathTextLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JKQTMathTextLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JKQTMathTextLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JKQTMathTextLabel.stringdata0))
        return static_cast<void*>(const_cast< JKQTMathTextLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int JKQTMathTextLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
