#include "startexperience.h"
#include "corps.h"
/*
SCHEMA DE FONCTIONNEMENT DE LA CLASSE
timer tick (toutes les 16ms)
        ↓
    step() appelé
        ↓
    calcule nouvelles positions de tous les corps
        ↓
    redessine SimView
        ↓
    attends 16ms...
        ↓
    step() appelé
        ↓
    ...

*/

//Les deux paramètres en entrée sont : sur quoi on réalise la simulation, donc SimView, et sur quel fenêtre la simulatio est donc MainWindow
StartExperience::StartExperience(SimView *view, QObject *parent) : QObject(parent){
    m_view =view;//on récupère ici la fenêtre de simulation
    m_timer= new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
}

void StartExperience::start()
{
    m_timer->start(16); // tick toutes les 16ms (~60fps)
}

void StartExperience::stop()
{
    m_timer->stop();
}

void StartExperience::step()//permet de lancer des expériences et de calculé les positions et l'énergie cinétique des différents corps de l'expérience
{
    float cinetique = 0;
    // Sécurité : on ne calcule rien s'il n'y a pas de corps
    if (Corps::GetNbCorps() == 0) return;
    std::vector<Corps>& bodies = Corps::GetIndex();
    int n = Corps::GetNbCorps();

    // On répète le calcul m_vitesse fois pour accélérer sans changer DT
    // Cela préserve la précision numérique de l'intégrateur
    for (int s = 0; s < m_vitesse; s++) {
        cinetique = 0;
        for (int i = 0; i < n; i++) {
            bodies[i].Calc_Position();
            cinetique+=bodies[i].CalcCinetique();
        }
        Corps::MajPotentielle(Corps::CalcPotentielle());
        Corps::MajCinetique(cinetique);
        m_EnergieTotale = Corps::GetPotentielle()+Corps::GetCinetique();

    }
    // On incrémente le temps physique en tenant compte de la vitesse
    m_tempsEcoule += Corps::DT * m_vitesse;
    emit tempsMAJ(m_tempsEcoule);
    m_view->update(); // un seul rendu par tick pour garder ~60fps
}

double StartExperience:: getEnergieTotale(){//retourne l'énergie totale du système calculer dans la méthode step
    return m_EnergieTotale;
}


void StartExperience::setVitesse(int vitesse)
{
    // On s'assure que la vitesse est au moins 1 (jamais 0 sous-pas)
    m_vitesse = qMax(1, vitesse);
}

float StartExperience::getTempsEcoule() const {
    return m_tempsEcoule;
}

void StartExperience::resetTemps() {
    m_tempsEcoule = 0.0f;
}

