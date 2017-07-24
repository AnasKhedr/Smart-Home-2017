/****************************************************************************
** Meta object code from reading C++ file 'writewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/writewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'writewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WriteWindow_t {
    QByteArrayData data[10];
    char stringdata[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WriteWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WriteWindow_t qt_meta_stringdata_WriteWindow = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 25),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 5),
QT_MOC_LITERAL(4, 45, 28),
QT_MOC_LITERAL(5, 74, 4),
QT_MOC_LITERAL(6, 79, 38),
QT_MOC_LITERAL(7, 118, 29),
QT_MOC_LITERAL(8, 148, 32),
QT_MOC_LITERAL(9, 181, 31)
    },
    "WriteWindow\0on_dial_temp_valueChanged\0"
    "\0value\0on_spinBox_temp_valueChanged\0"
    "arg1\0on_horizontalSlider_light_valueChanged\0"
    "on_spinBox_light_valueChanged\0"
    "on_pushButton_send_light_clicked\0"
    "on_pushButton_send_temp_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WriteWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       6,    1,   50,    2, 0x08 /* Private */,
       7,    1,   53,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WriteWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WriteWindow *_t = static_cast<WriteWindow *>(_o);
        switch (_id) {
        case 0: _t->on_dial_temp_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_spinBox_temp_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_horizontalSlider_light_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_spinBox_light_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_send_light_clicked(); break;
        case 5: _t->on_pushButton_send_temp_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject WriteWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WriteWindow.data,
      qt_meta_data_WriteWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *WriteWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WriteWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WriteWindow.stringdata))
        return static_cast<void*>(const_cast< WriteWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int WriteWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
