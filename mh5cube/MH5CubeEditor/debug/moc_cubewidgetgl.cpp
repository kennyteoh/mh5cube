/****************************************************************************
** Meta object code from reading C++ file 'cubewidgetgl.h'
**
** Created: Wed 29. Sep 22:25:17 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cubewidgetgl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cubewidgetgl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CubeWidgetGL[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,
      53,   47,   13,   13, 0x05,
      75,   47,   13,   13, 0x05,
      97,   47,   13,   13, 0x05,
     124,  119,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     151,  141,   13,   13, 0x0a,
     173,   47,   13,   13, 0x0a,
     191,   47,   13,   13, 0x0a,
     209,   47,   13,   13, 0x0a,
     227,  119,   13,   13, 0x0a,
     240,   13,   13,   13, 0x0a,
     256,   13,   13,   13, 0x0a,
     269,   13,   13,   13, 0x0a,
     288,   13,   13,   13, 0x0a,
     297,   13,   13,   13, 0x0a,
     308,   13,   13,   13, 0x0a,
     320,   13,   13,   13, 0x0a,
     332,   13,   13,   13, 0x0a,
     355,   13,   13,   13, 0x0a,
     385,  379,   13,   13, 0x0a,
     404,  400,   13,   13, 0x0a,
     421,  417,   13,   13, 0x0a,
     434,   13,   13,   13, 0x0a,
     446,   13,   13,   13, 0x0a,
     459,   13,   13,   13, 0x0a,
     471,   13,   13,   13, 0x0a,
     484,   13,   13,   13, 0x0a,
     496,   13,   13,   13, 0x0a,
     509,   13,   13,   13, 0x0a,
     523,   13,   13,   13, 0x0a,
     538,   13,   13,   13, 0x0a,
     552,   13,   13,   13, 0x0a,
     567,   13,   13,   13, 0x0a,
     581,   13,   13,   13, 0x0a,
     602,  596,   13,   13, 0x0a,
     625,  596,   13,   13, 0x0a,
     646,  596,   13,   13, 0x0a,
     667,   13,   13,   13, 0x0a,
     685,  679,   13,   13, 0x0a,
     714,  709,   13,   13, 0x0a,
     738,  596,   13,   13, 0x0a,
     760,   13,   13,   13, 0x0a,
     780,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CubeWidgetGL[] = {
    "CubeWidgetGL\0\0states\0statesChanged(QBitArray*)\0"
    "angle\0xRotationChanged(int)\0"
    "yRotationChanged(int)\0zRotationChanged(int)\0"
    "zoom\0zoomChanged(int)\0newStates\0"
    "setStates(QBitArray*)\0setXRotation(int)\0"
    "setYRotation(int)\0setZRotation(int)\0"
    "setZoom(int)\0resetRotation()\0updateCube()\0"
    "updateBackground()\0setAll()\0unsetAll()\0"
    "setRandom()\0setInvert()\0setCurrentLayersTrue()\0"
    "setCurrentLayersFalse()\0level\0"
    "setSLevel(int)\0col\0setSCol(int)\0row\0"
    "setSRow(int)\0moveXPlus()\0moveXMinus()\0"
    "moveYPlus()\0moveYMinus()\0moveZPlus()\0"
    "moveZMinus()\0rotateXPlus()\0rotateXMinus()\0"
    "rotateYPlus()\0rotateYMinus()\0rotateZPlus()\0"
    "rotateZMinus()\0state\0setSLevelEnabled(bool)\0"
    "setSRowEnabled(bool)\0setSColEnabled(bool)\0"
    "showDebug()\0ortho\0togglePerspective(bool)\0"
    "show\0toggleCoordinates(bool)\0"
    "toggleNightMode(bool)\0defaultGLSettings()\0"
    "setGLSettings(GLSettings)\0"
};

const QMetaObject CubeWidgetGL::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_CubeWidgetGL,
      qt_meta_data_CubeWidgetGL, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CubeWidgetGL::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CubeWidgetGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CubeWidgetGL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CubeWidgetGL))
        return static_cast<void*>(const_cast< CubeWidgetGL*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int CubeWidgetGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: statesChanged((*reinterpret_cast< QBitArray*(*)>(_a[1]))); break;
        case 1: xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: zoomChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setStates((*reinterpret_cast< QBitArray*(*)>(_a[1]))); break;
        case 6: setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: resetRotation(); break;
        case 11: updateCube(); break;
        case 12: updateBackground(); break;
        case 13: setAll(); break;
        case 14: unsetAll(); break;
        case 15: setRandom(); break;
        case 16: setInvert(); break;
        case 17: setCurrentLayersTrue(); break;
        case 18: setCurrentLayersFalse(); break;
        case 19: setSLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: setSCol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: setSRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: moveXPlus(); break;
        case 23: moveXMinus(); break;
        case 24: moveYPlus(); break;
        case 25: moveYMinus(); break;
        case 26: moveZPlus(); break;
        case 27: moveZMinus(); break;
        case 28: rotateXPlus(); break;
        case 29: rotateXMinus(); break;
        case 30: rotateYPlus(); break;
        case 31: rotateYMinus(); break;
        case 32: rotateZPlus(); break;
        case 33: rotateZMinus(); break;
        case 34: setSLevelEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: setSRowEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: setSColEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: showDebug(); break;
        case 38: togglePerspective((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: toggleCoordinates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: toggleNightMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: defaultGLSettings(); break;
        case 42: setGLSettings((*reinterpret_cast< GLSettings(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void CubeWidgetGL::statesChanged(QBitArray * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CubeWidgetGL::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CubeWidgetGL::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CubeWidgetGL::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CubeWidgetGL::zoomChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
