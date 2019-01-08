/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created: Sat May 26 19:15:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../multi_vlc_qt/player.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Player[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    8,    7,    7, 0x0a,
      31,    7,    7,    7, 0x0a,
      59,   49,    7,    7, 0x0a,
      89,   77,    7,    7, 0x0a,
     118,  109,    7,    7, 0x0a,
     129,    7,    7,    7, 0x0a,
     136,    7,    7,    7, 0x0a,
     150,    7,    7,    7, 0x0a,
     172,    7,  166,    7, 0x0a,
     197,    7,  182,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Player[] = {
    "Player\0\0file\0playFile(QString)\0"
    "updateInterface()\0newVolume\0"
    "changeVolume(int)\0newPosition\0"
    "changePosition(int)\0do_pause\0pause(int)\0"
    "play()\0test_expire()\0banner_expire()\0"
    "QRect\0getSize()\0libvlc_state_t\0"
    "getState()\0"
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Player *_t = static_cast<Player *>(_o);
        switch (_id) {
        case 0: _t->playFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateInterface(); break;
        case 2: _t->changeVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changePosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->pause((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->play(); break;
        case 6: _t->test_expire(); break;
        case 7: _t->banner_expire(); break;
        case 8: { QRect _r = _t->getSize();
            if (_a[0]) *reinterpret_cast< QRect*>(_a[0]) = _r; }  break;
        case 9: { libvlc_state_t _r = _t->getState();
            if (_a[0]) *reinterpret_cast< libvlc_state_t*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Player::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Player::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Player,
      qt_meta_data_Player, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Player::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Player))
        return static_cast<void*>(const_cast< Player*>(this));
    return QWidget::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
