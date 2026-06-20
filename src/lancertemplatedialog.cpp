#include "lancertemplatedialog.h"
#include "modele.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QDoubleSpinBox>
#include <cstdlib>
#include <ctime>

LancerTemplateDialog::LancerTemplateDialog(const std::vector<Corps> &corps, const QString &nom, QWidget *parent)
    : QDialog(parent), m_nomTemplateParente(nom)
{
    setWindowTitle(QString("Lancer : %1").arg(nom));
    setMinimumSize(450, 550);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titre = new QLabel(QString("Template : %1").arg(nom));
    titre->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 8px;");
    titre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titre);

    // Zone scrollable — exactement comme dans AddExperienceDialog et CreateTemplateDialog
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true); // le contenu s'adapte à la largeur disponible
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContent = new QWidget();
    m_listeLayout = new QVBoxLayout(scrollContent);
    m_listeLayout->setAlignment(Qt::AlignTop); // les corps s'empilent vers le haut
    m_listeLayout->setSpacing(8);

    scroll->setWidget(scrollContent);
    mainLayout->addWidget(scroll, 1); // le "1" = ce widget peut s'étirer verticalement

    // --- Boutons d'action ---
    m_btnAleatoire  = new QPushButton("Champs aléatoire");
    m_btnEnregistrer = new QPushButton("Enregistrer comme nouvelle template");
    QPushButton *btnLancer = new QPushButton("▶ Lancer");

    // Aléatoire grisé par défaut — ne s'active que si on ajoute des corps
    m_btnAleatoire->setEnabled(false);
    m_btnAleatoire->setStyleSheet(
        "QPushButton { background-color: #8e44ad; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #7d3c98; }"
        "QPushButton:pressed { background-color: #6c3483; }"
        "QPushButton:disabled { background-color: gray; color: #cccccc; }"
        );

    // Enregistrer grisé par défaut — ne s'active que si une modification est détectée
    m_btnEnregistrer->setEnabled(false);
    m_btnEnregistrer->setStyleSheet(
        "QPushButton { background-color: #f39c12; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #e67e22; }"
        "QPushButton:pressed { background-color: #d35400; }"
        "QPushButton:disabled { background-color: gray; color: #cccccc; }"
        );

    btnLancer->setStyleSheet(
        "QPushButton { background-color: #2ecc71; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #27ae60; }"
        "QPushButton:pressed { background-color: #1e8449; }"
        );

    // APRÈS — au dessus du bouton aléatoire
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
    mainLayout->addLayout(barreAjout); // placé juste avant m_btnAleatoire

    mainLayout->addWidget(m_btnAleatoire);
    mainLayout->addWidget(m_btnEnregistrer);
    mainLayout->addWidget(btnLancer);

    connect(btnAjouter, &QPushButton::clicked, this, [this]() {
        int nb = m_spinAjout->value();
        for (int i = 0; i < nb; i++) ajouterCorps();
    });

    connect(m_btnAleatoire, &QPushButton::clicked, this, &LancerTemplateDialog::aleatoire);
    connect(m_btnEnregistrer, &QPushButton::clicked, this, &LancerTemplateDialog::enregistrer);
    connect(btnLancer, &QPushButton::clicked, this, &LancerTemplateDialog::lancer);

    // --- Chargement des corps de la template parente ---
    // On les crée avec avecCouleur=true pour que le bouton couleur soit présent
    // et on leur affecte une couleur aléatoire à l'ouverture
    std::srand(std::time(nullptr));
    for (const Corps &c : corps) {
        int numero = m_corpsBase.size() + 1;
        CorpsWidget *cw = new CorpsWidget(numero, this, true);

        // Pré-remplissage avec les valeurs de la template
        cw->randomize(c.GetMasse(), c.GetPosition().GetX(), c.GetPosition().GetY(), c.GetVitesse().GetX(), c.GetVitesse().GetY());

        cw->setNom(QString::fromStdString(c.GetNom()));

        // Couleur aléatoire à l'ouverture
        QColor couleur(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        cw->setCouleurAleatoire(couleur);

        // Connexion suppression — on garde au moins 1 corps
        connect(cw, &CorpsWidget::supprimerDemande, this, &LancerTemplateDialog::supprimerCorps);

        // Toute modification sur un corps de base débloque le bouton enregistrer
        connecterModification(cw);

        m_listeLayout->addWidget(cw);
        m_corpsBase.append(cw);
    }

    // On mémorise l'état initial pour pouvoir comparer plus tard
    m_corpsInitiaux = corps;
}

// ------------------------------------------------------------------
// aEteModifie : dit si la template de base a subit des modifs
// connecterModification : connecte tous les champs d'un CorpsWidget
// vers onModification() pour détecter dès qu'un champ est touché
// ------------------------------------------------------------------

bool LancerTemplateDialog::aEteModifie() const
{
    // Si le nombre de corps a changé c'est forcément modifié
    if (!m_corpsAjoutes.isEmpty()) return true;
    if ((int)m_corpsInitiaux.size() != m_corpsBase.size()) return true;

    // On compare chaque corps actuel avec son état initial
    for (int i = 0; i < m_corpsBase.size(); i++) {
        Corps actuel = m_corpsBase[i]->buildCorps();
        Corps initial = m_corpsInitiaux[i];

        if (actuel.GetMasse() != initial.GetMasse()) return true;
        if (actuel.GetPosition().GetX() != initial.GetPosition().GetX()) return true;
        if (actuel.GetPosition().GetY() != initial.GetPosition().GetY()) return true;
        if (actuel.GetVitesse().GetX() != initial.GetVitesse().GetX())  return true;
        if (actuel.GetVitesse().GetY() != initial.GetVitesse().GetY())  return true;
    }

    return false;
}

void LancerTemplateDialog::connecterModification(CorpsWidget *cw)
{
    // On parcourt tous les QDoubleSpinBox et QLineEdit enfants du widget
    // et on connecte leur signal de changement vers onModification()
    for (QDoubleSpinBox *sb : cw->findChildren<QDoubleSpinBox*>()) {
        connect(sb, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &LancerTemplateDialog::onModification);
    }
    for (QLineEdit *le : cw->findChildren<QLineEdit*>()) {
        connect(le, &QLineEdit::textChanged, this, &LancerTemplateDialog::onModification);
    }
}

void LancerTemplateDialog::onModification()
{
    bool modifie = aEteModifie();

    if (modifie == m_modifie) return; // rien n'a changé, pas besoin de mettre à jour
    m_modifie = modifie;

    if (m_modifie) {
        m_btnEnregistrer->setEnabled(true);
        m_btnEnregistrer->setStyleSheet(
            "background-color: #f39c12; color: white; "
            "font-weight: bold; padding: 8px; border-radius: 4px;"
            );
    } else {
        m_btnEnregistrer->setEnabled(false);
        m_btnEnregistrer->setStyleSheet(
            "background-color: gray; color: #cccccc; "
            "font-weight: bold; padding: 8px; border-radius: 4px;"
            );
    }
}

void LancerTemplateDialog::ajouterCorps()
{
    // Les nouveaux corps sont numérotés à la suite des corps de base
    int numero = nbCorpsTotal() + 1;

    // avecCouleur=true comme dans AddExperienceDialog
    CorpsWidget *cw = new CorpsWidget(numero, this, true);

    connect(cw, &CorpsWidget::supprimerDemande,
            this, &LancerTemplateDialog::supprimerCorps);

    // Les nouveaux corps déclenchent aussi onModification
    connecterModification(cw);

    m_listeLayout->addWidget(cw);
    m_corpsAjoutes.append(cw);

    // Dès qu'on a au moins un corps ajouté, on débloque l'aléatoire
    if (!m_corpsAjoutes.isEmpty()) {
        m_btnAleatoire->setEnabled(true);
        m_btnAleatoire->setStyleSheet(
            "background-color: #8e44ad; color: white; "
            "font-weight: bold; padding: 8px; border-radius: 4px;"
            );
    }

    // Ajouter un corps = modification → débloque enregistrer
    onModification();
    m_spinAjout->setValue(1);
}

void LancerTemplateDialog::supprimerCorps(CorpsWidget *cw)
{
    // On cherche si c'est un corps de base ou un corps ajouté
    if (m_corpsBase.contains(cw)) {
        m_corpsBase.removeOne(cw);
    } else {
        m_corpsAjoutes.removeOne(cw);
    }

    m_listeLayout->removeWidget(cw);
    cw->deleteLater(); // deleteLater() = façon correcte en Qt de détruire un widget en cours d'utilisation

    // Si plus aucun corps ajouté, on regrise l'aléatoire
    if (m_corpsAjoutes.isEmpty()) {
        m_btnAleatoire->setEnabled(false);
        m_btnAleatoire->setStyleSheet(
            "background-color: gray; color: #cccccc; "
            "font-weight: bold; padding: 8px; border-radius: 4px;"
            );
    }

    // Supprimer un corps = modification
    onModification();
}

void LancerTemplateDialog::aleatoire()
{
    // L'aléatoire ne s'applique QUE sur les corps ajoutés manuellement
    // Les corps de la template parente (m_corpsBase) restent intouchés
    std::srand(std::time(nullptr));
    for (CorpsWidget *cw : std::as_const(m_corpsAjoutes)) {
        float masse = 800.0f  + (std::rand() % 200);
        float x = -100.0f + (std::rand() % 200);
        float y = -100.0f + (std::rand() % 200);
        float vx = -0.5f + (std::rand() % 10) * 0.1f;
        float vy = -0.5f + (std::rand() % 10) * 0.1f;
        cw->randomize(masse, x, y, vx, vy);

        // Couleur aléatoire sur les nouveaux corps aussi
        QColor couleur(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        cw->setCouleurAleatoire(couleur);
    }
}

void LancerTemplateDialog::lancer()
{
    if (nbCorpsTotal() < 2) {
        QMessageBox::warning(this, "Erreur", "Il faut au moins 2 corps pour lancer une expérience !");
        return;
    }

    std::vector<Corps> liste;
    QMap<int, QColor> couleurs;
    int index = 0;

    // On construit la liste complète : corps de base d'abord, puis les ajoutés
    auto collectCorps = [&](const QList<CorpsWidget*> &source) {
        for (CorpsWidget *cw : source) {
            Corps c = cw->buildCorps();

            if (c.GetMasse() <= 0) {
                QMessageBox::warning(this, "Erreur", "Tous les corps doivent avoir une masse positive !");
                return;
            }

            float x = c.GetPosition().GetX();
            float y = c.GetPosition().GetY();
            if (x < -1000.0f || x > 1000.0f || y < -1000.0f || y > 1000.0f) {
                QMessageBox::warning(this, "Erreur", "Les positions X et Y doivent être entre -500 et 500 !");
                return;
            }

            liste.push_back(c);
            couleurs[index++] = cw->getCouleur();
        }
    };

    collectCorps(m_corpsBase);
    collectCorps(m_corpsAjoutes);

    if ((int)liste.size() != nbCorpsTotal()) return; // une validation a échoué

    emit experienceLancee(liste, couleurs, m_modifie);
    accept(); // ferme le dialog
}

void LancerTemplateDialog::enregistrer()
{
    // QInputDialog::getText : popup native avec un champ texte
    bool ok;
    QString nom = QInputDialog::getText(
        this,
        "Enregistrer comme nouvelle template",
        "Nom de la template :",
        QLineEdit::Normal,
        m_nomTemplateParente + " (modifiée)",
        &ok
        );

    if (!ok || nom.trimmed().isEmpty()) return;

    // Génère un nom unique si le nom saisi existe déjà parmi les templates perso
    QString nomUnique = Modele::GenererNomUnique(nom);

    std::vector<Corps> liste;
    for (CorpsWidget *cw : std::as_const(m_corpsBase)) liste.push_back(cw->buildCorps());
    for (CorpsWidget *cw : std::as_const(m_corpsAjoutes)) liste.push_back(cw->buildCorps());

    // Crée le Modele et l'ajoute à l'index perso — la template parente reste intacte
    Modele nouvelleTemplate(nomUnique.toStdString(), liste);
    nouvelleTemplate.MajIndexPerso();

    emit templateEnregistree(); // pour que TemplateDialog rafraîchisse la liste

    QMessageBox::information(this, "Enregistré", QString("Template \"%1\" enregistrée !").arg(nomUnique));
}

