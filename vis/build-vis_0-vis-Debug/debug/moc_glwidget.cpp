/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vis_0/glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_glwidget_t {
    QByteArrayData data[15];
    char stringdata[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_glwidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_glwidget_t qt_meta_stringdata_glwidget = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 12),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 8),
QT_MOC_LITERAL(4, 32, 1),
QT_MOC_LITERAL(5, 34, 1),
QT_MOC_LITERAL(6, 36, 7),
QT_MOC_LITERAL(7, 44, 15),
QT_MOC_LITERAL(8, 60, 12),
QT_MOC_LITERAL(9, 73, 5),
QT_MOC_LITERAL(10, 79, 14),
QT_MOC_LITERAL(11, 94, 13),
QT_MOC_LITERAL(12, 108, 10),
QT_MOC_LITERAL(13, 119, 19),
QT_MOC_LITERAL(14, 139, 5)
    },
    "glwidget\0initializeGL\0\0resizeGL\0w\0h\0"
    "paintGL\0mousePressEvent\0QMouseEvent*\0"
    "event\0mouseMoveEvent\0keyPressEvent\0"
    "QKeyEvent*\0set_peel_percentage\0value\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_glwidget[] = {

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
       1,    0,   49,    2, 0x0a,
       3,    2,   50,    2, 0x0a,
       6,    0,   55,    2, 0x0a,
       7,    1,   56,    2, 0x0a,
      10,    1,   59,    2, 0x0a,
      11,    1,   62,    2, 0x0a,
      13,    1,   65,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 12,    9,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void glwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        glwidget *_t = static_cast<glwidget *>(_o);
        switch (_id) {
        case 0: _t->initializeGL(); break;
        case 1: _t->resizeGL((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->paintGL(); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 6: _t->set_peel_percentage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject glwidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_glwidget.data,
      qt_meta_data_glwidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *glwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *glwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_glwidget.stringdata))
        return static_cast<void*>(const_cast< glwidget*>(this));
    if (!strcmp(_clname, "QGLFunctions"))
        return static_cast< QGLFunctions*>(const_cast< glwidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int glwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
