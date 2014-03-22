/****************************************************************************
** Meta object code from reading C++ file 'view_new_search.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vis_0/view_new_search.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_new_search.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_view_new_search_t {
    QByteArrayData data[7];
    char stringdata[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_view_new_search_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_view_new_search_t qt_meta_stringdata_view_new_search = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 16),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 16),
QT_MOC_LITERAL(4, 51, 21),
QT_MOC_LITERAL(5, 73, 9),
QT_MOC_LITERAL(6, 83, 7)
    },
    "view_new_search\0write_categories\0\0"
    "QListWidgetItem*\0append_value_to_query\0"
    "do_submit\0do_help\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_view_new_search[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a,
       4,    1,   37,    2, 0x0a,
       5,    0,   40,    2, 0x0a,
       6,    0,   41,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void view_new_search::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        view_new_search *_t = static_cast<view_new_search *>(_o);
        switch (_id) {
        case 0: _t->write_categories((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->append_value_to_query((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->do_submit(); break;
        case 3: _t->do_help(); break;
        default: ;
        }
    }
}

const QMetaObject view_new_search::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_view_new_search.data,
      qt_meta_data_view_new_search,  qt_static_metacall, 0, 0}
};


const QMetaObject *view_new_search::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *view_new_search::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_view_new_search.stringdata))
        return static_cast<void*>(const_cast< view_new_search*>(this));
    return QWidget::qt_metacast(_clname);
}

int view_new_search::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
