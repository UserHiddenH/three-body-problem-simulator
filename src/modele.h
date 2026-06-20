#ifndef MODELE_H
#define MODELE_H

#include "corps.h"
#include <vector>
#include <QString>

using namespace std;

class Modele
{
private:
    static vector<Modele> indexTemplatePerso;
    static int nb_template_perso;
    static int dernier_num_perso;
    string nom;
    vector<Corps> ListeCorps;

public:
    ///Un constructeur "explicite" avec tous les arguments déjà fournis, et un
    /// qui construit les arguments selon les inputs utilisateur (celui par défaut).
    Modele();
    Modele(string, vector<Corps>);
    void MajIndexPerso();
    static Modele SauvegarderActu();//Transforme les corps actuellement chargés en template, vitesse initiale = vitesse actuelle;
    static void SupprimerPerso(int index); // supprime la template perso à l'index donné
    void chargerTemplate();
    //une fonction spéciale pour créer le modèle à 15 corps utilisé dans constants.h
    static Modele CreerGalaxie();
    // ---
    string GetNom() const;
    vector<Corps> GetListeCorps() const;
    static vector<Modele>& GetIndexPerso();
    static QString GenererNomUnique(const QString &nom);

    // ---
    // Persistance des templates perso sur disque
    static void SauvegarderSurDisque();
    static void ChargerDepuisDisque();
    static QString CheminFichier();
};

#endif
