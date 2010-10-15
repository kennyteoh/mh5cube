/****************************************************************************
** Meta object code from reading C++ file 'cubecommunication.h'
**
** Created: Mon 23. Aug 22:53:29 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cubecommunication.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cubecommunication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CubeCommunication[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   19,   18,   18, 0x05,
      57,   18,   18,   18, 0x05,
      81,   18,   18,   18, 0x05,
     113,  101,   18,   18, 0x05,
     147,  101,   18,   18, 0x05,
     177,  101,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     210,  204,   18,   18, 0x0a,
     233,  204,   18,   18, 0x0a,
     269,  254,   18,   18, 0x0a,
     309,  302,   18,   18, 0x0a,
     358,  342,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CubeCommunication[] = {
    "CubeCommunication\0\0percentage\0"
    "programmingPercentage(int)\0"
    "programmingSuccessful()\0programmingFailed()\0"
    "COMPortName\0openingCOMPortSuccessful(QString)\0"
    "openingCOMPortFailed(QString)\0"
    "findingCubeFailed(QString)\0state\0"
    "ConnectionToggle(bool)\0LiveModeToggle(bool)\0"
    "data,countRows\0startProgramming(QByteArray,int)\0"
    "states\0updateLiveModeStates(QBitArray*)\0"
    "nrEffect,looped\0ShowFixedEffects(int,bool)\0"
};

const QMetaObject CubeCommunication::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CubeCommunication,
      qt_meta_data_CubeCommunication, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CubeCommunication::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CubeCommunication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CubeCommunication::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CubeCommunication))
        return static_cast<void*>(const_cast< CubeCommunication*>(this));
    return QObject::qt_metacast(_clname);
}

int CubeCommunication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: programmingPercentage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: programmingSuccessful(); break;
        case 2: programmingFailed(); break;
        case 3: openingCOMPortSuccessful((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: openingCOMPortFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: findingCubeFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: ConnectionToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: LiveModeToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: startProgramming((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: updateLiveModeStates((*reinterpret_cast< QBitArray*(*)>(_a[1]))); break;
        case 10: ShowFixedEffects((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void CubeCommunication::programmingPercentage(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CubeCommunication::programmingSuccessful()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CubeCommunication::programmingFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CubeCommunication::openingCOMPortSuccessful(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CubeCommunication::openingCOMPortFailed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CubeCommunication::findingCubeFailed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
