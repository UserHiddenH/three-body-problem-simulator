 #include "vect.h"
#include <math.h>
#include <cstdio>


Vect::Vect() :x(0), y(0) {
}

Vect::Vect(float x, float y): x(x), y(y) {
}
Vect Vect::operator*(float lambda) const{//surcharge de l'opérateur "*"
    return Vect(lambda * this->x, lambda * this->y);
}
Vect Vect::operator+(Vect v2) const{//surcharge de l'opérateur "+"
    Vect res(this->x + v2.x, this->y + v2.y);
    return res;
}

void Vect::UpdatePosition(float new_x, float new_y) {//mise à jour du vecteur position
    x = new_x;
    y = new_y;
}

float Vect::Norme() const{//permet de calculer la norme du vecteur
    return sqrt(pow(x,2) + pow(y,2));
}

void Vect::Affiche() {
    printf("%f %f\n", x, y);
}

