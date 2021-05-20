/****************************************************************************
** Meta object code from reading C++ file 'axisinfoui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HS-P66/Form/axisinfoui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'axisinfoui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AxisInfoUI_t {
    QByteArrayData data[11];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AxisInfoUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AxisInfoUI_t qt_meta_stringdata_AxisInfoUI = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AxisInfoUI"
QT_MOC_LITERAL(1, 11, 6), // "RunORG"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "RunSon"
QT_MOC_LITERAL(4, 26, 8), // "RunReSet"
QT_MOC_LITERAL(5, 35, 7), // "RunLeft"
QT_MOC_LITERAL(6, 43, 8), // "RunRight"
QT_MOC_LITERAL(7, 52, 14), // "RunQuickFixPos"
QT_MOC_LITERAL(8, 67, 7), // "RunStop"
QT_MOC_LITERAL(9, 75, 7), // "EmgStop"
QT_MOC_LITERAL(10, 83, 16) // "timerUpInputData"

    },
    "AxisInfoUI\0RunORG\0\0RunSon\0RunReSet\0"
    "RunLeft\0RunRight\0RunQuickFixPos\0RunStop\0"
    "EmgStop\0timerUpInputData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AxisInfoUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AxisInfoUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AxisInfoUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RunORG(); break;
        case 1: _t->RunSon(); break;
        case 2: _t->RunReSet(); break;
        case 3: _t->RunLeft(); break;
        case 4: _t->RunRight(); break;
        case 5: _t->RunQuickFixPos(); break;
        case 6: _t->RunStop(); break;
        case 7: _t->EmgStop(); break;
        case 8: _t->timerUpInputData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AxisInfoUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AxisInfoUI.data,
    qt_meta_data_AxisInfoUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AxisInfoUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AxisInfoUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AxisInfoUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AxisInfoUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
