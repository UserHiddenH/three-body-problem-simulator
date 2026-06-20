#ifndef TEMPLATEDIALOG_H
#define TEMPLATEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include "createtemplatedialog.h"
#include "lancertemplatedialog.h"

namespace Ui {
class TemplateDialog;
}

class TemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateDialog(QWidget *parent = nullptr);
    ~TemplateDialog();

    // Appelée depuis MainWindow après qu'une template perso est enregistrée
    // pour recréer dynamiquement les boutons dans l'onglet templates perso
    void rafraichirTemplatesPerso();

signals:
    // Convention : id > 0 = template prédéfinie (INDEX_PREDEF[id-1])
    //              id < 0 = template perso (GetIndexPerso()[-(id+1)])
    void modeleChoisi(int id);

    // Émis quand LancerTemplateDialog veut lancer avec des corps modifiés
    void experienceLanceeDepuisTemplate(std::vector<Corps> corps, QMap<int, QColor> couleurs, bool modifie, QString nomTemplate);
    void templateSupprimee(QString nom);

private:
    Ui::TemplateDialog *ui;
    CreateTemplateDialog *createTemplateDialog;

    // Layout dans lequel on injecte les boutons perso dynamiquement
    // séparé du layout principal pour ne pas toucher aux boutons prédéfinis
    QVBoxLayout *m_layoutPerso;
    QLabel *m_labelPerso;
    QScrollArea *m_scrollArea;

    // Ouvre LancerTemplateDialog avec les corps du modèle choisi
    // id = identifiant du modèle (même convention que modeleChoisi)
    void ouvrirLancerDialog(int id);

private slots:
    //slots liés au clic sur les différentes templates prédéfinis
    void onBtnTerreSoleilClicked();
    void onBtnTerreSoleilLuneClicked();
    void onBtnTerreSoleilMarsClicked();
    void onBtnBiSoleilClicked();
    void onBtnTriSoleilClicked();
    void onBtnBiSoleilPlaneteClicked();
    void onBtnGalaxieClicked();
    void onBtnInfinityClicked();
    void onBtnDoubleBiSoleilClicked();
    void onBtnSystemeSolaireClicked();
};

#endif
