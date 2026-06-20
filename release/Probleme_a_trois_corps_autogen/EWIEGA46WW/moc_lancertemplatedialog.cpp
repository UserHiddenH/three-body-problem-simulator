/****************************************************************************
** Meta object code from reading C++ file 'lancertemplatedialog.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lancertemplatedialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lancertemplatedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN20LancerTemplateDialogE_t {};
} // unnamed namespace

template <> constexpr inline auto LancerTemplateDialog::qt_create_metaobjectdata<qt_meta_tag_ZN20LancerTemplateDialogE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LancerTemplateDialog",
        "experienceLancee",
        "",
        "std::vector<Corps>",
        "corps",
        "QMap<int,QColor>",
        "couleurs",
        "modifie",
        "templateEnregistree",
        "ajouterCorps",
        "supprimerCorps",
        "CorpsWidget*",
        "cw",
        "aleatoire",
        "lancer",
        "enregistrer",
        "onModification"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'experienceLancee'
        QtMocHelpers::SignalData<void(std::vector<Corps>, QMap<int,QColor>, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 }, { QMetaType::Bool, 7 },
        }}),
        // Signal 'templateEnregistree'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'ajouterCorps'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'supprimerCorps'
        QtMocHelpers::SlotData<void(CorpsWidget *)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'aleatoire'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'lancer'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'enregistrer'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onModification'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LancerTemplateDialog, qt_meta_tag_ZN20LancerTemplateDialogE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject LancerTemplateDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20LancerTemplateDialogE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20LancerTemplateDialogE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20LancerTemplateDialogE_t>.metaTypes,
    nullptr
} };

void LancerTemplateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LancerTemplateDialog *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->experienceLancee((*reinterpret_cast<std::add_pointer_t<std::vector<Corps>>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QMap<int,QColor>>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        case 1: _t->templateEnregistree(); break;
        case 2: _t->ajouterCorps(); break;
        case 3: _t->supprimerCorps((*reinterpret_cast<std::add_pointer_t<CorpsWidget*>>(_a[1]))); break;
        case 4: _t->aleatoire(); break;
        case 5: _t->lancer(); break;
        case 6: _t->enregistrer(); break;
        case 7: _t->onModification(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CorpsWidget* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LancerTemplateDialog::*)(std::vector<Corps> , QMap<int,QColor> , bool )>(_a, &LancerTemplateDialog::experienceLancee, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LancerTemplateDialog::*)()>(_a, &LancerTemplateDialog::templateEnregistree, 1))
            return;
    }
}

const QMetaObject *LancerTemplateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LancerTemplateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20LancerTemplateDialogE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LancerTemplateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void LancerTemplateDialog::experienceLancee(std::vector<Corps> _t1, QMap<int,QColor> _t2, bool _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void LancerTemplateDialog::templateEnregistree()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
