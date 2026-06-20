#ifndef CORPS_H
#define CORPS_H

#include "vect.h"
#include "integrateur.h"
#include <string>
#include <vector>
#include <QColor>
#include <QMap>


class Corps
{

private :
    int numero; //Chaque corps a une variable locale unique pour pouvoir le distingué de tous les autre corps
    static std ::vector<Corps>index; //tableau dynamique contenant tous les corps pour une expérience
    static int nb_corps;
    static int dernier_num;
    std::string nom;
    float masse;
    Vect position;
    Vect vitesse;
    std::vector<Vect> trace; // stocke les anciennes positions du corps pour dessiner sa trajectoire
    static float energie_potentielle;
    static float energie_cinetique;

    //variables d'instances relatives au calcul des tours d'un corps
    int quadrant = 0;
    int sens = 0;
    int compteur = 0;
    int nbTours = 0;


public :
    static constexpr float DT = 0.01f; // constante de classe, accessible partout

    Corps(std::string nom, float masse, float x, float y);
    Corps(std::string nom, float masse, float x, float y, Vect); //Constructeur AVEC vitesse initiale
    void UpdatePosition(float new_x, float new_y); //met à jour les coordonnées avec des valeurs quelconques
    void Calc_Position(); //met à jour les coordonnées grâce à l'accélération en appelant UpdatePosition().
    Vect Acceleration();
    void Affiche();
    void MajIndex();//Met à jour le tableau dynamique de corps lors de l'ajout d'un nouveau corps
    void VitesseInitiale(float, float);
    const std::vector<Vect>& GetTrace() const; // retourne la trace du corps pour que simview puisse la dessiner
    void resetTrace(); // réinitialise les traces du corps (utilisé par BodyPanel)

    static void setIntegrateur(Integrateur *integrateur); // change l'intégrateur pour tous les corps
    static Integrateur *s_integrateur; // partagé entre tous les corps via static

    static void ResetSystem(); //réinitialise le tableau dynamique de corps
    static std::vector<Corps>& GetIndex();
    static int GetNbCorps();
    Vect GetPosition() const;
    Vect GetVitesse() const;
    // ---
    float GetMasse() const;
    float getMasse(); // alias minuscule utilisé par BodyPanel
    std::string GetNom() const;
    void setNom(std::string nom);
    void setMasse(float masse);
    void setVitesse(float vx, float vy);

    //méthodes relatives à l'énergie
    double CalcCinetique() const;
    static double CalcPotentielle();
    static void MajCinetique(double);
    static void MajPotentielle(double);
    static double GetCinetique();
    static double GetPotentielle();

    //méthodes relatives au calcul des tours d'un corps
    void CalcTours();
    int GetNbTours() const;
};

#endif
