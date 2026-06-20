#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include "experiencerecord.h"

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog() = default;

    // appelée depuis MainWindow à chaque nouveau lancement
    void ajouterExperience(const ExperienceRecord &record);

    // met à jour une ligne comme sauvegardée
    void marquerSauvegardee(int index, const QString &nom);

    // retourne l'index de la ligne sélectionnée dans le tableau expériences, -1 si aucune
    int indexSelectionne() const;

    // retourne l'expérience à l'index donné
    const ExperienceRecord& getRecord(int index) const;

    int nbExperiences() const;

    ExperienceRecord& getRecordModifiable(int index);

    void rafraichirTableauXp();
    void mettreAJourIndicateur();
    void exporterTraceExperienceActuelle();
    void exporterTrace(int idx);

signals:
    void sauvegarderDemandee(int index);
    void relancerDemande(int index);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void onExperienceSelectionnee();
    void onBtnSauvegarderClicked();
    void onBtnExportTableauXpClicked();
    void onBtnExportTraceXpClicked();
    void onBtnExportTableauCorpsClicked();
    void onBtnRelancerClicked();

private:

    QLabel *m_titreCorps;

    // tableau du haut : liste des expériences
    QTableWidget *m_tableXp;

    // tableau du bas : corps de l'expérience sélectionnée
    QTableWidget *m_tableCorps;

    // indicateur du nombre d'expériences non sauvegardées
    QLabel *m_labelNonSauvegardees;

    // boutons expériences
    QPushButton *m_btnSauvegarder;
    QPushButton *m_btnExportTableauXp;
    QPushButton *m_btnExportTraceXp;
    QPushButton *m_btnRelancer;

    // boutons corps
    QPushButton *m_btnExportTableauCorps;

    QList<ExperienceRecord> m_records;

    void rafraichirTableauCorps(int indexXp);
    void colorerLigneXp(int row, bool sauvegardee);

    // calcule la distance totale parcourue par un corps depuis sa trace
    float calculerDistanceParcourue(const std::vector<Vect> &trace) const;

    // exporte un QTableWidget dans un PDF
    void exporterTableauEnPdf(QTableWidget *table, const QString &titre);
};

#endif
