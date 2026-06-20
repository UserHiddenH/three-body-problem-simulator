#include "integrateur.h"

void EulerExplicite::calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt)
{
    // on met à jour la position avec l'ancienne vitesse
    position = position + vitesse * dt;
    // puis la vitesse avec l'acceleration
    vitesse  = vitesse  + acceleration * dt;
}

void EulerSymplectique::calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt)
{
    // on met à jour la vitesse en premier
    vitesse  = vitesse  + acceleration * dt;
    // puis la position avec la nouvelle vitesse
    position = position + vitesse * dt;
}

void RungeKutta4::calculer(Vect &position, Vect &vitesse, const Vect &acceleration, float dt)
{
    /*
        FONCTIONNEMENT DE RUNGE-KUTTA 4

        RK4 estime la dérivée en 4 points du pas de temps
        et fait une moyenne pondérée pour plus de précision.

        Position initiale : x0, Vitesse initiale : v0, Acceleration : a

            t0                    t0 + dt/2                 t0 + dt
            |_________________________|_________________________|
            x0                      x_mid                     x1

        k1 : pente au début du pas
            k1x = v0 * dt
            k1v = a * dt

        k2 : pente au milieu du pas (estimée avec k1)
            k2x = (v0 + k1v/2) * dt
            k2v = a * dt

        k3 : pente au milieu du pas (estimée avec k2)
            k3x = (v0 + k2v/2) * dt
            k3v = a * dt

        k4 : pente à la fin du pas (estimée avec k3)
            k4x = (v0 + k3v) * dt
            k4v = a * dt

        Résultat final = moyenne pondérée des 4 estimations
            x1 = x0 + (k1x + 2*k2x + 2*k3x + k4x) / 6
            v1 = v0 + (k1v + 2*k2v + 2*k3v + k4v) / 6

        Les points du milieu comptent double car ils
        représentent mieux la tendance sur tout le pas.
    */

    Vect k1v = acceleration * dt;
    Vect k1x = vitesse * dt;

    Vect k2v = acceleration * dt;
    Vect k2x = (vitesse + k1v * 0.5f) * dt;

    Vect k3v = acceleration * dt;
    Vect k3x = (vitesse + k2v * 0.5f) * dt;

    Vect k4v = acceleration * dt;
    Vect k4x = (vitesse + k3v) * dt;

    vitesse  = vitesse  + (k1v + k2v * 2.0f + k3v * 2.0f + k4v) * (1.0f / 6.0f);
    position = position + (k1x + k2x * 2.0f + k3x * 2.0f + k4x) * (1.0f / 6.0f);
}
