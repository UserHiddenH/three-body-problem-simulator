#ifndef STARTEXPERIENCE_H
#define STARTEXPERIENCE_H

#include <QObject>
#include <QTimer>
#include "simview.h"

//Classe qui sert tout simplement à lancer les simulations avec QTimer

class StartExperience : public QObject
{
    Q_OBJECT
private:
    QTimer  *m_timer;  //timer utilisé pour les expériences
    SimView *m_view;  // pointer vers le widget utilisé pour réaliser les expériences donc ici notre widget qui est lié à la classe SimView

    int m_vitesse = 1; // nombre de sous-pas physiques par tick (1 = normal)
    // Temps physique écoulé depuis le début de l'expérience (en secondes simulées)

    float m_tempsEcoule = 0.0f; //variable qui servira à calculer le temps passé pour une simulation en cours
    double m_EnergieTotale = 0;
protected :
    bool play_pause = true;

public:
    explicit StartExperience(SimView *view, QObject *parent = nullptr);
    void start();
    void stop();

    // Définit le nombre de sous-pas par tick (vitesse × 1 = normal, × N = N fois plus rapide)
    void setVitesse(int vitesse);
    float getTempsEcoule() const;
    void resetTemps(); // remet le compteur à 0 au début d'une nouvelle expérience
    double getEnergieTotale();

private slots:
    void step(); // appelé à chaque tick du timer : calcule + redessine

signals:
    void tempsMAJ(float temps); //signal pour mettre le temps écoulé de la simulation en cours à jour

};

#endif
