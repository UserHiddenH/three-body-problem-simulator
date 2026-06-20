#include "corps.h"
#include "vect.h"
#include "integrateur.h"
#include <vector>
#include <math.h>
#include <cmath>

float const DT = 0.01; //le pas de temps
int const G = 10;

float Corps::energie_potentielle;
float Corps::energie_cinetique;
int Corps::nb_corps = 0;
int Corps::dernier_num = 0;
std::vector<Corps> Corps::index;

Corps::Corps(std::string nom, float masse, float x, float y) {// constructeur principal
    numero = dernier_num + 1;
    this->masse = masse;
    this->nom = nom;
    this->position = Vect(x, y);
}

Corps::Corps(std::string nom, float masse, float x, float y, Vect vitesseinit) {// avec vitesse initiale
    numero = dernier_num + 1;
    this->masse = masse;
    this->nom = nom;
    this->position = Vect(x, y);
    this->vitesse = vitesseinit;
}

void Corps::MajIndex() {
    nb_corps++;
    dernier_num++;
    numero = dernier_num; // recale numero sur dernier_num après incrément
    index.push_back(*this);
}

void Corps::UpdatePosition(float new_x, float new_y) {
    position.UpdatePosition(new_x, new_y);//on met à jour la position du vecteur position à l'aide de la méthode définie dans la classe Vect
}

Vect Corps::Acceleration() {
    Vect Somme;

    for (int i = 0; i < Corps::nb_corps; i++) { //On parcourt tous les corps indexés
        Corps corps_i = Corps::index[i];
        if (corps_i.numero != this->numero) {//Pour ne pas calculer l'accélération appliquée sur lui même
            Vect v = (corps_i.position + (this->position) * (-1)); //Le vecteur qui va de corps_i vers le corps étudié (Ce calcul sert à obtenir le vecteur direction entre deux positions)
            float distance = v.Norme();
            if (distance < 1.0f) continue; // évite la division par zéro si deux corps se superposent
            Somme = Somme + v * ((corps_i.masse * G) / (pow(distance, 3)));// Ce calcul donne l’accélération gravitationnelle du corps étudié (this) causée par tous les autres corps du système.

        }
    }
    return Somme;
}

Integrateur* Corps::s_integrateur = new RungeKutta4(); //Par défaut

void Corps::setIntegrateur(Integrateur *integrateur)
{
    delete s_integrateur;
    s_integrateur = integrateur;
}

void Corps::Calc_Position() {
    Vect acceleration = this->Acceleration(); //On calcule l'accélération au moment de l'appel
    s_integrateur->calculer(position, vitesse, acceleration, DT); //On calcule la position et la vitesse en passant par l'integrateur
    //Synchroniser l'index
    Corps::index[numero - 1].position = position;

    trace.push_back(position); //Sauvegarde la position dans la trace
    Corps::index[numero - 1].CalcTours();//permet de calculer les tours pour le corps en question
}

void Corps::CalcTours() {
    // Quadrant 1-4 basé sur l'angle polaire, centré sur l'origine
    int nouvquadrant = (int)floor(atan2(position.GetY(), position.GetX()) / (0.5 * M_PI)) + 1;

    // On n'étudie le tour que si le corps est suffisamment loin du centre
    if ((nouvquadrant != quadrant) && (position.Norme() > 10)) {
        // +1 sens horaire, -1 sens antihoraire
        int nouvsens = (int)std::pow(-1.0, ((nouvquadrant - quadrant) % 4 + 4) % 4 % 3);

        if ((compteur == 0) || (sens == nouvsens)) {
            compteur += nouvsens;
            if (abs(compteur) > 4) {
                nbTours++;
                compteur = 0;
            }
        } else {
            // sens inversé : on repart à zéro
            compteur = 0;
        }
        sens = nouvsens;
    }
    quadrant = nouvquadrant;
}

void Corps::Affiche() {
    position.Affiche();
}

void Corps::VitesseInitiale(float x, float y) {
    vitesse.UpdatePosition(x, y);
}

// Des fonctions Get pour obtenir des valeur privees.
void Corps::ResetSystem(){
    index.clear();
    nb_corps = 0;
    dernier_num = 0;

}
std::vector<Corps>& Corps::GetIndex(){
    return index;
}
int Corps::GetNbCorps() {
    return nb_corps;
}
Vect Corps::GetPosition() const{
    return position;
}

Vect Corps::GetVitesse() const {
    return vitesse;
}

const std::vector<Vect>& Corps::GetTrace() const {
    return trace; // retourne simplement la trace
}

float Corps::GetMasse() const {
    return masse;
}

float Corps::getMasse() {
    return masse;
}

std::string Corps::GetNom() const {
    return nom;
}

int Corps::GetNbTours() const {
    return nbTours;
}

void Corps::setNom(std::string nom) {
    this->nom = nom;
}

void Corps::setMasse(float masse) {
    this->masse = masse;
}

void Corps::setVitesse(float vx, float vy) {
    this->vitesse.UpdatePosition(vx, vy);
}

double Corps::GetPotentielle(){
    return energie_potentielle;
}

double Corps::GetCinetique(){
    return energie_cinetique;
}

double Corps::CalcCinetique() const{
    return 0.5*masse*pow(vitesse.Norme(),2);
}
double Corps::CalcPotentielle(){
    double potentielle = 0;
    int i,j;
    //On regarde tous les couples de corps et l'énergie potentielle du système associé.
    for(i = 0; i<nb_corps; i++){
        for(j=i+1; j<nb_corps; j++){
            if (index[i].numero != index[j].numero) {
                Vect v = (index[i].position + (index[j].position) * (-1));
                potentielle=potentielle-(G*(index[i].masse*index[j].masse))/(v.Norme());
            }
        }
    }
    return potentielle;
}
void Corps::MajCinetique(double energie){
    Corps::energie_cinetique = energie;
}

void Corps::MajPotentielle(double energie){
    Corps::energie_potentielle = energie;
}
void Corps::resetTrace() {
    trace.clear();
}



