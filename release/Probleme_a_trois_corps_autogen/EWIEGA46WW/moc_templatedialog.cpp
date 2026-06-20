/****************************************************************************
** Meta object code from reading C++ file 'templatedialog.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../templatedialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'templatedialog.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14TemplateDialogE_t {};
} // unnamed namespace

template <> constexpr inline auto TemplateDialog::qt_create_metaobjectdata<qt_meta_tag_ZN14TemplateDialogE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TemplateDialog",
        "modeleChoisi",
        "",
        "id",
        "experienceLanceeDepuisTemplate",
        "std::vector<Corps>",
        "corps",
        "QMap<int,QColor>",
        "couleurs",
        "modifie",
        "nomTemplate",
        "templateSupprimee",
        "nom",
        "onBtnTerreSoleilClicked",
        "onBtnTerreSoleilLuneClicked",
        "onBtnTerreSoleilMarsClicked",
        "onBtnBiSoleilClicked",
        "onBtnTriSoleilClicked",
        "onBtnBiSoleilPlaneteClicked",
        "onBtnGalaxieClicked",
        "onBtnInfinityClicked",
        "onBtnDoubleBiSoleilClicked",
        "onBtnSystemeSolaireClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'modeleChoisi'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'experienceLanceeDepuisTemplate'
        QtMocHelpers::SignalData<void(std::vector<Corps>, QMap<int,QColor>, bool, QString)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { 0x80000000 | 7, 8 }, { QMetaType::Bool, 9 }, { QMetaType::QString, 10 },
        }}),
        // Signal 'templateSupprimee'
        QtMocHelpers::SignalData<void(QString)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Slot 'onBtnTerreSoleilClicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnTerreSoleilLuneClicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnTerreSoleilMarsClicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnBiSoleilClicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnTriSoleilClicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnBiSoleilPlaneteClicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnGalaxieClicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnInfinityClicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnDoubleBiSoleilClicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnSystemeSolaireClicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TemplateDialog, qt_meta_tag_ZN14TemplateDialogE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TemplateDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14TemplateDialogE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14TemplateDialogE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14TemplateDialogE_t>.metaTypes,
    nullptr
} };

void TemplateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TemplateDialog *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->modeleChoisi((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->experienceLanceeDepuisTemplate((*reinterpret_cast<std::add_pointer_t<std::vector<Corps>>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QMap<int,QColor>>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 2: _t->templateSupprimee((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onBtnTerreSoleilClicked(); break;
        case 4: _t->onBtnTerreSoleilLuneClicked(); break;
        case 5: _t->onBtnTerreSoleilMarsClicked(); break;
        case 6: _t->onBtnBiSoleilClicked(); break;
        case 7: _t->onBtnTriSoleilClicked(); break;
        case 8: _t->onBtnBiSoleilPlaneteClicked(); break;
        case 9: _t->onBtnGalaxieClicked(); break;
        case 10: _t->onBtnInfinityClicked(); break;
        case 11: _t->onBtnDoubleBiSoleilClicked(); break;
        case 12: _t->onBtnSystemeSolaireClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TemplateDialog::*)(int )>(_a, &TemplateDialog::modeleChoisi, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TemplateDialog::*)(std::vector<Corps> , QMap<int,QColor> , bool , QString )>(_a, &TemplateDialog::experienceLanceeDepuisTemplate, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TemplateDialog::*)(QString )>(_a, &TemplateDialog::templateSupprimee, 2))
            return;
    }
}

const QMetaObject *TemplateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TemplateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14TemplateDialogE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int TemplateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void TemplateDialog::modeleChoisi(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TemplateDialog::experienceLanceeDepuisTemplate(std::vector<Corps> _t1, QMap<int,QColor> _t2, bool _t3, QString _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 2
void TemplateDialog::templateSupprimee(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
