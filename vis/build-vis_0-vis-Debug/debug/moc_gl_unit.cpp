/****************************************************************************
** Meta object code from reading C++ file 'gl_unit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vis_0/gl_unit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gl_unit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_gl_unit_t {
    QByteArrayData data[16];
    char stringdata[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_gl_unit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_gl_unit_t qt_meta_stringdata_gl_unit = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 15),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 20),
QT_MOC_LITERAL(4, 46, 4),
QT_MOC_LITERAL(5, 51, 12),
QT_MOC_LITERAL(6, 64, 8),
QT_MOC_LITERAL(7, 73, 1),
QT_MOC_LITERAL(8, 75, 1),
QT_MOC_LITERAL(9, 77, 7),
QT_MOC_LITERAL(10, 85, 15),
QT_MOC_LITERAL(11, 101, 12),
QT_MOC_LITERAL(12, 114, 5),
QT_MOC_LITERAL(13, 120, 14),
QT_MOC_LITERAL(14, 135, 13),
QT_MOC_LITERAL(15, 149, 10)
    },
    "gl_unit\0set_visual_unit\0\0visual_unit_gl_info*\0"
    "info\0initializeGL\0resizeGL\0w\0h\0paintGL\0"
    "mousePressEvent\0QMouseEvent*\0event\0"
    "mouseMoveEvent\0keyPressEvent\0QKeyEvent*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gl_unit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a,
       5,    0,   52,    2, 0x0a,
       6,    2,   53,    2, 0x0a,
       9,    0,   58,    2, 0x0a,
      10,    1,   59,    2, 0x0a,
      13,    1,   62,    2, 0x0a,
      14,    1,   65,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 15,   12,

       0        // eod
};

void gl_unit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gl_unit *_t = static_cast<gl_unit *>(_o);
        switch (_id) {
        case 0: _t->set_visual_unit((*reinterpret_cast< visual_unit_gl_info*(*)>(_a[1]))); break;
        case 1: _t->initializeGL(); break;
        case 2: _t->resizeGL((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->paintGL(); break;
        case 4: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject gl_unit::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_gl_unit.data,
      qt_meta_data_gl_unit,  qt_static_metacall, 0, 0}
};


const QMetaObject *gl_unit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gl_unit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gl_unit.stringdata))
        return static_cast<void*>(const_cast< gl_unit*>(this));
    if (!strcmp(_clname, "QGLFunctions"))
        return static_cast< QGLFunctions*>(const_cast< gl_unit*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int gl_unit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
