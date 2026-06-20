#include "modele.h"
#include <QWidget>
#include "constants.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

std::vector<Modele> Modele::indexTemplatePerso;
Modele::Modele(string nom, std::vector<Corps> listecorps) {
    this->ListeCorps=listecorps;
    this->nom = nom;
}
Modele::Modele(){
}

void Modele::MajIndexPerso() {
    indexTemplatePerso.push_back(*this);
    SauvegarderSurDisque();
}
Modele Modele::SauvegarderActu(){
    Modele res = Modele("Template Auto", Corps::GetIndex());
    res.MajIndexPerso();
    return res;
}

void Modele::chargerTemplate(){
    Corps::ResetSystem();
    //Charge tous les corps du template dans l'index des corps courants
    unsigned i;

    for(i=0; i<ListeCorps.size(); i++){
        ListeCorps.at(i).MajIndex();
    }
}


Modele Modele::CreerGalaxie(){
    vector<Corps>galaxie = {GROS_SOLEIL};
    struct OrbiteData {float r; float angle;};
    QList<OrbiteData> orbites = {
        {30.0f,  0.0f},  {40.0f,  45.0f}, {50.0f,  90.0f},
        {60.0f, 135.0f}, {35.0f, 180.0f}, {45.0f, 225.0f},
        {55.0f, 270.0f}, {65.0f, 315.0f}, {70.0f,  20.0f},
        {75.0f,  70.0f}, {80.0f, 160.0f}, {85.0f, 200.0f},
        {90.0f, 250.0f}, {95.0f, 300.0f}, {100.0f, 350.0f}
    };
    for (int i = 0; i < orbites.size(); i++) {
        float r = orbites[i].r;
        float a = orbites[i].angle * M_PI / 180.0f;
        float x = r * cos(a);
        float y = r * sin(a);
        float v = sqrt(10.0f * 500.0f / r);
        float vx = -v * sin(a);
        float vy =  v * cos(a);
        galaxie.push_back(Corps("Etoile" + std::to_string(i), 1.0f, x,y,Vect(vx, vy)));
    }
    return Modele("Galaxie à 15 corps", galaxie);
}
// ---
string Modele::GetNom() const {
    return nom;
}

vector<Corps> Modele::GetListeCorps() const {
    return ListeCorps;
}

vector<Modele>& Modele::GetIndexPerso() {
    return indexTemplatePerso;
}

void Modele::SupprimerPerso(int index)
{
    if (index < 0 || index >= (int)indexTemplatePerso.size()) return;
    indexTemplatePerso.erase(indexTemplatePerso.begin() + index);
    SauvegarderSurDisque();
}

// =====================================================================
// PERSISTANCE DES TEMPLATES PERSO
// =====================================================================


//permet de recharger à l'ouverture de l'application l'ensemble des expériences sauvegardées
QString Modele::CheminFichier()
{
    QString dossier = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dossier); // crée le dossier si il n'existe pas
    return dossier + "/templates_perso.json";
}

void Modele::SauvegarderSurDisque()
{
    QJsonArray arrTemplates;
    for (const Modele &m : indexTemplatePerso) {
        QJsonObject objTemplate;
        objTemplate["nom"] = QString::fromStdString(m.nom);

        QJsonArray arrCorps;
        for (const Corps &c : m.ListeCorps) {
            QJsonObject objCorps;
            objCorps["nom"] = QString::fromStdString(c.GetNom());
            objCorps["masse"] = c.GetMasse();
            objCorps["x"] = c.GetPosition().GetX();
            objCorps["y"] = c.GetPosition().GetY();
            objCorps["vx"] = c.GetVitesse().GetX();
            objCorps["vy"] = c.GetVitesse().GetY();
            arrCorps.append(objCorps);
        }
        objTemplate["corps"] = arrCorps;
        arrTemplates.append(objTemplate);
    }

    QJsonDocument doc(arrTemplates);
    QFile fichier(CheminFichier());
    if (fichier.open(QIODevice::WriteOnly)) {
        fichier.write(doc.toJson());
        fichier.close();
    }
}

void Modele::ChargerDepuisDisque()
{
    QFile fichier(CheminFichier());
    if (!fichier.open(QIODevice::ReadOnly)) return; // première exécution : pas de fichier, c'est normal

    QJsonDocument doc = QJsonDocument::fromJson(fichier.readAll());
    fichier.close();
    if (!doc.isArray()) return;

    indexTemplatePerso.clear();
    QJsonArray arrTemplates = doc.array();
    for (const QJsonValue &valTemplate : std::as_const(arrTemplates)) {
        QJsonObject objTemplate = valTemplate.toObject();
        std::string nom = objTemplate["nom"].toString().toStdString();

        std::vector<Corps> corps;
        QJsonArray arrCorps = objTemplate["corps"].toArray();
        for (const QJsonValue &valCorps : std::as_const(arrCorps)) {
            QJsonObject objCorps = valCorps.toObject();
            Corps c(
                objCorps["nom"].toString().toStdString(),
                (float)objCorps["masse"].toDouble(),
                (float)objCorps["x"].toDouble(),
                (float)objCorps["y"].toDouble(),
                Vect((float)objCorps["vx"].toDouble(), (float)objCorps["vy"].toDouble())
                );
            corps.push_back(c);
        }

        indexTemplatePerso.push_back(Modele(nom, corps));
    }
}


QString Modele::GenererNomUnique(const QString &nom)
{
    // Fonction locale qui vérifie si un nom donné existe déjà
    auto existeDeja = [](const QString &candidat) -> bool {
        for (const Modele &m : indexTemplatePerso) {
            if (QString::fromStdString(m.GetNom()) == candidat) {
                return true;
            }
        }
        return false;
    };

    // Si le nom original est libre, on le retourne tel quel
    if (!existeDeja(nom)) return nom;

    // Sinon on incrémente le suffixe jusqu'à trouver un nom libre
    int suffixe = 2;
    QString candidat;
    do {
        candidat = QString("%1 (%2)").arg(nom).arg(suffixe);
        suffixe++;
    } while (existeDeja(candidat));

    return candidat;
}
