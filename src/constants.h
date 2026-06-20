#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "corps.h"
#include "modele.h"
#include <vector>


//Les valeurs concrètes sont définies dans le .cpp
//L'usage de "extern" garantit que l'édition de liens ne crée pas de multiples copies d'une même variable si le .h est inclut
//dans plusieurs .cpp

// Corps prédéfinis
extern const Corps GROS_SOLEIL;
extern const Corps TERRE;
extern const Corps LUNE;
extern const Corps MARS;
extern const Corps BISOLEIL1;
extern const Corps BISOLEIL2;
extern const Corps BISOLEILPLANETE;
extern const Corps HUIT1;
extern const Corps HUIT2;
extern const Corps HUIT3;
extern const Corps TRISOLEIL1;
extern const Corps TRISOLEIL2;
extern const Corps TRISOLEIL3;

// Listes de corps
extern std::vector<Corps> soleil_terre_lune;
extern std::vector<Corps> soleil_terre;
extern std::vector<Corps> soleil_terre_mars;
extern std::vector<Corps> bisoleil;
extern std::vector<Corps> bisoleil_planete;
extern std::vector<Corps> figure_eight;
extern std::vector<Corps> trisoleil;
extern std::vector<Corps> doublebisoleil;
extern const Corps DOUBLEBISOLEIL1;
extern const Corps DOUBLEBISOLEIL2;
extern const Corps DOUBLEBISOLEIL3;
extern const Corps DOUBLEBISOLEIL4;
// Système solaire
extern const Corps SOL_SOLEIL;
extern const Corps SOL_MERCURE;
extern const Corps SOL_VENUS;
extern const Corps SOL_TERRE;
extern const Corps SOL_MARS;
extern const Corps SOL_JUPITER;
extern const Corps SOL_SATURNE;
extern const Corps SOL_URANUS;
extern const Corps SOL_NEPTUNE;
extern std::vector<Corps> systeme_solaire;

// Modèles
extern Modele SOLEIL_TERRE;
extern Modele SOLEIL_TERRE_LUNE;
extern Modele SOLEIL_TERRE_MARS;
extern Modele BISOLEIL;
extern Modele BISOLEIL_PLANETE;
extern Modele FIGURE_EIGHT;
extern Modele TRISOLEIL;
extern Modele GALAXIE;
extern Modele DOUBLEBISOLEIL;
extern Modele SYSTEME_SOLAIRE;

// Index global
extern std::vector<Modele> INDEX_PREDEF;

#endif
