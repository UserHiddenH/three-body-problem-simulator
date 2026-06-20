#ifndef LANCERTEMPLATEDIALOG_H
#define LANCERTEMPLATEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QList>
#include <QPushButton>
#include <QSpinBox>
#include <QColor>
#include <QMap>
#include "corps.h"
#include "addexperiencedialog.h" // pour réutiliser CorpsWidget

// ------------------------------------------------------------------
// LancerTemplateDialog : fenêtre intermédiaire avant le lancement
// d'une template. Affiche les corps de la template pré-remplis,
// permet d'en ajouter de nouveaux, de modifier les champs,
// et de lancer ou enregistrer comme nouvelle template perso.
// ------------------------------------------------------------------
class LancerTemplateDialog : public QDialog
{
    Q_OBJECT

public:
    // corps = corps de la template parente, nom = nom de la template
    explicit LancerTemplateDialog(const std::vector<Corps> &corps,const QString &nom,QWidget *parent = nullptr);
    ~LancerTemplateDialog() = default;

signals:

    void experienceLancee(std::vector<Corps> corps, QMap<int, QColor> couleurs, bool modifie);
    void templateEnregistree();

private slots:
    void ajouterCorps();
    void supprimerCorps(CorpsWidget *cw);
    void aleatoire();   // s'applique uniquement sur les nouveaux corps
    void lancer();
    void enregistrer();
    void onModification(); // appelé dès qu'un champ est modifié

private:
    QVBoxLayout *m_listeLayout;

    // Corps de la template parente non affectés par l'aléatoire
    QList<CorpsWidget*> m_corpsBase;

    // Corps ajoutés manuellement affectés par l'aléatoire
    QList<CorpsWidget*> m_corpsAjoutes;

    QPushButton *m_btnAleatoire;
    QPushButton *m_btnEnregistrer;

    QSpinBox *m_spinAjout;

    QString m_nomTemplateParente;
    bool m_modifie = false;

    // Snapshot de l'état initial de la template pour comparaison
    std::vector<Corps> m_corpsInitiaux;

    // Compare l'état actuel avec l'état initial
    bool aEteModifie() const;

    // Connecte les signaux de modification d'un CorpsWidget vers onModification()
    void connecterModification(CorpsWidget *cw);

    // Nombre total de corps (base + ajoutés)
    int nbCorpsTotal() const { return m_corpsBase.size() + m_corpsAjoutes.size(); }
};

#endif
