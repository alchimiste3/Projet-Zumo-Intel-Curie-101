/****************************************************************************
** Meta object code from reading C++ file 'device.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../device.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Device_t {
    QByteArrayData data[20];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Device_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Device_t qt_meta_stringdata_Device = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Device"
QT_MOC_LITERAL(1, 7, 9), // "majValues"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 16), // "deviceDiscovered"
QT_MOC_LITERAL(4, 35, 20), // "QBluetoothDeviceInfo"
QT_MOC_LITERAL(5, 56, 10), // "deviceInfo"
QT_MOC_LITERAL(6, 67, 18), // "deviceDisconnected"
QT_MOC_LITERAL(7, 86, 15), // "serviceScanDone"
QT_MOC_LITERAL(8, 102, 14), // "QBluetoothUuid"
QT_MOC_LITERAL(9, 117, 11), // "serviceUuid"
QT_MOC_LITERAL(10, 129, 15), // "deviceConnected"
QT_MOC_LITERAL(11, 145, 24), // "serviceDetailsDiscovered"
QT_MOC_LITERAL(12, 170, 31), // "QLowEnergyService::ServiceState"
QT_MOC_LITERAL(13, 202, 30), // "motionServiceDetailsDiscovered"
QT_MOC_LITERAL(14, 233, 28), // "positionCharacteristicUpdate"
QT_MOC_LITERAL(15, 262, 24), // "QLowEnergyCharacteristic"
QT_MOC_LITERAL(16, 287, 2), // "ch"
QT_MOC_LITERAL(17, 290, 9), // "byteArray"
QT_MOC_LITERAL(18, 300, 15), // "envoyerCommande"
QT_MOC_LITERAL(19, 316, 8) // "commande"

    },
    "Device\0majValues\0\0deviceDiscovered\0"
    "QBluetoothDeviceInfo\0deviceInfo\0"
    "deviceDisconnected\0serviceScanDone\0"
    "QBluetoothUuid\0serviceUuid\0deviceConnected\0"
    "serviceDetailsDiscovered\0"
    "QLowEnergyService::ServiceState\0"
    "motionServiceDetailsDiscovered\0"
    "positionCharacteristicUpdate\0"
    "QLowEnergyCharacteristic\0ch\0byteArray\0"
    "envoyerCommande\0commande"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Device[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,   10,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   80,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    1,   84,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    1,   88,    2, 0x0a /* Public */,
      13,    1,   91,    2, 0x0a /* Public */,
      14,    2,   94,    2, 0x0a /* Public */,
      18,    1,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 15, QMetaType::QByteArray,   16,   17,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void Device::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Device *_t = static_cast<Device *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->majValues((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7])),(*reinterpret_cast< float(*)>(_a[8])),(*reinterpret_cast< float(*)>(_a[9])),(*reinterpret_cast< float(*)>(_a[10]))); break;
        case 1: _t->deviceDiscovered((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 2: _t->deviceDisconnected(); break;
        case 3: _t->serviceScanDone((*reinterpret_cast< QBluetoothUuid(*)>(_a[1]))); break;
        case 4: _t->deviceConnected(); break;
        case 5: _t->serviceDetailsDiscovered((*reinterpret_cast< QLowEnergyService::ServiceState(*)>(_a[1]))); break;
        case 6: _t->motionServiceDetailsDiscovered((*reinterpret_cast< QLowEnergyService::ServiceState(*)>(_a[1]))); break;
        case 7: _t->positionCharacteristicUpdate((*reinterpret_cast< QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 8: _t->envoyerCommande((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothUuid >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceState >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Device::*_t)(float , float , float , float , float , float , float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Device::majValues)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Device::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Device.data,
      qt_meta_data_Device,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Device::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Device::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Device.stringdata0))
        return static_cast<void*>(const_cast< Device*>(this));
    return QObject::qt_metacast(_clname);
}

int Device::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Device::majValues(float _t1, float _t2, float _t3, float _t4, float _t5, float _t6, float _t7, float _t8, float _t9, float _t10)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
