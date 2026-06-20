#include "randomgenerator.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include "corps.h"

//Méthode qui permet de générer un systeme de 2 à 5 corps de façon aléatoire
void RandomGenerator::GenerateRandom() {
    Corps::ResetSystem();//réinitialisation de l'index de corps au début de chaque nouvelle expérience
    std::srand(std::time(nullptr));//permet de ne pas avoir la même séquence de nombres à chaque lancement du programme

    int nbCorps = 2 + (std::rand() % 4); // entre 2 et 5

    for (int i = 0; i < nbCorps; i++) {
        float masse = 800.0f  + (std::rand() % 200);
        float x = -100.0f + (std::rand() % 200);
        float y = -100.0f + (std::rand() % 200);
        float vx = -0.5f + (std::rand() % 10) * 0.1f;
        float vy = -0.5f + (std::rand() % 10) * 0.1f;

        std::string nom = "Corps " + std::to_string(i + 1);
        Corps c(nom, masse, x, y);
        c.VitesseInitiale(vx, vy);
        c.MajIndex();
    }

}

