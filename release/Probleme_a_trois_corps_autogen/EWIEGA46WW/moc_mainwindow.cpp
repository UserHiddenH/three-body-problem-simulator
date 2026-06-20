/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onSliderVitesseChanged",
        "",
        "value",
        "chargerModele",
        "id",
        "onBtnRestartClicked",
        "onBtnPlayPauseClicked",
        "onTempsMAJ",
        "temps",
        "onRelancerDepuisHistorique",
        "index",
        "onBtnRandomClicked",
        "onExperienceLancee",
        "std::vector<Corps>",
        "corps",
        "QMap<int,QColor>",
        "couleurs",
        "onTemplateEnregistreeEtLancee",
        "onExperienceLanceeDepuisTemplate",
        "modifie",
        "nomTemplate",
        "onBtnEnregistrerClicked",
        "onCorpsClique",
        "onParametresPhysiquesModifies",
        "onSauvegarderDepuisHistorique",
        "onTemplateSupprimee",
        "nom",
        "onBtnExportTraceClicked",
        "onIntegrateurChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onSliderVitesseChanged'
        QtMocHelpers::SlotData<void(int)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'chargerModele'
        QtMocHelpers::SlotData<void(int)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Slot 'onBtnRestartClicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtnPlayPauseClicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTempsMAJ'
        QtMocHelpers::SlotData<void(float)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Float, 9 },
        }}),
        // Slot 'onRelancerDepuisHistorique'
        QtMocHelpers::SlotData<void(int)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'onBtnRandomClicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onExperienceLancee'
        QtMocHelpers::SlotData<void(std::vector<Corps>, QMap<int,QColor>)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { 0x80000000 | 16, 17 },
        }}),
        // Slot 'onTemplateEnregistreeEtLancee'
        QtMocHelpers::SlotData<void(std::vector<Corps>)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Slot 'onExperienceLanceeDepuisTemplate'
        QtMocHelpers::SlotData<void(std::vector<Corps>, QMap<int,QColor>, bool, QString)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { 0x80000000 | 16, 17 }, { QMetaType::Bool, 20 }, { QMetaType::QString, 21 },
        }}),
        // Slot 'onBtnEnregistrerClicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCorpsClique'
        QtMocHelpers::SlotData<void(int)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'onParametresPhysiquesModifies'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSauvegarderDepuisHistorique'
        QtMocHelpers::SlotData<void(int)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'onTemplateSupprimee'
        QtMocHelpers::SlotData<void(QString)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Slot 'onBtnExportTraceClicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onIntegrateurChanged'
        QtMocHelpers::SlotData<void(int)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onSliderVitesseChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->chargerModele((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->onBtnRestartClicked(); break;
        case 3: _t->onBtnPlayPauseClicked(); break;
        case 4: _t->onTempsMAJ((*reinterpret_cast<std::add_pointer_t<float>>(_a[1]))); break;
        case 5: _t->onRelancerDepuisHistorique((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->onBtnRandomClicked(); break;
        case 7: _t->onExperienceLancee((*reinterpret_cast<std::add_pointer_t<std::vector<Corps>>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QMap<int,QColor>>>(_a[2]))); break;
        case 8: _t->onTemplateEnregistreeEtLancee((*reinterpret_cast<std::add_pointer_t<std::vector<Corps>>>(_a[1]))); break;
        case 9: _t->onExperienceLanceeDepuisTemplate((*reinterpret_cast<std::add_pointer_t<std::vector<Corps>>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QMap<int,QColor>>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 10: _t->onBtnEnregistrerClicked(); break;
        case 11: _t->onCorpsClique((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->onParametresPhysiquesModifies(); break;
        case 13: _t->onSauvegarderDepuisHistorique((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->onTemplateSupprimee((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->onBtnExportTraceClicked(); break;
        case 16: _t->onIntegrateurChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
