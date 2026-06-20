#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QColor>
#include <QMap>
#include <QComboBox>
#include "templatedialog.h"
#include "addexperiencedialog.h"
#include "startexperience.h"
#include "historydialog.h"
#include "bodypanel.h"
#include "corps.h"
#include "integrateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    //////////////////////Boutons flottants////////////////////////////////////////
    QPushButton *btnRandom;
    QPushButton *btnResetVue;
    QPushButton *btnPlayPause;
    QPushButton *btnRestart;
    QPushButton *btnVitesse;
    QPushButton *btnGrille;
    QPushButton *btnNoms;
    // btnEnregistrer est maintenant dans le .ui (barre du haut)
    QSlider *sliderVitesse;
    QLabel *labelVitesse;
    QLabel *labelVitesseValeur;
    QLabel *labelTemps;
    QLabel *labelEnergieTotale;
    QLabel *labelEnergieTotaleValeur;
    ///////////////////////////////////////////////////////////////////////////////

    bool play_pause;
    std::vector<Corps> m_modeleActuel;

    // index de l'expérience courante dans l'historique (-1 si pas encore ajoutée)
    int m_indexExperienceCourante = -1;

    //////////////////////Dialogs//////////////////////////////////////////////////
    TemplateDialog *templateDialog;
    AddExperienceDialog *addExperienceDialog;
    HistoryDialog *historyDialog;
    BodyPanel *bodyPanel;
    ///////////////////////////////////////////////////////////////////////////////

    //////////////////////Moteur///////////////////////////////////////////////////
    StartExperience *m_engine;
    ///////////////////////////////////////////////////////////////////////////////

    // vrai quand la simulation vient d'une template prédéfinie ou perso
    // dans ce cas btnEnregistrer est grisé car ça n'a pas de sens
    // de réenregistrer quelque chose qui existe déjà
    bool m_estUneTemplate = false;

    // enregistre l'expérience courante dans l'historique
    void enregistrerDansHistorique(int nbCorps, const std::vector<Corps> &corpsFinals, float duree, const QString &nomTemplate = "");

    // met à jour l'entrée courante dans l'historique comme sauvegardée
    void marquerHistoriqueSauvegarde(const QString &nom);

private slots:
    void onSliderVitesseChanged(int value);
    void chargerModele(int id);
    void onBtnRestartClicked();
    void onBtnPlayPauseClicked();
    void onTempsMAJ(float temps);

    //////////////////////Lancement d'expériences//////////////////////////////////
    void onRelancerDepuisHistorique(int index);
    void onBtnRandomClicked();
    void onExperienceLancee(std::vector<Corps> corps, QMap<int, QColor> couleurs);
    void onTemplateEnregistreeEtLancee(std::vector<Corps> corps);
    void onExperienceLanceeDepuisTemplate(std::vector<Corps> corps, QMap<int, QColor> couleurs, bool modifie, QString nomTemplate);
    ///////////////////////////////////////////////////////////////////////////////

    //////////////////////Gestion d'expériences////////////////////////////////////
    void onBtnEnregistrerClicked();
    void onCorpsClique(int index);
    void onParametresPhysiquesModifies();
    void onSauvegarderDepuisHistorique(int index);
    void onTemplateSupprimee(QString nom);
    void onBtnExportTraceClicked();
    ///////////////////////////////////////////////////////////////////////////////

    //////////////////////Integrateur//////////////////////////////////////////////
    void onIntegrateurChanged(int index);
    //////////////////////////////////////////////////////////////////////////////
};

#endif
