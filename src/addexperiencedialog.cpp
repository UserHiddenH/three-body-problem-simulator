#include "addexperiencedialog.h"
#include "corps.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QColorDialog>
#include <QColor>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QScrollArea>

// =====================================================================
// CORPSWIDGET
// =====================================================================

CorpsWidget::CorpsWidget(int numero, QWidget *parent, bool avecCouleur)
    : QWidget(parent)
{
    // QGroupBox : encadre le widget avec un titre lisible
    QGroupBox *boite = new QGroupBox(QString("Corps %1").arg(numero), this);

    // QFormLayout : layout "label à gauche / champ à droite", parfait pour les formulaires
    QFormLayout *form = new QFormLayout(boite);
    form->setSpacing(6);

    // QLineEdit : champ texte simple pour le nom
    m_nom = new QLineEdit(QString("Corps %1").arg(numero));

    // QDoubleSpinBox : bien mieux qu'un QLineEdit pour les nombres
    // car il empêche les entrées invalides et a des flèches d'incrémentation
    m_masse = new QDoubleSpinBox();
    m_masse->setRange(0.001, 100000.0);
    m_masse->setValue(100.0);
    m_masse->setDecimals(3);

    m_x = new QDoubleSpinBox();
    m_x->setRange(-1000.0, 1000.0);
    m_x->setValue(0.0);
    m_x->setDecimals(2);

    m_y = new QDoubleSpinBox();
    m_y->setRange(-1000.0, 1000.0);
    m_y->setValue(0.0);
    m_y->setDecimals(2);

    m_vx = new QDoubleSpinBox();
    m_vx->setRange(-100.0, 100.0);
    m_vx->setValue(0.0);
    m_vx->setDecimals(3);

    m_vy = new QDoubleSpinBox();
    m_vy->setRange(-100.0, 100.0);
    m_vy->setValue(0.0);
    m_vy->setDecimals(3);

    form->addRow("Nom :", m_nom);
    form->addRow("Masse :", m_masse);
    form->addRow("Position X :", m_x);
    form->addRow("Position Y :", m_y);
    form->addRow("Vitesse X :", m_vx);
    form->addRow("Vitesse Y :", m_vy);

    // Le bouton couleur n'est affiché que dans AddExperienceDialog
    if (avecCouleur) {
        QPushButton *btnCouleur = new QPushButton("Choisir couleur");
        form->addRow(btnCouleur);
        connect(btnCouleur, &QPushButton::clicked, this, &CorpsWidget::onBtnCouleurClicked);
        btnCouleur->setObjectName("btnCouleur");
    }

    QPushButton *btnSuppr = new QPushButton("Supprimer ce corps");
    btnSuppr->setStyleSheet("color: #ff6b6b;");
    form->addRow(btnSuppr);

    // La lambda [this] capture le pointeur vers ce CorpsWidget
    // pour pouvoir émettre le signal avec soi-même en paramètre
    connect(btnSuppr, &QPushButton::clicked, this, [this]() {
        emit supprimerDemande(this);
    });

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(boite);
}

Corps CorpsWidget::buildCorps() const
{
    // Construit un Corps à partir des valeurs saisies dans les champs
    std::string nom = m_nom->text().toStdString();
    float masse = (float)m_masse->value();
    float x = (float)m_x->value();
    float y = (float)m_y->value();
    float vx = (float)m_vx->value();
    float vy = (float)m_vy->value();

    return Corps(nom, masse, x, y, Vect(vx, vy));
}

void CorpsWidget::randomize(float masse, float x, float y, float vx, float vy)
{
    // Remplit les champs avec les valeurs passées en paramètre
    // (générées par RandomGenerator dans le dialog parent)
    m_masse->setValue(masse);
    m_x->setValue(x);
    m_y->setValue(y);
    m_vx->setValue(vx);
    m_vy->setValue(vy);
}

void CorpsWidget::setNom(const QString &nom)
{
    m_nom->setText(nom);
}

QColor CorpsWidget::getCouleur() const
{
    return m_couleur;
}

void CorpsWidget::onBtnCouleurClicked()
{
    // QColorDialog::getColor : popup native qui retourne la couleur choisie.
    // m_couleur = couleur actuelle affichée par défaut dans le sélecteur.
    // Si l'utilisateur annule, isValid() retourne false et on ne fait rien.
    QColor couleur = QColorDialog::getColor(m_couleur, this, "Choisir une couleur");

    if (!couleur.isValid()) return;

    m_couleur = couleur; // on mémorise la couleur choisie

    // On change la couleur de fond du bouton pour retour visuel
    // findChild<QPushButton*> cherche dans les enfants du widget un QPushButton
    // avec le nom "btnCouleur" qu'on a défini avec setObjectName
    QPushButton *btn = findChild<QPushButton*>("btnCouleur");
    if (btn) {
        btn->setStyleSheet(
            QString("background-color: %1;").arg(couleur.name())
            );
    }
}

// =====================================================================
// ADDEXPERIENCEDIALOG
// =====================================================================

AddExperienceDialog::AddExperienceDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Nouvelle expérience");
    setMinimumSize(450, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titre = new QLabel("Créer une nouvelle expérience");
    titre->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 8px;");
    titre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titre);

    // QScrollArea : zone avec scrollbar automatique quand le contenu dépasse
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true); // le contenu s'adapte à la largeur disponible
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContent = new QWidget();
    m_listeLayout = new QVBoxLayout(scrollContent);
    m_listeLayout->setAlignment(Qt::AlignTop); // les corps s'empilent vers le haut
    m_listeLayout->setSpacing(8);

    scroll->setWidget(scrollContent);
    mainLayout->addWidget(scroll, 1); // le "1" = ce widget peut s'étirer verticalement

    QPushButton *btnAleatoire = new QPushButton("Champs aléatoire");
    QPushButton *btnLancer = new QPushButton("▶ Lancer l'expérience");

    btnAleatoire->setStyleSheet(
        "QPushButton { background-color: #8e44ad; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #7d3c98; }"
        "QPushButton:pressed { background-color: #6c3483; }"
        "QPushButton:disabled { background-color: gray; color: #cccccc; }"
        );

    btnLancer->setStyleSheet(
        "QPushButton { background-color: #2ecc71; color: white; "
        "font-weight: bold; padding: 8px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #27ae60; }"
        "QPushButton:pressed { background-color: #1e8449; }"
        );

    QHBoxLayout *barreAjout = new QHBoxLayout();

    m_spinAjout = new QSpinBox();
    m_spinAjout->setRange(1, 100);
    m_spinAjout->setValue(1); // par défaut on ajoute 1 corps
    m_spinAjout->setFixedWidth(80);

    QLabel *labelAjout = new QLabel("Nombre de corps à ajouter :");
    QPushButton *btnAjouter = new QPushButton("+ Ajouter");
    // le bouton prend plus de place que le spinbox
    btnAjouter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    barreAjout->addWidget(labelAjout);
    barreAjout->addWidget(m_spinAjout);
    barreAjout->addWidget(btnAjouter);
    mainLayout->addLayout(barreAjout);

    connect(btnAjouter, &QPushButton::clicked, this, [this]() {
        // On ajoute autant de corps que la valeur du spinbox
        int nb = m_spinAjout->value();
        for (int i = 0; i < nb; i++) ajouterCorps();
    });

    mainLayout->addWidget(btnAleatoire);
    mainLayout->addWidget(btnLancer);

    connect(btnAleatoire, &QPushButton::clicked, this, &AddExperienceDialog::aleatoire);
    connect(btnLancer, &QPushButton::clicked, this, &AddExperienceDialog::lancer);

    /*ajouterCorps();
    ajouterCorps();*/
}

void AddExperienceDialog::ajouterCorps()
{
    int numero = m_corps.size() + 1;
    // false = pas de bouton couleur, les couleurs seront aléatoires dans SimView
    CorpsWidget *cw = new CorpsWidget(numero, this, true);

    // Quand ce corps émet supprimerDemande, on appelle supprimerCorps()
    connect(cw, &CorpsWidget::supprimerDemande, this, &AddExperienceDialog::supprimerCorps);

    m_listeLayout->addWidget(cw);
    m_corps.append(cw);
    m_spinAjout->setValue(1);
}

void AddExperienceDialog::supprimerCorps(CorpsWidget *cw)
{
    m_corps.removeOne(cw);
    m_listeLayout->removeWidget(cw);
    cw->deleteLater(); // deleteLater() = façon correcte en Qt de détruire un widget en cours d'utilisation
}

void AddExperienceDialog::aleatoire()
{
    std::srand(std::time(nullptr));

    for (CorpsWidget *cw : std::as_const(m_corps)) {
        float masse = 800.0f  + (std::rand() % 200);
        float x = -100.0f + (std::rand() % 200);
        float y = -100.0f + (std::rand() % 200);
        float vx = -0.5f + (std::rand() % 10) * 0.1f;
        float vy = -0.5f + (std::rand() % 10) * 0.1f;
        cw->randomize(masse, x, y, vx, vy);

        // Couleur aléatoire
        QColor couleur(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        cw->setCouleurAleatoire(couleur);
    }
}

void AddExperienceDialog::lancer()
{
    if (m_corps.size() < 2) {
        QMessageBox::warning(this, "Erreur", "Il faut au moins 2 corps pour lancer une expérience !");
        return;
    }

    std::vector<Corps> liste;
    for (CorpsWidget *cw : std::as_const(m_corps)) {
        Corps c = cw->buildCorps();

        if (c.GetMasse() <= 0) {
            QMessageBox::warning(this, "Erreur", "Tous les corps doivent avoir une masse positive !");
            return;
        }

        float x = c.GetPosition().GetX();
        float y = c.GetPosition().GetY();
        if (x < -1000.0f || x > 1000.0f || y < -1000.0f || y > 1000.0f) {
            QMessageBox::warning(this, "Erreur", "Les positions X et Y doivent être comprises entre -500 et 500 !");
            return;
        }

        liste.push_back(c);
    }

    // On émet le signal vers MainWindow qui lancera la simulation
    // On construit la map des couleurs : index du corps → couleur choisie
    QMap<int, QColor> couleurs;
    for (int i = 0; i < m_corps.size(); i++) {
        couleurs[i] = m_corps[i]->getCouleur();
    }

    emit experienceLancee(liste, couleurs);
    accept(); // ferme le dialog
}

void CorpsWidget::setCouleurAleatoire(const QColor &couleur)
{
    m_couleur = couleur;
    QPushButton *btn = findChild<QPushButton*>("btnCouleur");
    if (btn) {
        btn->setStyleSheet(
            QString("background-color: %1;").arg(couleur.name())
            );
    }
}

void AddExperienceDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // Vide tous les corps existants
    for (CorpsWidget *cw : std::as_const(m_corps)) {
        m_listeLayout->removeWidget(cw);
        cw->deleteLater();
    }
    m_corps.clear();

    /*ajouterCorps();
    ajouterCorps();*/
}
