#ifndef CREATETEMPLATEDIALOG_H
#define CREATETEMPLATEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QList>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSpinBox>
#include "corps.h"
#include "addexperiencedialog.h" // on réutilise CorpsWidget, pas besoin de le réécrire

// dialog de création de template manuelle
// même structure qu'AddExperienceDialog mais avec un nom + boutons enregistrer
class CreateTemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTemplateDialog(QWidget *parent = nullptr);
    ~CreateTemplateDialog() = default;

signals:
    void templateEnregistree();                                 // enregistrement sans lancement
    void templateEnregistreeEtLancee(std::vector<Corps> corps); // enregistrement + lancement

protected:
    void showEvent(QShowEvent *event) override; // repart de zéro à chaque ouverture

private slots:
    void ajouterCorps();
    void supprimerCorps(CorpsWidget *cw);
    void aleatoire();
    void enregistrer();
    void enregistrerEtLancer();

private:
    QLineEdit *m_nomTemplate;      // nom donné à la template
    QVBoxLayout *m_listeLayout;    // layout qui contient les CorpsWidgets
    QList<CorpsWidget*> m_corps;   // liste des corps actuellement affichés
    QSpinBox *m_spinAjout;         // nb de corps à ajouter d'un coup
    QString m_dernierNomUtilise;

    bool sauvegarder(); // construit et enregistre le Modele, retourne false si nom vide
};

#endif
