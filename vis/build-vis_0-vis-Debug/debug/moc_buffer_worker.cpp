/****************************************************************************
** Meta object code from reading C++ file 'buffer_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vis_0/buffer_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buffer_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_buffer_worker_t {
    QByteArrayData data[6];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_buffer_worker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_buffer_worker_t qt_meta_stringdata_buffer_worker = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 8),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 5),
QT_MOC_LITERAL(4, 30, 3),
QT_MOC_LITERAL(5, 34, 7)
    },
    "buffer_worker\0finished\0\0error\0err\0"
    "process\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_buffer_worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06,
       3,    1,   30,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void buffer_worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        buffer_worker *_t = static_cast<buffer_worker *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (buffer_worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&buffer_worker::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (buffer_worker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&buffer_worker::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject buffer_worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_buffer_worker.data,
      qt_meta_data_buffer_worker,  qt_static_metacall, 0, 0}
};


const QMetaObject *buffer_worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *buffer_worker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_buffer_worker.stringdata))
        return static_cast<void*>(const_cast< buffer_worker*>(this));
    return QObject::qt_metacast(_clname);
}

int buffer_worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void buffer_worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void buffer_worker::error(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
