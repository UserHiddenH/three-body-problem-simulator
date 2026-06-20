#ifndef ADDEXPERIENCEDIALOG_H
#define ADDEXPERIENCEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QColor>
#include <QMap>
#include <QSpinBox>
#include "corps.h"

// ------------------------------------------------------------------
// CorpsWidget : représente la ligne de saisie d'UN seul corps
// C'est un widget qu'on empile dynamiquement dans le formulaire.
// Chaque instance a ses propres champs indépendants des autres.
// ------------------------------------------------------------------
class CorpsWidget : public QWidget
{
    Q_OBJECT
public:
    // avecCouleur = true dans AddExperienceDialog, false dans CreateTemplateDialog
    explicit CorpsWidget(int numero, QWidget *parent = nullptr, bool avecCouleur = true);

    // Lit les valeurs saisies dans les champs et construit un objet Corps
    Corps buildCorps() const;

    // Remplit les champs avec des valeurs aléatoires cohérentes
    void randomize(float masse, float x, float y, float vx, float vy);
    QColor getCouleur() const;
    void setCouleurAleatoire(const QColor &couleur);
    void setNom(const QString &nom);

signals:
    // Émis quand l'utilisateur clique sur supprimer corps, avec un pointeur vers soi-même
    // pour que AddExperienceDialog sache quel widget supprimer
    void supprimerDemande(CorpsWidget* moi);

private:
    // Les champs de saisie — privés car seul buildCorps() doit y accéder
    QLineEdit *m_nom;
    QDoubleSpinBox *m_masse;
    QDoubleSpinBox *m_x;
    QDoubleSpinBox *m_y;
    QDoubleSpinBox *m_vx;
    QDoubleSpinBox *m_vy;
    QColor m_couleur = Qt::white;
private slots:
    void onBtnCouleurClicked(); // ouvre le sélecteur de couleur natif Qt
};

// ------------------------------------------------------------------
// AddExperienceDialog : le dialog principal de création d'expérience
// Contient une liste dynamique de CorpsWidgets dans une zone scrollable
// ------------------------------------------------------------------
class AddExperienceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExperienceDialog(QWidget *parent = nullptr);
    ~AddExperienceDialog() = default;

signals:
    // Émis vers MainWindow quand l'utilisateur valide
    // Transporte les corps ET leurs couleurs associées vers MainWindow
    void experienceLancee(std::vector<Corps> corps, QMap<int, QColor> couleurs);

private slots:
    void ajouterCorps(); // ajoute un CorpsWidget vide à la liste
    void supprimerCorps(CorpsWidget *cw); // retire le CorpsWidget demandé
    void aleatoire(); // vide tout et génère un système aléatoire
    void lancer(); // construit les Corps et émet experienceLancee()
protected:
    void showEvent(QShowEvent *event) override;
private:
    // Layout qui contient les CorpsWidgets empilés verticalement
    QVBoxLayout *m_listeLayout;

    // Liste des widgets de corps actuellement affichés
    QList<CorpsWidget*> m_corps;

    QSpinBox *m_spinAjout;
};

#endif
