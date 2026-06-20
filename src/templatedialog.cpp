#include "templatedialog.h"
#include "ui_templatedialog.h"
#include "modele.h"
#include "constants.h"
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>

TemplateDialog::TemplateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TemplateDialog)
{
    ui->setupUi(this);

    createTemplateDialog = new CreateTemplateDialog(this);
    setWindowTitle("Templates");

    // ouvre le dialog de création de template au clic sur "+"
    connect(ui->btnAddTemplate, SIGNAL(clicked()), createTemplateDialog, SLOT(show()));

    // quand une template est enregistrée depuis CreateTemplateDialog on rafraîchit la liste
    connect(createTemplateDialog, &CreateTemplateDialog::templateEnregistree, this, &TemplateDialog::rafraichirTemplatesPerso);

    // connexions des boutons prédéfinis — passent par ouvrirLancerDialog au lieu d'émettre modeleChoisi directement
    connect(ui->btnTerreSoleil, &QPushButton::clicked, this, &TemplateDialog::onBtnTerreSoleilClicked);
    connect(ui->btnTerreSoleilLune, &QPushButton::clicked, this, &TemplateDialog::onBtnTerreSoleilLuneClicked);
    connect(ui->btnTerreSoleilMars, &QPushButton::clicked, this, &TemplateDialog::onBtnTerreSoleilMarsClicked);
    connect(ui->btnBiSoleils, &QPushButton::clicked, this, &TemplateDialog::onBtnBiSoleilClicked);
    connect(ui->btnTriSoleils, &QPushButton::clicked, this, &TemplateDialog::onBtnTriSoleilClicked);
    connect(ui->btnBiSoleilsPlanete, &QPushButton::clicked, this, &TemplateDialog::onBtnBiSoleilPlaneteClicked);
    connect(ui->btnGalaxie15, &QPushButton::clicked, this, &TemplateDialog::onBtnGalaxieClicked);
    connect(ui->btnInfinity, &QPushButton::clicked, this, &TemplateDialog::onBtnInfinityClicked);
    connect(ui->btnDoubleBiSoleils, &QPushButton::clicked, this, &TemplateDialog::onBtnDoubleBiSoleilClicked);
    connect(ui->btnSystemeSolaire, &QPushButton::clicked, this, &TemplateDialog::onBtnSystemeSolaireClicked);

    // label de séparation caché par défaut, affiché dès qu'il y a au moins une template perso
    m_labelPerso = new QLabel("— Templates personnalisées —");
    m_labelPerso->setAlignment(Qt::AlignCenter);
    m_labelPerso->setStyleSheet("color: gray; font-size: 11px;");
    m_labelPerso->setVisible(false);

    // zone scrollable pour les templates perso, limitée à 3 lignes visibles
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setFixedHeight(0); // caché par défaut, ajusté dans rafraichirTemplatesPerso()
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget *scrollContent = new QWidget();
    m_layoutPerso = new QVBoxLayout(scrollContent);
    m_layoutPerso->setContentsMargins(4, 4, 4, 4);
    m_layoutPerso->setSpacing(4);
    m_layoutPerso->setAlignment(Qt::AlignTop);
    m_scrollArea->setWidget(scrollContent);

    if (layout()) {
        layout()->addWidget(m_labelPerso);
        layout()->addWidget(m_scrollArea);
    }
}

// récupère les corps du modèle identifié par id, ouvre LancerTemplateDialog pré-rempli
void TemplateDialog::ouvrirLancerDialog(int id)
{
    std::vector<Corps> corps;
    QString nom;

    if (id > 0) {
        // template prédéfinie
        const Modele &m = INDEX_PREDEF.at(id - 1);
        corps = m.GetListeCorps();
        nom = QString::fromStdString(m.GetNom());
    } else {
        // template perso : id = -(i+1) donc i = -(id) - 1
        int i = -(id) - 1;
        vector<Modele>& perso = Modele::GetIndexPerso();
        if (i < 0 || i >= (int)perso.size()) return;
        corps = perso[i].GetListeCorps();
        nom = QString::fromStdString(perso[i].GetNom());
    }

    // on crée le dialog à chaque ouverture pour avoir un état propre
    LancerTemplateDialog *ltd = new LancerTemplateDialog(corps, nom, this);

    // MainWindow recevra experienceLanceeDepuisTemplate et gérera le lancement
    connect(ltd, &LancerTemplateDialog::experienceLancee, this, [this, nom](std::vector<Corps> corps, QMap<int, QColor> couleurs, bool modifie) {
        emit experienceLanceeDepuisTemplate(corps, couleurs, modifie, nom);
    });

    // pour rafraîchir la liste si l'utilisateur enregistre une nouvelle template perso
    connect(ltd, &LancerTemplateDialog::templateEnregistree, this, &TemplateDialog::rafraichirTemplatesPerso);

    // WA_DeleteOnClose : Qt détruit le dialog automatiquement à la fermeture
    // évite les fuites mémoire puisqu'on crée un nouveau dialog à chaque ouverture
    ltd->setAttribute(Qt::WA_DeleteOnClose);

    close();
    ltd->exec();
}

void TemplateDialog::rafraichirTemplatesPerso()
{
    // vide tout le layout
    while (m_layoutPerso->count() > 0) {
        QLayoutItem *item = m_layoutPerso->takeAt(0);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    vector<Modele>& perso = Modele::GetIndexPerso();
    for (int i = 0; i < (int)perso.size(); i++) {
        QString nom = QString::fromStdString(perso[i].GetNom());

        // ligne horizontale : bouton template à gauche, bouton supprimer à droite
        QWidget *ligne = new QWidget();
        QHBoxLayout *ligneLayout = new QHBoxLayout(ligne);
        ligneLayout->setContentsMargins(0, 0, 0, 0);
        ligneLayout->setSpacing(4);

        QPushButton *btn = new QPushButton(nom);
        QPushButton *btnSuppr = new QPushButton("🗑");
        btnSuppr->setFixedWidth(32);
        btnSuppr->setToolTip("Supprimer cette template");
        btnSuppr->setStyleSheet("color: #ff6b6b;");
        btn->setStyleSheet("text-align: left; padding: 4px 8px;");

        // La lambda capture i par valeur, chaque bouton mémorise son propre index
        connect(btn, &QPushButton::clicked, this, [this, i]() {
            ouvrirLancerDialog(-(i + 1));
        });

        connect(btnSuppr, &QPushButton::clicked, this, [this, i, nom]() {
            QMessageBox::StandardButton reponse = QMessageBox::warning(
                this,
                "Supprimer la template",
                QString("Voulez-vous vraiment supprimer \"%1\" ?").arg(nom),
                QMessageBox::Yes | QMessageBox::No
                );

            if (reponse != QMessageBox::Yes) return;

            Modele::SupprimerPerso(i);
            rafraichirTemplatesPerso();
            emit templateSupprimee(nom);
        });

        ligneLayout->addWidget(btn);
        ligneLayout->addWidget(btnSuppr);
        m_layoutPerso->addWidget(ligne);
    }

    int nb = (int)perso.size();

    // affiche la zone seulement s'il y a au moins une template perso
    m_labelPerso->setVisible(nb > 0);

    // hauteur d'une ligne = 34px (bouton) + 4px (spacing) = 38px, max 3 lignes visibles
    int hauteurLigne  = 38;
    int hauteurMax  = hauteurLigne * 3;
    int hauteurReelle = hauteurLigne * nb;
    m_scrollArea->setFixedHeight(nb > 0 ? qMin(hauteurReelle, hauteurMax) : 0);
    resize(width(), sizeHint().height());
}

// slots prédéfinis, passent par ouvrirLancerDialog
void TemplateDialog::onBtnTerreSoleilClicked()     { ouvrirLancerDialog(1); }
void TemplateDialog::onBtnTerreSoleilLuneClicked() { ouvrirLancerDialog(2); }
void TemplateDialog::onBtnBiSoleilClicked()        { ouvrirLancerDialog(3); }
void TemplateDialog::onBtnGalaxieClicked()         { ouvrirLancerDialog(4); }
void TemplateDialog::onBtnTerreSoleilMarsClicked() { ouvrirLancerDialog(5); }
void TemplateDialog::onBtnBiSoleilPlaneteClicked() { ouvrirLancerDialog(6); }
void TemplateDialog::onBtnInfinityClicked()        { ouvrirLancerDialog(7); }
void TemplateDialog::onBtnTriSoleilClicked()       { ouvrirLancerDialog(8); }
void TemplateDialog::onBtnDoubleBiSoleilClicked()  { ouvrirLancerDialog(9); }
void TemplateDialog::onBtnSystemeSolaireClicked() { ouvrirLancerDialog(10); }

TemplateDialog::~TemplateDialog()
{
    delete ui;
}
