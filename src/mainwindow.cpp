#include "simview.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "templatedialog.h"
#include "modele.h"
#include "constants.h"
#include "historydialog.h"
#include "startexperience.h"
#include "randomgenerator.h"
#include "bodypanel.h"

#include <QPushButton>
#include <QColor>
#include <QRandomGenerator>
#include <QSlider>
#include <QResizeEvent>
#include <QTimer>
#include <QInputDialog>  // popup native Qt pour demander un texte à l'utilisateur
#include <QMessageBox>   // popup native Qt pour afficher un message
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(800, 600);
    setWindowTitle("Le Problème à Trois Corps");

    play_pause = true;
    m_estUneTemplate = false; // au démarrage on lance un système aléatoire, pas une template

    //////////////////////Instanciation des dialogs////////////////////////////////////////////
    templateDialog = new TemplateDialog(this);
    addExperienceDialog = new AddExperienceDialog(this);
    historyDialog = new HistoryDialog(this);
    templateDialog->rafraichirTemplatesPerso();
    bodyPanel = new BodyPanel(this);
    ///////////////////////////////////////////////////////////////////////////////////////////


    //////////////////////Déclaration de tous les boutons avec leurs paramètres///////////////
    btnRandom = new QPushButton("Aléatoire", ui->simWidget);
    btnPlayPause = new QPushButton("||", ui->simWidget);
    btnResetVue = new QPushButton("⌖", ui->simWidget);
    btnVitesse = new QPushButton("Vect. vitesse", ui->simWidget);
    btnGrille = new QPushButton("Grille", ui->simWidget);
    btnNoms = new QPushButton("Noms", ui->simWidget);
    btnRestart = new QPushButton("⟳", ui->simWidget);
    sliderVitesse = new QSlider(Qt::Horizontal, ui->simWidget);
    labelVitesse = new QLabel("Vitesse :", ui->simWidget);
    labelVitesseValeur = new QLabel("1", ui->simWidget);
    labelEnergieTotale = new QLabel("Énergie totale :", ui->simWidget);
    labelEnergieTotaleValeur = new QLabel("1", ui->simWidget);
    labelTemps = new QLabel("00:00:00", ui->simWidget);

    // --- Pour dynamiser un peu les boutons flottants ---
    btnRandom->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );

    btnPlayPause->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );

    btnRestart->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );

    btnResetVue->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );

    btnVitesse->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );

    btnGrille->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );

    btnNoms->setStyleSheet(
        "QPushButton:hover { background-color: rgba(255,255,255,30); }"
        "QPushButton:pressed { background-color: rgba(0,0,0,40); }"
        );
    // ------------------------------------------------------------

    labelTemps->setStyleSheet("color: white; background: transparent; font-size: 14px;");
    labelTemps->setAlignment(Qt::AlignCenter);

    sliderVitesse->setMinimum(1);
    sliderVitesse->setMaximum(10);
    sliderVitesse->setValue(1);
    labelVitesse->setStyleSheet("color: white;");
    labelVitesseValeur->setStyleSheet("color: white;");
    ///////////////////////////////////////////////////////////////////////////////////////////



    /////////////////////////////Design des boutons flottants//////////////////////////////////

    // Positionne les boutons dès que Qt a fini de construire la fenêtre
    QTimer::singleShot(0, this, [this]() {
        QResizeEvent fakeResize(this->size(), this->size());
        resizeEvent(&fakeResize);
    });

    ///////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////Integrateur//////////////////////////////////////////
    ui->cbIntegrateur->addItem("Runge-Kutta 4");
    ui->cbIntegrateur->addItem("Euler symplectique");
    ui->cbIntegrateur->addItem("Euler explicite");
    ui->cbIntegrateur->setCurrentIndex(0); // RK4 par défaut

    connect(ui->cbIntegrateur, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onIntegrateurChanged);
    ///////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////Signaux non liés au lancement des expériences///////////////////
    connect(sliderVitesse, SIGNAL(valueChanged(int)), this, SLOT(onSliderVitesseChanged(int)));

    connect(ui->btnTemplates, SIGNAL(clicked()), templateDialog, SLOT(show()));

    connect(ui->btnAddExperience, SIGNAL(clicked()), addExperienceDialog, SLOT(show()));

    connect(ui->btnHistorique, &QPushButton::clicked, this, [this]() {
        // on met à jour le snapshot de l'expérience en cours avant d'ouvrir
        if (m_indexExperienceCourante >= 0) {
            ExperienceRecord &courant = historyDialog->getRecordModifiable(0);
            courant.corps = Corps::GetIndex();
            courant.dureeTicks = m_engine->getTempsEcoule();
            courant.energieTotale = m_engine->getEnergieTotale();
        }
        historyDialog->rafraichirTableauXp();
        historyDialog->show();
    });

    connect(btnVitesse, &QPushButton::clicked, ui->simWidget, &SimView::toggleVitesses);

    connect(btnGrille, &QPushButton::clicked, ui->simWidget, &SimView::toggleGrille);

    connect(btnNoms, &QPushButton::clicked, ui->simWidget, &SimView::toggleNoms);

    connect(btnPlayPause, SIGNAL(clicked()), this, SLOT(onBtnPlayPauseClicked()));

    connect(btnResetVue, &QPushButton::clicked, ui->simWidget, &SimView::resetVue);

    connect(ui->btnEnregistrer, SIGNAL(clicked()), this, SLOT(onBtnEnregistrerClicked()));

    connect(ui->btnExportTrace, &QPushButton::clicked, this, &MainWindow::onBtnExportTraceClicked);

    // demande de sauvegarde depuis l'historique
    connect(historyDialog, &HistoryDialog::sauvegarderDemandee, this, &MainWindow::onSauvegarderDepuisHistorique);
    ///////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////Lancement d'expériences/////////////////////////////
    connect(btnRandom, SIGNAL(clicked()), this, SLOT(onBtnRandomClicked()));

    connect(historyDialog, &HistoryDialog::relancerDemande,this, &MainWindow::onRelancerDepuisHistorique);

    connect(btnRestart, SIGNAL(clicked()), this, SLOT(onBtnRestartClicked()));

    // AddExperienceDialog : lance la simulation avec les corps créés
    connect(addExperienceDialog, &AddExperienceDialog::experienceLancee, this, &MainWindow::onExperienceLancee);

    // TemplateDialog : charge le modèle choisi
    connect(templateDialog, SIGNAL(modeleChoisi(int)), this, SLOT(chargerModele(int)));

    // TemplateDialog : lance depuis LancerTemplateDialog (corps éventuellement modifiés)
    connect(templateDialog, &TemplateDialog::experienceLanceeDepuisTemplate, this, &MainWindow::onExperienceLanceeDepuisTemplate);
    ///////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////Gestion d'expériences////////////////////////////////

    // BodyPanel : clic sur un corps et ouvre le panel
    connect(ui->simWidget, SIGNAL(corpsClique(int)), this, SLOT(onCorpsClique(int)));

    connect(bodyPanel, SIGNAL(parametresPhysiquesModifies()), this, SLOT(onParametresPhysiquesModifies()));

    connect(bodyPanel, SIGNAL(couleurModifiee(int, QColor)), ui->simWidget, SLOT(setCouleurCorps(int, QColor)));

    connect(templateDialog, &TemplateDialog::templateSupprimee, this, &MainWindow::onTemplateSupprimee);

    // CreateTemplateDialog : lance ET enregistre
    // On passe par templateDialog car c'est lui qui possède createTemplateDialog
    CreateTemplateDialog *ctd = templateDialog->findChild<CreateTemplateDialog*>();
    if (ctd) {
        connect(ctd, &CreateTemplateDialog::templateEnregistreeEtLancee, this, &MainWindow::onTemplateEnregistreeEtLancee);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////

    // Moteur de simulation
    m_engine = new StartExperience(ui->simWidget, this);
    connect(m_engine, SIGNAL(tempsMAJ(float)), this, SLOT(onTempsMAJ(float)));

    // --- Démarrage : système aléatoire par défaut ---
    // m_estUneTemplate reste false : btnEnregistrer actif
    RandomGenerator::GenerateRandom();
    m_modeleActuel = Corps::GetIndex();
    enregistrerDansHistorique(Corps::GetNbCorps(), Corps::GetIndex(), 0.0f);
    m_engine->start();
}

// ------------------------------------------------------------------
// enregistrerDansHistorique : crée un ExperienceRecord et l'ajoute
// à HistoryDialog. Appelé à chaque nouveau lancement d'expérience.
// ------------------------------------------------------------------
void MainWindow::enregistrerDansHistorique(int nbCorps, const std::vector<Corps> &corpsFinals, float duree, const QString &nomTemplate)
{
    // on finalise le record précédent avec les données de fin de simulation
    if (m_indexExperienceCourante >= 0) {
        ExperienceRecord &precedent = historyDialog->getRecordModifiable(0);
        precedent.corps = corpsFinals;
        precedent.dureeTicks = duree;
        precedent.energieTotale = m_engine->getEnergieTotale();
    }

    ExperienceRecord record;
    record.dateHeure = QDateTime::currentDateTime();
    record.nbCorps = nbCorps;
    record.dureeTicks = 0.0f;
    record.energieTotale = 0.0;
    record.sauvegardee = m_estUneTemplate;
    record.nomTemplate = nomTemplate;;
    record.stabilite = 0.0f;
    record.corps = Corps::GetIndex();
    record.corpsInitiaux = Corps::GetIndex();

    historyDialog->ajouterExperience(record);
    m_indexExperienceCourante = 0;
}

void MainWindow::onBtnExportTraceClicked()
{
    // on met à jour le snapshot avant d'exporter
    if (m_indexExperienceCourante >= 0) {
        ExperienceRecord &courant = historyDialog->getRecordModifiable(0);
        courant.corps = Corps::GetIndex();
        courant.dureeTicks = m_engine->getTempsEcoule();
        courant.energieTotale = m_engine->getEnergieTotale();
    }
    historyDialog->exporterTraceExperienceActuelle();
}

void MainWindow::marquerHistoriqueSauvegarde(const QString &nom)
{
    if (m_indexExperienceCourante < 0) return;
    historyDialog->marquerSauvegardee(m_indexExperienceCourante, nom);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int w = ui->simWidget->width();
    int h = ui->simWidget->height();

    // Haut gauche
    labelEnergieTotale->setGeometry(20, 0, 85, 35);
    labelEnergieTotaleValeur->setGeometry(108, 0, 150, 35);

    // Bas gauche — reset vue, restart, play sur une seule ligne
    btnResetVue->setGeometry(110, h - 50, 40, 35);
    btnRestart->setGeometry(20,  h - 50, 40, 35);
    btnPlayPause->setGeometry(65,  h - 50, 40, 35);

    // Bas droite
    btnVitesse->setGeometry(w - 120, h - 90,  100, 35);
    btnGrille->setGeometry(w - 120, h - 50,  100, 35);
    btnNoms->setGeometry(w - 120, h - 130, 100, 35);

    // Bas centre
    btnRandom->setGeometry(w / 2 - 60, h - 50, 120, 35);

    // Haut droite
    labelVitesse->setGeometry(w - 280,  0, 60, 35);
    labelVitesse->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    sliderVitesse->setGeometry(w - 208, 10, 150, 35);
    labelVitesseValeur->setGeometry(w -  55,  0, 30, 35);
    labelVitesseValeur->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    // Haut milieu
    labelTemps->setGeometry(w / 2 - 60, 5, 120, 25);

    labelVitesse->setStyleSheet("background: transparent; color: white;");
    sliderVitesse->setStyleSheet("background: transparent;");
    labelVitesseValeur->setStyleSheet("background: transparent; color: white;");
    labelEnergieTotale->setStyleSheet("background: transparent; color: white;");
    labelEnergieTotaleValeur->setStyleSheet("background: transparent; color: white;");
}

void MainWindow::onSliderVitesseChanged(int value)
{
    labelVitesseValeur->setText(QString::number(value));
    m_engine->setVitesse(value);
}

void MainWindow::chargerModele(int id)
{
    m_engine->stop();
    std::vector<Corps> snapshot = Corps::GetIndex();
    float duree = m_engine->getTempsEcoule();

    QString nomTemplate = "";
    if (id > 0) {
        // Template prédéfinie
        nomTemplate = QString::fromStdString(INDEX_PREDEF.at(id - 1).GetNom());
        INDEX_PREDEF.at(id - 1).chargerTemplate();
    } else {
        // Template perso : id = -(i+1) donc i = -(id) - 1
        int i = -(id) - 1;
        vector<Modele>& perso = Modele::GetIndexPerso();
        if (i >= 0 && i < (int)perso.size()) {
            nomTemplate = QString::fromStdString(perso[i].GetNom());
            perso[i].chargerTemplate();
        }
    }

    m_modeleActuel = Corps::GetIndex();
    // Vide les couleurs de l'expérience précédente pour éviter le double vecteur vitesse
    ui->simWidget->clearCouleurs();
    // On grise le bouton enregistrer car c'est déjà une template
    // setEnabled(false) rend le bouton non cliquable et le grise automatiquement
    m_estUneTemplate = true;
    ui->btnEnregistrer->setEnabled(false);
    play_pause = true;
    btnPlayPause->setText("||");
    m_engine->resetTemps();
    ui->simWidget->resetVue();
    sliderVitesse->setValue(1);
    m_engine->setVitesse(1);
    enregistrerDansHistorique(Corps::GetNbCorps(), snapshot, duree, nomTemplate);
    m_engine->start();
}

// Reçu depuis AddExperienceDialog, lance sans enregistrer
void MainWindow::onExperienceLancee(std::vector<Corps> corps, QMap<int, QColor> couleurs)
{
    m_engine->stop();
    std::vector<Corps> snapshot = Corps::GetIndex();
    float duree = m_engine->getTempsEcoule();
    Corps::ResetSystem();

    for (unsigned i = 0; i < corps.size(); i++) {
        corps[i].MajIndex();
    }

    m_modeleActuel = Corps::GetIndex();

    // Vide les couleurs de l'expérience précédente
    ui->simWidget->clearCouleurs();

    // Ce n'est pas une template donc bouton enregistrer actif
    m_estUneTemplate = false;
    ui->btnEnregistrer->setEnabled(true);
    ui->btnEnregistrer->setStyleSheet(
        "background-color: #f39c12; color: white; "
        "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
        );

    play_pause = true;
    btnPlayPause->setText("||");
    m_engine->resetTemps();
    ui->simWidget->resetVue();
    sliderVitesse->setValue(1);
    m_engine->setVitesse(1);
    enregistrerDansHistorique((int)corps.size(), snapshot, duree);
    m_engine->start();

    for (auto it = couleurs.begin(); it != couleurs.end(); ++it) {
        ui->simWidget->setCouleurCorps(it.key(), it.value());
    }
}

// Reçu depuis CreateTemplateDialog, enregistre ET lance
void MainWindow::onTemplateEnregistreeEtLancee(std::vector<Corps> corps)
{
    m_engine->stop();
    std::vector<Corps> snapshot = Corps::GetIndex();
    float duree = m_engine->getTempsEcoule();
    Corps::ResetSystem();

    for (unsigned i = 0; i < corps.size(); i++) {
        corps[i].MajIndex();
    }

    m_modeleActuel = Corps::GetIndex();

    // Vide les couleurs de l'expérience précédente
    ui->simWidget->clearCouleurs();

    // Rafraîchit les boutons perso dans TemplateDialog
    templateDialog->rafraichirTemplatesPerso();

    // C'est une template donc on grise le bouton enregistrer
    m_estUneTemplate = true;
    ui->btnEnregistrer->setEnabled(false);
    ui->btnEnregistrer->setStyleSheet(
        "background-color: gray; color: #cccccc; "
        "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
        );

    play_pause = true;
    btnPlayPause->setText("||");
    m_engine->resetTemps();
    ui->simWidget->resetVue();
    sliderVitesse->setValue(1);
    m_engine->setVitesse(1);
    QString nomTemplate = "";
    vector<Modele>& perso = Modele::GetIndexPerso();
    if (!perso.empty()) {
        nomTemplate = QString::fromStdString(perso.back().GetNom());
    }
    enregistrerDansHistorique((int)corps.size(), snapshot, duree, nomTemplate);
    m_engine->start();
}

void MainWindow::onBtnEnregistrerClicked()
{
    // QInputDialog::getText : popup native avec un champ texte
    // Paramètres : parent, titre fenêtre, label, mode, valeur par défaut, &ok
    bool ok;
    QString nom = QInputDialog::getText(
        this,
        "Enregistrer comme template",
        "Nom de la template :",
        QLineEdit::Normal,
        "Ma template",
        &ok
        );

    if (!ok || nom.trimmed().isEmpty()) return;

    // Crée le Modele depuis l'état initial et l'ajoute à l'index perso
    Modele nouvelleTemplate(nom.toStdString(), m_modeleActuel);
    nouvelleTemplate.MajIndexPerso();

    // Rafraîchit les boutons dans TemplateDialog
    templateDialog->rafraichirTemplatesPerso();

    // On grise le bouton car la simulation est maintenant une template
    m_estUneTemplate = true;
    ui->btnEnregistrer->setEnabled(false);
    ui->btnEnregistrer->setStyleSheet(
        "background-color: gray; color: #cccccc; "
        "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
        );

    // on met à jour l'historique
    marquerHistoriqueSauvegarde(nom);

    QMessageBox::information(this, "Enregistré", QString("Template \"%1\" enregistrée").arg(nom));
}

void MainWindow::onBtnRestartClicked()
{
    m_engine->stop();
    Corps::ResetSystem();
    for (unsigned i = 0; i < m_modeleActuel.size(); i++) {
        m_modeleActuel.at(i).MajIndex();
    }
    play_pause = true;
    btnPlayPause->setText("||");
    m_engine->resetTemps();
    ui->simWidget->resetVue();
    sliderVitesse->setValue(1);
    m_engine->setVitesse(1);
    m_engine->start();
}

void MainWindow::onBtnPlayPauseClicked()
{
    play_pause = !play_pause;
    if (!play_pause) {
        m_engine->stop();
        btnPlayPause->setText("▶");
    } else {
        m_engine->start();
        btnPlayPause->setText("||");
    }
}

void MainWindow::onTempsMAJ(float temps)
{
    int total = (int)temps;
    int h = total / 3600;
    int m = (total % 3600) / 60;
    int s = total % 60;
    labelTemps->setText(QString("%1:%2:%3").arg(h, 2, 10, QChar('0')).arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0')));

    labelTemps->adjustSize();
    int w = ui->simWidget->width();
    labelTemps->move(w / 2 - labelTemps->width() / 2, 5);
    labelEnergieTotaleValeur->setText(QString::number(m_engine->getEnergieTotale()));
}

void MainWindow::onBtnRandomClicked()
{
    m_engine->stop();
    std::vector<Corps> snapshot = Corps::GetIndex();
    float duree = m_engine->getTempsEcoule();
    RandomGenerator::GenerateRandom();
    m_modeleActuel = Corps::GetIndex();

    // Vide les couleurs de l'expérience précédente
    ui->simWidget->clearCouleurs();

    // Système aléatoire : bouton enregistrer actif
    m_estUneTemplate = false;
    ui->btnEnregistrer->setEnabled(true);
    ui->btnEnregistrer->setStyleSheet(
        "background-color: #f39c12; color: white; "
        "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
        );

    play_pause = true;
    btnPlayPause->setText("||");
    m_engine->resetTemps();
    ui->simWidget->resetVue();
    sliderVitesse->setValue(1);
    m_engine->setVitesse(1);
    enregistrerDansHistorique(Corps::GetNbCorps(), snapshot, duree);
    m_engine->start();
}

// Reçu depuis LancerTemplateDialog — lance avec corps éventuellement modifiés
// Comme onExperienceLancee mais le bouton enregistrer reste actif
// car c'est une expérience potentiellement différente de la template parente
void MainWindow::onExperienceLanceeDepuisTemplate(std::vector<Corps> corps, QMap<int, QColor> couleurs, bool modifie, QString nomTemplate)
{
    m_engine->stop();
    std::vector<Corps> snapshot = Corps::GetIndex();
    float duree = m_engine->getTempsEcoule();
    Corps::ResetSystem();

    for (unsigned i = 0; i < corps.size(); i++) {
        corps[i].MajIndex();
    }

    m_modeleActuel = Corps::GetIndex();
    ui->simWidget->clearCouleurs();

    // Si pas de modification : même comportement qu'une template normale (bouton grisé)
    // Si modification : bouton enregistrer actif car c'est une nouvelle expérience
    m_estUneTemplate = !modifie;
    if (modifie) {
        ui->btnEnregistrer->setEnabled(true);
        ui->btnEnregistrer->setStyleSheet(
            "background-color: #f39c12; color: white; "
            "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
            );
    } else {
        ui->btnEnregistrer->setEnabled(false);
        ui->btnEnregistrer->setStyleSheet(
            "background-color: gray; color: #cccccc; "
            "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
            );
    }

    play_pause = true;
    btnPlayPause->setText("||");
    m_engine->resetTemps();
    ui->simWidget->resetVue();
    sliderVitesse->setValue(1);
    m_engine->setVitesse(1);
    enregistrerDansHistorique((int)corps.size(), snapshot, duree, modifie ? "" : nomTemplate);
    m_engine->start();

    for (auto it = couleurs.begin(); it != couleurs.end(); ++it) {
        ui->simWidget->setCouleurCorps(it.key(), it.value());
    }
}

void MainWindow::onRelancerDepuisHistorique(int index)
{
    if (index < 0 || index >= historyDialog->nbExperiences()) return;

    const ExperienceRecord &record = historyDialog->getRecord(index);

    // IMPORTANT : on utilise corpsInitiaux et pas corps
    // pour que la simulation redémarre depuis les conditions initiales
    std::vector<Corps> corps = record.corpsInitiaux;

    // Vérifie si la template référencée existe encore parmi les templates perso
    // Cas où l'expérience était liée à une template qui existe toujours :
    //   → on garde le lien (l'entrée historique sera marquée sauvegardée)
    // Cas où la template a été supprimée (ou aucune template) :
    //   → on traite comme une expérience from-scratch
    QString nomTemplate = "";
    bool templateExiste = false;

    if (record.sauvegardee && !record.nomTemplate.isEmpty()) {
        // Cherche d'abord dans les templates perso
        for (const Modele &m : Modele::GetIndexPerso()) {
            if (QString::fromStdString(m.GetNom()) == record.nomTemplate) {
                nomTemplate = record.nomTemplate;
                templateExiste = true;
                break;
            }
        }
        // Si pas trouvée, cherche dans les templates prédéfinies
        // (les prédéfinies ne peuvent pas être supprimées mais on vérifie par cohérence)
        if (!templateExiste) {
            for (const Modele &m : INDEX_PREDEF) {
                if (QString::fromStdString(m.GetNom()) == record.nomTemplate) {
                    nomTemplate = record.nomTemplate;
                    templateExiste = true;
                    break;
                }
            }
        }
    }

    // On ferme l'historique
    historyDialog->close();

    // Si la template existe encore, on passe par le flux "template"
    // pour que l'entrée historique soit marquée sauvegardée avec le bon nom.
    // Sinon, flux "from scratch" classique.
    if (templateExiste) {
        // modifie = false : expérience identique à la template → reste sauvegardée
        onExperienceLanceeDepuisTemplate(corps, QMap<int, QColor>(), false, nomTemplate);
    } else {
        onExperienceLancee(corps, QMap<int, QColor>());
    }
}

// demande de sauvegarde depuis l'historique : même comportement que onBtnEnregistrerClicked
// mais l'index de l'expérience à sauvegarder est fourni par HistoryDialog
void MainWindow::onSauvegarderDepuisHistorique(int index)
{
    bool ok;
    QString nom = QInputDialog::getText(
        this,
        "Enregistrer comme template",
        "Nom de la template :",
        QLineEdit::Normal,
        "Ma template",
        &ok
        );

    if (!ok || nom.trimmed().isEmpty()) return;

    // Génère un nom unique si collision
    QString nomUnique = Modele::GenererNomUnique(nom);

    const ExperienceRecord &record = historyDialog->getRecord(index);
    std::vector<Corps> liste = record.corpsInitiaux;

    Modele nouvelleTemplate(nomUnique.toStdString(), liste);
    nouvelleTemplate.MajIndexPerso();
    templateDialog->rafraichirTemplatesPerso();

    historyDialog->marquerSauvegardee(index, nomUnique);

    QMessageBox::information(this, "Enregistré",QString("Template \"%1\" enregistrée").arg(nomUnique));
}

void MainWindow::onTemplateSupprimee(QString nom)
{
    // Si l'expérience courante était cette template, on réactive le bouton enregistrer
    // (cas où on supprime la template qu'on est en train de simuler)
    if (m_estUneTemplate) {
        m_estUneTemplate = false;
        ui->btnEnregistrer->setEnabled(true);
        ui->btnEnregistrer->setStyleSheet(
            "background-color: #f39c12; color: white; "
            "font-weight: bold; border-radius: 4px; padding: 2px 6px;"
            );
    }

    // On parcourt TOUT l'historique pour démarquer toutes les entrées
    // qui référençaient la template supprimée.
    // Grâce au système de noms uniques (Modele::GenererNomUnique),
    // ce match par nom est fiable : il n'y a qu'une seule template
    // par nom, donc pas d'ambiguïté.
    for (int i = 0; i < historyDialog->nbExperiences(); i++) {
        ExperienceRecord &rec = historyDialog->getRecordModifiable(i);
        if (rec.sauvegardee && rec.nomTemplate == nom) {
            rec.sauvegardee = false;
            rec.nomTemplate = "";
        }
    }

    // Rafraîchit l'affichage une seule fois après toutes les modifications
    historyDialog->rafraichirTableauXp();
    historyDialog->mettreAJourIndicateur();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////Gestion d'expériences////////////////////////////////
void MainWindow::onCorpsClique(int index)
{
    bodyPanel->chargerCorps(index);
}

void MainWindow::onParametresPhysiquesModifies()
{
    m_engine->stop();
    m_modeleActuel = Corps::GetIndex();
    m_engine->start();
}

void MainWindow::onIntegrateurChanged(int index)
{
    if (index == 0) Corps::setIntegrateur(new RungeKutta4());
    else if (index == 1) Corps::setIntegrateur(new EulerSymplectique());
    else if (index == 2) Corps::setIntegrateur(new EulerExplicite());
}
///////////////////////////////////////////////////////////////////////////////////////////
