/****************************************************************************
** Meta object code from reading C++ file 'Server_Rollup_Wrapper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Server_Rollup_Wrapper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Server_Rollup_Wrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Server_Rollup_Wrapper_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Server_Rollup_Wrapper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Server_Rollup_Wrapper_t qt_meta_stringdata_Server_Rollup_Wrapper = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Server_Rollup_Wrapper"
QT_MOC_LITERAL(1, 22, 23), // "on_button_start_toggled"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 3), // "tog"
QT_MOC_LITERAL(4, 51, 16), // "acceptConnection"
QT_MOC_LITERAL(5, 68, 8) // "readData"

    },
    "Server_Rollup_Wrapper\0on_button_start_toggled\0"
    "\0tog\0acceptConnection\0readData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server_Rollup_Wrapper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x09 /* Protected */,
       4,    0,   32,    2, 0x09 /* Protected */,
       5,    0,   33,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Server_Rollup_Wrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Server_Rollup_Wrapper *_t = static_cast<Server_Rollup_Wrapper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_button_start_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->acceptConnection(); break;
        case 2: _t->readData(); break;
        default: ;
        }
    }
}

const QMetaObject Server_Rollup_Wrapper::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Server_Rollup_Wrapper.data,
      qt_meta_data_Server_Rollup_Wrapper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Server_Rollup_Wrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server_Rollup_Wrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Server_Rollup_Wrapper.stringdata0))
        return static_cast<void*>(const_cast< Server_Rollup_Wrapper*>(this));
    return QWidget::qt_metacast(_clname);
}

int Server_Rollup_Wrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
