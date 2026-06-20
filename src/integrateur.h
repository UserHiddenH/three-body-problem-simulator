#ifndef INTEGRATEUR_H
#define INTEGRATEUR_H

#include "vect.h"

class Corps; // forward declaration pour éviter l'include circulaire

class Integrateur
{
public:
    virtual ~Integrateur() = default;

    // calcule la nouvelle position et vitesse du corps
    // prend la position, vitesse et acceleration actuelles
    // retourne la nouvelle vitesse et position via les références
    virtual void calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt) = 0;
};

// ------------------------------------------------------------------
// Euler explicite : calcule vitesse avec ancienne acceleration
// simple mais peu précis, diverge rapidement
// ------------------------------------------------------------------
class EulerExplicite : public Integrateur
{
public:
    void calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt) override;
};

// ------------------------------------------------------------------
// Euler symplectique : calcule vitesse d'abord puis position
// meilleure conservation de l'énergie que l'explicite
// ------------------------------------------------------------------
class EulerSymplectique : public Integrateur
{
public:
    void calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt) override;
};

// ------------------------------------------------------------------
// Runge-Kutta 4 : méthode à 4 étapes
// le plus précis des trois mais le plus coûteux en calcul
// ------------------------------------------------------------------
class RungeKutta4 : public Integrateur
{
public:
    void calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt) override;
};

#endif
