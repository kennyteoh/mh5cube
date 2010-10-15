/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed 29. Sep 22:25:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   16,   12,   11, 0x0a,
      49,   11,   12,   11, 0x0a,
      71,   11,   12,   11, 0x0a,
     111,   93,   12,   11, 0x0a,
     148,  138,   12,   11, 0x2a,
     171,   11,   12,   11, 0x2a,
     199,  191,   12,   11, 0x0a,
     219,   11,   12,   11, 0x0a,
     232,   11,   12,   11, 0x0a,
     244,   11,   12,   11, 0x0a,
     259,   11,   12,   11, 0x0a,
     273,   11,   12,   11, 0x0a,
     288,   11,   12,   11, 0x0a,
     305,   11,   12,   11, 0x0a,
     322,  320,   12,   11, 0x0a,
     364,   11,   11,   11, 0x0a,
     381,   11,   11,   11, 0x0a,
     400,   11,   11,   11, 0x0a,
     421,   11,   11,   11, 0x0a,
     441,   11,   11,   11, 0x0a,
     474,  462,   11,   11, 0x0a,
     504,  462,   11,   11, 0x0a,
     535,  462,   11,   11, 0x0a,
     562,   11,   11,   11, 0x0a,
     589,   11,   11,   11, 0x0a,
     605,   11,   11,   11, 0x0a,
     620,   11,   11,   11, 0x0a,
     638,   11,   11,   11, 0x0a,
     650,   11,   11,   11, 0x0a,
     660,   11,   11,   11, 0x0a,
     671,   11,   11,   11, 0x0a,
     684,   11,   11,   11, 0x0a,
     695,   11,   11,   11, 0x0a,
     708,   11,   11,   11, 0x0a,
     716,   11,   11,   11, 0x0a,
     727,   11,   11,   11, 0x0a,
     738,   11,   11,   11, 0x0a,
     759,   11,   11,   11, 0x0a,
     777,   11,   11,   11, 0x0a,
     810,   11,   11,   11, 0x0a,
     850,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0int\0states\0statesChanged(QBitArray*)\0"
    "FigureTimesIncrease()\0FigureTimesDecrease()\0"
    "increment,fixtime\0FigureTimesChange(int,int)\0"
    "increment\0FigureTimesChange(int)\0"
    "FigureTimesChange()\0newTime\0"
    "FigureTimesSet(int)\0FigurePlay()\0"
    "FigureAdd()\0FigureInsert()\0FigureClone()\0"
    "FigureMoveUp()\0FigureMoveDown()\0"
    "FigureDelete()\0,\0"
    "CopyFigureToCube(QModelIndex,QModelIndex)\0"
    "generateOutput()\0showFixedEffects()\0"
    "prepareProgramming()\0failedProgramming()\0"
    "successProgramming()\0COMPortName\0"
    "failedOpeningCOMPort(QString)\0"
    "successOpeningCOMPort(QString)\0"
    "failedFindingCube(QString)\0"
    "FillFixedEffectsComboBox()\0writeSettings()\0"
    "readSettings()\0defaultSettings()\0"
    "selectAll()\0FileNew()\0FileSave()\0"
    "FileSaveAs()\0FileOpen()\0FileAppend()\0"
    "About()\0openFile()\0saveFile()\0"
    "openSettingsDialog()\0openTimesDialog()\0"
    "updateGLSettingsCube(GLSettings)\0"
    "updateGLSettingsCubePreview(GLSettings)\0"
    "TimeOut()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = statesChanged((*reinterpret_cast< QBitArray*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = FigureTimesIncrease();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = FigureTimesDecrease();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = FigureTimesChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = FigureTimesChange((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = FigureTimesChange();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = FigureTimesSet((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { int _r = FigurePlay();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = FigureAdd();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { int _r = FigureInsert();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { int _r = FigureClone();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = FigureMoveUp();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = FigureMoveDown();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { int _r = FigureDelete();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = CopyFigureToCube((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: generateOutput(); break;
        case 16: showFixedEffects(); break;
        case 17: prepareProgramming(); break;
        case 18: failedProgramming(); break;
        case 19: successProgramming(); break;
        case 20: failedOpeningCOMPort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: successOpeningCOMPort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: failedFindingCube((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: FillFixedEffectsComboBox(); break;
        case 24: writeSettings(); break;
        case 25: readSettings(); break;
        case 26: defaultSettings(); break;
        case 27: selectAll(); break;
        case 28: FileNew(); break;
        case 29: FileSave(); break;
        case 30: FileSaveAs(); break;
        case 31: FileOpen(); break;
        case 32: FileAppend(); break;
        case 33: About(); break;
        case 34: openFile(); break;
        case 35: saveFile(); break;
        case 36: openSettingsDialog(); break;
        case 37: openTimesDialog(); break;
        case 38: updateGLSettingsCube((*reinterpret_cast< GLSettings(*)>(_a[1]))); break;
        case 39: updateGLSettingsCubePreview((*reinterpret_cast< GLSettings(*)>(_a[1]))); break;
        case 40: TimeOut(); break;
        default: ;
        }
        _id -= 41;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
