/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[32];
    char stringdata0[388];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "ajouterPoint"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "nomSerie"
QT_MOC_LITERAL(4, 34, 5), // "point"
QT_MOC_LITERAL(5, 40, 13), // "afficherSerie"
QT_MOC_LITERAL(6, 54, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 76, 7), // "checked"
QT_MOC_LITERAL(8, 84, 12), // "redMajValues"
QT_MOC_LITERAL(9, 97, 3), // "yaw"
QT_MOC_LITERAL(10, 101, 2), // "ax"
QT_MOC_LITERAL(11, 104, 2), // "ay"
QT_MOC_LITERAL(12, 107, 2), // "az"
QT_MOC_LITERAL(13, 110, 2), // "vx"
QT_MOC_LITERAL(14, 113, 2), // "vy"
QT_MOC_LITERAL(15, 116, 2), // "vz"
QT_MOC_LITERAL(16, 119, 2), // "px"
QT_MOC_LITERAL(17, 122, 2), // "py"
QT_MOC_LITERAL(18, 125, 2), // "pz"
QT_MOC_LITERAL(19, 128, 24), // "on_ajouterButton_clicked"
QT_MOC_LITERAL(20, 153, 11), // "redAccepted"
QT_MOC_LITERAL(21, 165, 26), // "on_supprimerButton_clicked"
QT_MOC_LITERAL(22, 192, 24), // "on_envoyerButton_clicked"
QT_MOC_LITERAL(23, 217, 16), // "redButtonToggled"
QT_MOC_LITERAL(24, 234, 2), // "id"
QT_MOC_LITERAL(25, 237, 4), // "etat"
QT_MOC_LITERAL(26, 242, 26), // "on_apprendreButton_clicked"
QT_MOC_LITERAL(27, 269, 28), // "redAcceptedCommandeApprendre"
QT_MOC_LITERAL(28, 298, 28), // "on_reconnaitreButton_clicked"
QT_MOC_LITERAL(29, 327, 34), // "on_reexucuterActionsButton_cl..."
QT_MOC_LITERAL(30, 362, 19), // "redMajReconaissance"
QT_MOC_LITERAL(31, 382, 5) // "value"

    },
    "MainWindow\0ajouterPoint\0\0nomSerie\0"
    "point\0afficherSerie\0on_pushButton_clicked\0"
    "checked\0redMajValues\0yaw\0ax\0ay\0az\0vx\0"
    "vy\0vz\0px\0py\0pz\0on_ajouterButton_clicked\0"
    "redAccepted\0on_supprimerButton_clicked\0"
    "on_envoyerButton_clicked\0redButtonToggled\0"
    "id\0etat\0on_apprendreButton_clicked\0"
    "redAcceptedCommandeApprendre\0"
    "on_reconnaitreButton_clicked\0"
    "on_reexucuterActionsButton_clicked\0"
    "redMajReconaissance\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       5,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   92,    2, 0x08 /* Private */,
       8,   10,   95,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    0,  117,    2, 0x08 /* Private */,
      21,    0,  118,    2, 0x08 /* Private */,
      22,    0,  119,    2, 0x08 /* Private */,
      23,    2,  120,    2, 0x08 /* Private */,
      26,    0,  125,    2, 0x08 /* Private */,
      27,    0,  126,    2, 0x08 /* Private */,
      28,    1,  127,    2, 0x08 /* Private */,
      29,    1,  130,    2, 0x08 /* Private */,
      30,    1,  133,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QPointF,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,   31,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ajouterPoint((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 1: _t->afficherSerie((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->redMajValues((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7])),(*reinterpret_cast< float(*)>(_a[8])),(*reinterpret_cast< float(*)>(_a[9])),(*reinterpret_cast< float(*)>(_a[10]))); break;
        case 4: _t->on_ajouterButton_clicked(); break;
        case 5: _t->redAccepted(); break;
        case 6: _t->on_supprimerButton_clicked(); break;
        case 7: _t->on_envoyerButton_clicked(); break;
        case 8: _t->redButtonToggled((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->on_apprendreButton_clicked(); break;
        case 10: _t->redAcceptedCommandeApprendre(); break;
        case 11: _t->on_reconnaitreButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_reexucuterActionsButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->redMajReconaissance((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QString , QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::ajouterPoint)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::afficherSerie)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::ajouterPoint(QString _t1, QPointF _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::afficherSerie(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
