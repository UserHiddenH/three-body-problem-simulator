#ifndef VECT_H
#define VECT_H

class Vect
{
private :
    float x;
    float y;

public:
    Vect(); //constructeur par défaut sans arguement
    Vect(float x, float y); //constructeur avec arguement
    void UpdatePosition(float new_x, float new_y);//met à jour le vecteur position pour un vecteur
    float Norme() const; //méthode permettant de calculer la norme du vecteur
    Vect operator+(Vect v2) const; //surcharge de l'opérateur "+"
    Vect operator*(float lambda) const; //surcharge de l'opérateur "*"
    void Affiche();
    float GetX() const {return x;}
    float GetY() const {return y;}
};

#endif
