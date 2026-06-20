#ifndef EXPERIENCERECORD_H
#define EXPERIENCERECORD_H

#include <QString>
#include <QDateTime>
#include <vector>
#include "corps.h"

// représente une expérience enregistrée dans l'historique
// chaque lancement de simulation crée un ExperienceRecord
struct ExperienceRecord
{
    QDateTime dateHeure;      // horodatage du lancement
    int nbCorps;              // nombre de corps au lancement
    float dureeTicks;         // durée totale en ticks (temps physique simulé)
    double energieTotale;     // énergie totale à la fin de l'expérience
    bool sauvegardee;         // true si l'expérience a été enregistrée comme template
    QString nomTemplate;      // nom de la template si sauvegardée, vide sinon
    float stabilite;          // indice de stabilité, non calculé pour l'instant
    std::vector<Corps> corps; // snapshot des corps pour export de trace
    std::vector<Corps> corpsInitiaux; // corps au lancement — pour relancer à l'identique
};

#endif
