#include "createtemplatedialog.h"
#include "modele.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

CreateTemplateDialog::CreateTemplateDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Créer une template");
    setMinimumSize(450, 500);//fixation d'une taille minimale pour la fenêtre

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titre = new QLabel("Créer une nouvelle template");
    titre->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 8px;");
    titre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titre);

    // Champ pour le nom de la template — absent dans AddExperienceDialog
    // car une expérience lancée sans enregistrer n'a pas besoin de nom
    QFormLayout *formNom = new QFormLayout();
    m_nomTemplate = new QLineEdit("Ma template");
    formNom->addRow("Nom de la template :", m_nomTemplate);
    mainLayout->addLayout(formNom);

    // Zone scrollable — exactement comme dans AddExperienceDialog
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContent = new QWidget();
    m_listeLayout = new QVBoxLayout(scrollContent);
    m_listeLayout->setAlignment(Qt::AlignTop);
    m_listeLayout->setSpacing(8);

    scroll->setWidget(scrollContent);
    mainLayout->addWidget(scroll, 1);

    QPushButton *btnAleatoire = new QPushButton("Champs aléatoire");
    QPushButton *btnEnregistrer = new QPushButton("Enregistrer la template");
    QPushButton *btnEnregistrerLancer = new QPushButton("▶ Lancer et enregistrer");

    btnAleatoire->setStyleSheet(
        "QPushButton { background-color: #8e44ad; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #7d3c98; }"
        "QPushButton:pressed { background-color: #6c3483; }"
        "QPushButton:disabled { background-color: gray; color: #cccccc; }"
        );

    // Styles différents pour distinguer visuellement les deux actions principales
    btnEnregistrer->setStyleSheet(
        "QPushButton { background-color: #f39c12; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #e67e22; }"
        "QPushButton:pressed { background-color: #d35400; }"
        );
    btnEnregistrerLancer->setStyleSheet(
        "QPushButton { background-color: #2ecc71; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #27ae60; }"
        "QPushButton:pressed { background-color: #1e8449; }"
        );

    QHBoxLayout *barreAjout = new QHBoxLayout();

    m_spinAjout = new QSpinBox();
    m_spinAjout->setRange(1, 100);
    m_spinAjout->setValue(1);
    m_spinAjout->setFixedWidth(80);

    QLabel *labelAjout = new QLabel("Nombre de corps à ajouter :");
    QPushButton *btnAjouter = new QPushButton("+ Ajouter");
    btnAjouter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    barreAjout->addWidget(labelAjout);
    barreAjout->addWidget(m_spinAjout);
    barreAjout->addWidget(btnAjouter);
    mainLayout->addLayout(barreAjout);

    connect(btnAjouter, &QPushButton::clicked, this, [this]() {
        int nb = m_spinAjout->value();
        for (int i = 0; i < nb; i++) ajouterCorps();
    });

    mainLayout->addWidget(btnAleatoire);
    mainLayout->addWidget(btnEnregistrer);
    mainLayout->addWidget(btnEnregistrerLancer);

    connect(btnAleatoire, &QPushButton::clicked, this, &CreateTemplateDialog::aleatoire);
    connect(btnEnregistrer, &QPushButton::clicked, this, &CreateTemplateDialog::enregistrer);
    connect(btnEnregistrerLancer, &QPushButton::clicked, this, &CreateTemplateDialog::enregistrerEtLancer);

}

void CreateTemplateDialog::ajouterCorps()
{
    int numero = m_corps.size() + 1;
    CorpsWidget *cw = new CorpsWidget(numero, this, false);;
    connect(cw, &CorpsWidget::supprimerDemande, this, &CreateTemplateDialog::supprimerCorps);
    m_listeLayout->addWidget(cw);
    m_corps.append(cw);
}

void CreateTemplateDialog::supprimerCorps(CorpsWidget *cw)
{
    m_corps.removeOne(cw);
    m_listeLayout->removeWidget(cw);
    cw->deleteLater();
    m_spinAjout->setValue(1);
}

void CreateTemplateDialog::aleatoire()
{
    std::srand(std::time(nullptr));

    // on randomise seulement les champs existants sans toucher au nombre de corps
    for (CorpsWidget *cw : std::as_const(m_corps)) {
        float masse = 800.0f + (std::rand() % 200);
        float x = -100.0f + (std::rand() % 200);
        float y = -100.0f + (std::rand() % 200);
        float vx = -0.5f + (std::rand() % 10) * 0.1f;
        float vy = -0.5f + (std::rand() % 10) * 0.1f;
        cw->randomize(masse, x, y, vx, vy);
    }
}

bool CreateTemplateDialog::sauvegarder()
{
    // Vérifie que le nom n'est pas vide
    if (m_nomTemplate->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Nom manquant", "Donne un nom à ta template !");
        return false;
    }

    if (m_corps.size() < 2) {
        QMessageBox::warning(this, "Pas assez de corps", "Il faut au moins 2 corps pour lancer une expérience !");
        return false;
    }

    // Construit la liste des corps à partir des widgets
    std::vector<Corps> liste;
    for (CorpsWidget *cw : std::as_const(m_corps)) {
        Corps c = cw->buildCorps();

        //Verificatin de la masse
        if (c.GetMasse() <= 0) {
            QMessageBox::warning(this, "Erreur","Tous les corps doivent avoir une masse positive !");
            return false;
        }

        //verification de la postion
        float x = c.GetPosition().GetX();
        float y = c.GetPosition().GetY();
        if (x < -1000.0f || x > 1000.0f || y < -1000.0f || y > 1000.0f) {
            QMessageBox::warning(this, "Erreur", "Les positions X et Y doivent être comprises entre -500 et 500 !");
            return false;
        }

        liste.push_back(c);
    }

    // Crée le Modele et l'ajoute à l'index des templates perso
    // C'est le même mécanisme que Modele::SauvegarderActu()
    // mais avec un nom choisi par l'utilisateur et des corps définis dans le formulaire
    // Génère un nom unique si le nom saisi existe déjà parmi les templates perso
    m_dernierNomUtilise = Modele::GenererNomUnique(m_nomTemplate->text());

    Modele nouvelleTemplate(m_dernierNomUtilise.toStdString(), liste);
    nouvelleTemplate.MajIndexPerso();

    return true;
}

void CreateTemplateDialog::enregistrer()
{
    // Enregistre sans lancer la simulation
    if (!sauvegarder()) return;

    // On prévient TemplateDialog de se rafraîchir
    emit templateEnregistree();

    QMessageBox::information(this, "Enregistré",QString("Template \"%1\" enregistrée").arg(m_dernierNomUtilise));

    accept(); // ferme le dialog
}

void CreateTemplateDialog::enregistrerEtLancer()
{
    // Enregistre ET lance la simulation
    if (!sauvegarder()) return;

    // On construit la liste une deuxième fois pour l'envoyer via le signal
    std::vector<Corps> liste;
    for (CorpsWidget *cw : std::as_const(m_corps)) {
        liste.push_back(cw->buildCorps());
    }

    emit templateEnregistree(); // pour rafraîchir TemplateDialog
    emit templateEnregistreeEtLancee(liste); // pour lancer la simulation dans MainWindow

    accept();
}

void CreateTemplateDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // Vide tous les corps existants
    for (CorpsWidget *cw : std::as_const(m_corps)) {
        m_listeLayout->removeWidget(cw);
        cw->deleteLater();
    }
    m_corps.clear();


}
