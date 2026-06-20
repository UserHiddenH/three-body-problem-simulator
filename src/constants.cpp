#include "constants.h"
#include "modele.h"
#include <math.h>

// Corps prédéfinis
const Corps GROS_SOLEIL("Gros soleil", 1000.0f, 0.0f, 0.0f, Vect(0.0f, 0.0f));
const Corps TERRE("Terre", 1.0f, 100.0f, 0.0f, Vect(0.0f, 10.0f));
const Corps LUNE("Lune", 0.01f, 102.0f, 0.0f, Vect(0.0f, 12.236));
const Corps MARS("Mars", 0.1f, -160.0f, 0.0f, Vect(0.0f, -7.906));
const Corps BISOLEIL1("Soleil 1", 500.0f, 50.0f, 0.0f, Vect(0.0f, -5.0f));
const Corps BISOLEIL2("Soleil 2", 500.0f, -50.0f, 0.0f, Vect(0.0f, 5.0f));
const Corps BISOLEILPLANETE("Petite planète", 0.001f, 100.0f, 0.0f, Vect(0.0f, 0.0f));
const Corps HUIT1("Corps 1", 100.0f, -97.0004f, 24.3088f, Vect(1.474f, 1.367f));
const Corps HUIT2("Corps 2", 100.0f, 97.0004f, -24.3088f, Vect(1.474f, 1.367f));
const Corps HUIT3("Corps 3", 100.0f, 0.0f, 0.0f, Vect(-2.948f, -2.734f));
const Corps TRISOLEIL1("Soleil 1", 500.0f, -50.0f, 0.0f, Vect(0.0f, -5.0f));
const Corps TRISOLEIL2("Soleil 2", 500.0f, 50.0f, 0.0f, Vect(0.0f, 5.0f));
const Corps TRISOLEIL3("Soleil 3", 500.0f, 0.0f, 120.0f, Vect(5.0f, 0.0f));
const Corps DOUBLEBISOLEIL1("Soleil 1", 500,-50,300,Vect(2.89,-5));
const Corps DOUBLEBISOLEIL2("Soleil 2",500,50,300,Vect(2.89,5));
const Corps DOUBLEBISOLEIL3("Soleil 3",500,-50,-300,Vect(-2.89,-5));
const Corps DOUBLEBISOLEIL4("Soleil 4",500,50,-300,Vect(-2.89,5));
// Système solaire
const Corps SOL_SOLEIL("Soleil", 5000.0f, 0.0f, 0.0f, Vect(-0.0863f, 0.0837f));
const Corps SOL_MERCURE("Mercure", 0.055f, 45.21f, 12.11f, Vect(-8.46f, 31.57f));
const Corps SOL_VENUS("Vénus", 0.815f, 43.20f, 74.82f, Vect(-20.83f, 12.03f));
const Corps SOL_TERRE("Terre", 1.0f, -41.04f, 112.76f, Vect(-19.18f, -6.98f));
const Corps SOL_MARS("Mars", 0.107f, -171.40f,  62.38f, Vect(-5.66f, -15.56f));
const Corps SOL_JUPITER("Jupiter", 40.0f, -290.98f, -168.00f, Vect(6.10f, -10.56f));
const Corps SOL_SATURNE("Saturne", 20.0f, -205.3f, -563.8f, Vect(8.47f, -3.08f));
const Corps SOL_URANUS("Uranus", 6.0f, 400.0f, -692.8f, Vect(6.85f, 3.95f));
const Corps SOL_NEPTUNE("Neptune", 6.0f, 986.7f, -359.2f, Vect(2.36f, 6.49f));

//Listes de corps
vector<Corps> soleil_terre_lune = {LUNE, TERRE, GROS_SOLEIL};
vector<Corps> soleil_terre = {GROS_SOLEIL, TERRE};
vector<Corps> soleil_terre_mars = {GROS_SOLEIL, TERRE, MARS};
vector<Corps> bisoleil = {BISOLEIL1, BISOLEIL2};
vector<Corps> bisoleil_planete = {BISOLEIL1, BISOLEIL2, BISOLEILPLANETE};
vector<Corps> figure_eight = {HUIT1, HUIT2, HUIT3};
vector<Corps> trisoleil = {TRISOLEIL1, TRISOLEIL2, TRISOLEIL3};
vector<Corps> doublebisoleil = {DOUBLEBISOLEIL1,DOUBLEBISOLEIL2,DOUBLEBISOLEIL3,DOUBLEBISOLEIL4};
vector<Corps> systeme_solaire = {SOL_SOLEIL, SOL_MERCURE, SOL_VENUS, SOL_TERRE, SOL_MARS, SOL_JUPITER, SOL_SATURNE, SOL_URANUS, SOL_NEPTUNE};

//Les modèles
Modele SOLEIL_TERRE = Modele("Soleil/Terre", soleil_terre);
Modele SOLEIL_TERRE_LUNE = Modele("Soleil/Terre/lune", soleil_terre_lune);
Modele SOLEIL_TERRE_MARS = Modele("Soleil/Terre/Mars", soleil_terre_mars);
Modele BISOLEIL = Modele("Bisoleil", bisoleil);
Modele BISOLEIL_PLANETE = Modele("Bisoleil + planète", bisoleil_planete);
Modele FIGURE_EIGHT = Modele("Grand huit", figure_eight);
Modele TRISOLEIL = Modele("Trois soleils", trisoleil);
Modele GALAXIE = Modele::CreerGalaxie();
Modele DOUBLEBISOLEIL = Modele("Double Bi-soleil", doublebisoleil);
Modele SYSTEME_SOLAIRE = Modele("Système Solaire", systeme_solaire);

//L'index des modèles
//L'ordre est important pour savoir quel modèle charger à partir de sa position dans l'index
vector<Modele> INDEX_PREDEF = {SOLEIL_TERRE, SOLEIL_TERRE_LUNE, BISOLEIL, GALAXIE, SOLEIL_TERRE_MARS, BISOLEIL_PLANETE, FIGURE_EIGHT, TRISOLEIL, DOUBLEBISOLEIL, SYSTEME_SOLAIRE};

