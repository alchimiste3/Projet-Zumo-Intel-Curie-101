/****************************************************************************
** Meta object code from reading C++ file 'linechart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../linechart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linechart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LineChart_t {
    QByteArrayData data[9];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LineChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LineChart_t qt_meta_stringdata_LineChart = {
    {
QT_MOC_LITERAL(0, 0, 9), // "LineChart"
QT_MOC_LITERAL(1, 10, 13), // "afficherSerie"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "nomSerie"
QT_MOC_LITERAL(4, 34, 4), // "etat"
QT_MOC_LITERAL(5, 39, 13), // "afficherChart"
QT_MOC_LITERAL(6, 53, 8), // "getColor"
QT_MOC_LITERAL(7, 62, 12), // "ajouterPoint"
QT_MOC_LITERAL(8, 75, 1) // "p"

    },
    "LineChart\0afficherSerie\0\0nomSerie\0"
    "etat\0afficherChart\0getColor\0ajouterPoint\0"
    "p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LineChart[] = {

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
       1,    2,   44,    2, 0x0a /* Public */,
       1,    1,   49,    2, 0x2a /* Public | MethodCloned */,
       1,    0,   52,    2, 0x2a /* Public | MethodCloned */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x0a /* Public */,
       7,    2,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QColor, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QPointF,    3,    8,

       0        // eod
};

void LineChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LineChart *_t = static_cast<LineChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->afficherSerie((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->afficherSerie((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->afficherSerie(); break;
        case 3: _t->afficherChart(); break;
        case 4: { QColor _r = _t->getColor((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 5: _t->ajouterPoint((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject LineChart::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LineChart.data,
      qt_meta_data_LineChart,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LineChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LineChart::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LineChart.stringdata0))
        return static_cast<void*>(const_cast< LineChart*>(this));
    return QObject::qt_metacast(_clname);
}

int LineChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
