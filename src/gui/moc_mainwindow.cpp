/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Dec 16 05:44:10 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x0a,
      46,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      73,   11,   11,   11, 0x08,
      87,   11,   11,   11, 0x08,
     102,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     116,   11,   11,   11, 0x08,
     122,   11,   11,   11, 0x08,
     129,   11,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     145,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0executeTclCommand()\0"
    "updateModel()\0newProject()\0openProject()\0"
    "saveProject()\0closeProject()\0undo()\0"
    "redo()\0cut()\0copy()\0paste()\0about()\0"
    "help()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->executeTclCommand(); break;
        case 1: _t->updateModel(); break;
        case 2: _t->newProject(); break;
        case 3: _t->openProject(); break;
        case 4: _t->saveProject(); break;
        case 5: _t->closeProject(); break;
        case 6: _t->undo(); break;
        case 7: _t->redo(); break;
        case 8: _t->cut(); break;
        case 9: _t->copy(); break;
        case 10: _t->paste(); break;
        case 11: _t->about(); break;
        case 12: _t->help(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
