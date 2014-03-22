/****************************************************************************
** Meta object code from reading C++ file 'view_search.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vis_0/view_search.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_search.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_view_search_t {
    QByteArrayData data[15];
    char stringdata[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_view_search_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_view_search_t qt_meta_stringdata_view_search = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 18),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 6),
QT_MOC_LITERAL(4, 39, 11),
QT_MOC_LITERAL(5, 51, 8),
QT_MOC_LITERAL(6, 60, 11),
QT_MOC_LITERAL(7, 72, 9),
QT_MOC_LITERAL(8, 82, 9),
QT_MOC_LITERAL(9, 92, 10),
QT_MOC_LITERAL(10, 103, 11),
QT_MOC_LITERAL(11, 115, 20),
QT_MOC_LITERAL(12, 136, 21),
QT_MOC_LITERAL(13, 158, 15),
QT_MOC_LITERAL(14, 174, 5)
    },
    "view_search\0search_highlighted\0\0result\0"
    "func_rename\0func_new\0func_delete\0"
    "func_edit\0func_draw\0func_stats\0"
    "func_linear\0func_view_new_search\0"
    "func_view_edit_search\0onColumnChanged\0"
    "index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_view_search[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a,
       4,    0,   72,    2, 0x0a,
       5,    0,   73,    2, 0x0a,
       6,    0,   74,    2, 0x0a,
       7,    0,   75,    2, 0x0a,
       8,    0,   76,    2, 0x0a,
       9,    0,   77,    2, 0x0a,
      10,    0,   78,    2, 0x0a,
      11,    0,   79,    2, 0x0a,
      12,    0,   80,    2, 0x0a,
      13,    1,   81,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   14,

       0        // eod
};

void view_search::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        view_search *_t = static_cast<view_search *>(_o);
        switch (_id) {
        case 0: _t->search_highlighted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->func_rename(); break;
        case 2: _t->func_new(); break;
        case 3: _t->func_delete(); break;
        case 4: _t->func_edit(); break;
        case 5: _t->func_draw(); break;
        case 6: _t->func_stats(); break;
        case 7: _t->func_linear(); break;
        case 8: _t->func_view_new_search(); break;
        case 9: _t->func_view_edit_search(); break;
        case 10: _t->onColumnChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject view_search::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_view_search.data,
      qt_meta_data_view_search,  qt_static_metacall, 0, 0}
};


const QMetaObject *view_search::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *view_search::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_view_search.stringdata))
        return static_cast<void*>(const_cast< view_search*>(this));
    return QWidget::qt_metacast(_clname);
}

int view_search::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
