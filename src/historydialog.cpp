#include "historydialog.h"
#include "corps.h"
#include "vect.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFrame>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QColor>
#include <QDateTime>
#include <cmath>

// colonnes tableau expériences
static const int XP_DATE = 0;
static const int XP_NB_CORPS = 1;
static const int XP_DUREE = 2;
static const int XP_ENERGIE = 3;
static const int XP_SAUVEGARDE = 4;
static const int XP_NOM = 5;
static const int XP_NB_COLS = 6;

// colonnes tableau corps
static const int CORPS_NOM = 0;
static const int CORPS_MASSE = 1;
static const int CORPS_POS_X = 2;
static const int CORPS_POS_Y = 3;
static const int CORPS_VIT_X = 4;
static const int CORPS_VIT_Y = 5;
static const int CORPS_DIST = 6;
static const int CORPS_CINETIQUE = 7;
static const int CORPS_TOURS = 8;
static const int CORPS_NB_COLS = 9;

HistoryDialog::HistoryDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Historique");
    setMinimumSize(1000, 650);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    // =====================================================================
    // COMPARTIMENT HAUT : expériences
    // =====================================================================

    // titre + indicateur non sauvegardées sur la même ligne
    QHBoxLayout *lignetitre = new QHBoxLayout();
    QLabel *titreXp = new QLabel("Expériences lancées");
    titreXp->setStyleSheet("font-size: 15px; font-weight: bold;");

    m_labelNonSauvegardees = new QLabel("");
    m_labelNonSauvegardees->setStyleSheet(
        "color: #e74c3c; font-size: 12px; padding: 2px 8px; "
        "border: 1px solid #e74c3c; border-radius: 4px;"
    );
    m_labelNonSauvegardees->setVisible(false);

    lignetitre->addWidget(titreXp);
    lignetitre->addStretch();
    lignetitre->addWidget(m_labelNonSauvegardees);
    mainLayout->addLayout(lignetitre);

    // tableau expériences
    m_tableXp = new QTableWidget(this);
    m_tableXp->setColumnCount(XP_NB_COLS);
    m_tableXp->setHorizontalHeaderLabels({
        "Date / Heure",
        "Corps",
        "Durée (s sim.)",
        "Énergie totale",
        "Sauvegardée",
        "Nom template",
        "Stabilité"
    });

    m_tableXp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableXp->horizontalHeader()->setSectionResizeMode(XP_NB_CORPS, QHeaderView::ResizeToContents);
    m_tableXp->horizontalHeader()->setSectionResizeMode(XP_SAUVEGARDE, QHeaderView::ResizeToContents);

    m_tableXp->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableXp->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableXp->setSelectionMode(QAbstractItemView::SingleSelection);

    m_tableXp->verticalHeader()->setDefaultSectionSize(36);
    m_tableXp->verticalHeader()->hide();
    m_tableXp->setAlternatingRowColors(false);
    m_tableXp->horizontalHeader()->setStyleSheet(
        "QHeaderView::section { font-weight: bold; padding: 6px; }"
    );
    m_tableXp->setSortingEnabled(false);

    mainLayout->addWidget(m_tableXp, 3); // 3 parts de hauteur

    // boutons expériences
    QHBoxLayout *barreXp = new QHBoxLayout();

    m_btnSauvegarder = new QPushButton("Enregistrer");
    m_btnExportTableauXp = new QPushButton("Exporter tableau PDF");
    m_btnExportTraceXp = new QPushButton("Exporter trace PDF");
    m_btnRelancer = new QPushButton("Relancer");

    m_btnRelancer->setEnabled(false);
    m_btnSauvegarder->setEnabled(false);
    m_btnExportTraceXp->setEnabled(false);

    //style des différents boutons de l'historique
    m_btnRelancer->setStyleSheet(
        "QPushButton { background-color: #27ae60; color: white; "
        "font-weight: bold; padding: 2px 6px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #229954; }"
        "QPushButton:pressed { background-color: #1e8449; }"
        "QPushButton:disabled { background-color: #145a32; "
        "color: #aaaaaa; }"
        );
    m_btnSauvegarder->setStyleSheet(
        "QPushButton { background-color: #f39c12; color: white; "
        "font-weight: bold; padding: 2px 6px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #e67e22; }"
        "QPushButton:pressed { background-color: #d35400; }"
        "QPushButton:disabled { background-color: #7f6030; color: #aaaaaa; }"
        );
    m_btnExportTableauXp->setStyleSheet(
        "QPushButton { background-color: #2980b9; color: white; "
        "font-weight: bold; padding: 2px 6px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #2471a3; }"
        "QPushButton:pressed { background-color: #1a5276; }"
        "QPushButton:disabled { background-color: #1a5276; color: #aaaaaa; }"
        );
    m_btnExportTraceXp->setStyleSheet(
        "QPushButton { background-color: #8e44ad; color: white; "
        "font-weight: bold; padding: 2px 6px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #7d3c98; }"
        "QPushButton:pressed { background-color: #6c3483; }"
        "QPushButton:disabled { background-color: #5b2c6f; color: #aaaaaa; }"
        );

    barreXp->addWidget(m_btnRelancer);
    barreXp->addWidget(m_btnSauvegarder);
    barreXp->addWidget(m_btnExportTableauXp);
    barreXp->addStretch();
    barreXp->addWidget(m_btnExportTraceXp);
    mainLayout->addLayout(barreXp);

    // séparateur visuel entre les deux compartiments
    QFrame *separateur = new QFrame();
    separateur->setFrameShape(QFrame::HLine);
    separateur->setStyleSheet("color: #444;");
    mainLayout->addWidget(separateur);

    // =====================================================================
    // COMPARTIMENT BAS : corps de l'expérience sélectionnée
    // =====================================================================

    m_titreCorps = new QLabel("Corps de l'expérience sélectionnée");
    m_titreCorps->setStyleSheet("font-size: 15px; font-weight: bold;");
    mainLayout->addWidget(m_titreCorps);

    m_tableCorps = new QTableWidget(this);
    m_tableCorps->setColumnCount(CORPS_NB_COLS);
    m_tableCorps->setHorizontalHeaderLabels({
        "Nom",
        "Masse",
        "Pos. X",
        "Pos. Y",
        "Vit. X",
        "Vit. Y",
        "Dist.",
        "Én. cin.",
        "Tours"
    });

    m_tableCorps->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableCorps->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableCorps->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_tableCorps->setSelectionMode(QAbstractItemView::MultiSelection); // sélection multiple pour export trace

    m_tableCorps->verticalHeader()->setDefaultSectionSize(34);

    m_tableCorps->verticalHeader()->hide();

    m_tableCorps->horizontalHeader()->setStyleSheet(
        "QHeaderView::section { font-weight: bold; padding: 6px; }"
        );
    m_tableCorps->setSortingEnabled(true);

    mainLayout->addWidget(m_tableCorps, 2); // 2 parts de hauteur

    // boutons corps
    QHBoxLayout *barreCorps = new QHBoxLayout();

    m_btnExportTableauCorps = new QPushButton("Exporter tableau corps PDF");

    m_btnExportTableauCorps->setEnabled(false);

    m_btnExportTableauCorps->setStyleSheet(
        "QPushButton { background-color: #2980b9; color: white; "
        "font-weight: bold; padding: 2px 6px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #2471a3; }"
        "QPushButton:pressed { background-color: #1a5276; }"
        "QPushButton:disabled { background-color: #1a5276; color: #aaaaaa; }"
        );

    barreCorps->addWidget(m_btnExportTableauCorps);
    barreCorps->addStretch();
    mainLayout->addLayout(barreCorps);

    // connexions
    connect(m_btnRelancer, &QPushButton::clicked,this, &HistoryDialog::onBtnRelancerClicked);

    connect(m_tableXp, &QTableWidget::itemSelectionChanged, this, &HistoryDialog::onExperienceSelectionnee);

    connect(m_btnSauvegarder, &QPushButton::clicked, this, &HistoryDialog::onBtnSauvegarderClicked);

    connect(m_btnExportTableauXp,&QPushButton::clicked, this, &HistoryDialog::onBtnExportTableauXpClicked);

    connect(m_btnExportTraceXp, &QPushButton::clicked, this, &HistoryDialog::onBtnExportTraceXpClicked);

    connect(m_btnExportTableauCorps, &QPushButton::clicked, this, &HistoryDialog::onBtnExportTableauCorpsClicked);
}

// ------------------------------------------------------------------
// calculerDistanceParcourue : somme des distances entre chaque point
// consécutif de la trace — donne la distance totale parcourue
// ------------------------------------------------------------------
float HistoryDialog::calculerDistanceParcourue(const std::vector<Vect> &trace) const
{
    float distance = 0.0f;
    for (int i = 1; i < (int)trace.size(); i++) {
        float dx = trace[i].GetX() - trace[i-1].GetX();
        float dy = trace[i].GetY() - trace[i-1].GetY();
        distance += std::sqrt(dx*dx + dy*dy);
    }
    return distance;
}

void HistoryDialog::ajouterExperience(const ExperienceRecord &record)
{
    m_records.prepend(record);
    rafraichirTableauXp();
    mettreAJourIndicateur();
}

void HistoryDialog::marquerSauvegardee(int index, const QString &nom)
{
    if (index < 0 || index >= m_records.size()) return;
    m_records[index].sauvegardee = true;
    m_records[index].nomTemplate = nom;
    rafraichirTableauXp();
    mettreAJourIndicateur();
}

int HistoryDialog::indexSelectionne() const
{
    QList<QTableWidgetItem*> sel = m_tableXp->selectedItems();
    if (sel.isEmpty()) return -1;
    return sel.first()->row();
}

const ExperienceRecord& HistoryDialog::getRecord(int index) const
{
    return m_records.at(index);
}

int HistoryDialog::nbExperiences() const
{
    return m_records.size();
}

void HistoryDialog::mettreAJourIndicateur()
{
    int nonSauv = 0;
    for (const ExperienceRecord &r : std::as_const(m_records)) {
        if (!r.sauvegardee) nonSauv++;
    }

    if (nonSauv > 0) {
        m_labelNonSauvegardees->setText(
            QString("%1 expérience%2 non sauvegardée%2")
                .arg(nonSauv)
                .arg(nonSauv > 1 ? "s" : "")
        );
        m_labelNonSauvegardees->setVisible(true);
    } else {
        m_labelNonSauvegardees->setVisible(false);
    }
}

void HistoryDialog::rafraichirTableauXp()
{
    m_tableXp->setSortingEnabled(false);
    m_tableXp->setRowCount(0);

    for (int i = 0; i < m_records.size(); i++) {
        const ExperienceRecord &r = m_records[i];
        m_tableXp->insertRow(i);

        auto item = [](const QString &texte) {
            QTableWidgetItem *it = new QTableWidgetItem(texte);
            it->setTextAlignment(Qt::AlignCenter);
            return it;
        };

        m_tableXp->setItem(i, XP_DATE, item(r.dateHeure.toString("dd/MM/yyyy  hh:mm:ss")));
        m_tableXp->setItem(i, XP_NB_CORPS, item(QString::number(r.nbCorps)));
        m_tableXp->setItem(i, XP_DUREE,    item(QString::number(r.dureeTicks, 'f', 2)));
        m_tableXp->setItem(i, XP_ENERGIE,  item(QString::number(r.energieTotale, 'f', 4)));

        QTableWidgetItem *itemSauv = item(r.sauvegardee ? "Oui" : "Non");
        itemSauv->setForeground(QBrush(r.sauvegardee ? QColor(46, 204, 113) : QColor(231, 76, 60)));
        m_tableXp->setItem(i, XP_SAUVEGARDE, itemSauv);

        QTableWidgetItem *itemNom = item(r.nomTemplate);
        if (r.nomTemplate.isEmpty()) itemNom->setForeground(QBrush(QColor(102, 102, 102)));
        m_tableXp->setItem(i, XP_NOM, itemNom);

        colorerLigneXp(i, r.sauvegardee);
    }

    m_tableXp->setSortingEnabled(false);
}

void HistoryDialog::colorerLigneXp(int row, bool sauvegardee)
{
    QColor fond = sauvegardee
        ? QColor(30, 80, 50, 60)
        : QColor(50, 50, 50, 40);

    for (int col = 0; col < XP_NB_COLS; col++) {
        QTableWidgetItem *it = m_tableXp->item(row, col);
        if (it) it->setBackground(fond);
    }
}

void HistoryDialog::rafraichirTableauCorps(int indexXp)
{
    m_tableCorps->setSortingEnabled(false);
    m_tableCorps->setRowCount(0);

    if (indexXp < 0 || indexXp >= m_records.size()) return;

    const ExperienceRecord &r = m_records[indexXp];
    m_titreCorps->setText(
        QString("Corps | %1  -  Instant : %2 s").arg(r.dateHeure.toString("dd/MM hh:mm:ss")).arg(r.dureeTicks, 0, 'f', 2)
        );

    for (int i = 0; i < (int)r.corps.size(); i++) {
        const Corps &c = r.corps[i];
        m_tableCorps->insertRow(i);

        auto item = [](const QString &texte) {
            QTableWidgetItem *it = new QTableWidgetItem(texte);
            it->setTextAlignment(Qt::AlignCenter);
            return it;
        };

        float dist = calculerDistanceParcourue(c.GetTrace());
        double cinetique = c.CalcCinetique();

        m_tableCorps->setItem(i, CORPS_NOM, item(QString::fromStdString(c.GetNom())));
        m_tableCorps->setItem(i, CORPS_MASSE, item(QString::number(c.GetMasse(), 'f', 3)));
        m_tableCorps->setItem(i, CORPS_POS_X, item(QString::number(c.GetPosition().GetX(), 'f', 2)));
        m_tableCorps->setItem(i, CORPS_POS_Y, item(QString::number(c.GetPosition().GetY(), 'f', 2)));
        m_tableCorps->setItem(i, CORPS_VIT_X, item(QString::number(c.GetVitesse().GetX(), 'f', 3)));
        m_tableCorps->setItem(i, CORPS_VIT_Y, item(QString::number(c.GetVitesse().GetY(), 'f', 3)));
        m_tableCorps->setItem(i, CORPS_DIST, item(QString::number(dist, 'f', 2)));
        m_tableCorps->setItem(i, CORPS_CINETIQUE, item(QString::number(cinetique, 'f', 4)));
        //m_tableCorps->setItem(i, CORPS_TOURS, item(""));
        m_tableCorps->setItem(i, CORPS_TOURS, item(QString::number(c.GetNbTours())));
    }

    m_tableCorps->setSortingEnabled(true);
    m_btnExportTableauCorps->setEnabled(true);
}

// ------------------------------------------------------------------
// exporterTableauEnPdf : méthode générique qui exporte n'importe quel
// QTableWidget dans un PDF — utilisée pour les deux tableaux
// ------------------------------------------------------------------
void HistoryDialog::exporterTableauEnPdf(QTableWidget *table, const QString &titre)
{
    if (table->rowCount() == 0) {
        QMessageBox::information(this, "Tableau vide", "Rien à exporter.");
        return;
    }

    QString chemin = QFileDialog::getSaveFileName(
        this, "Exporter en PDF", titre + ".pdf", "PDF (*.pdf)"
        );
    if (chemin.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(chemin);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QPainter painter(&printer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le PDF.");
        return;
    }

    QRect page = painter.window();
    int margeG = 80;
    int margeD = 80;
    int largeurTotale = page.width() - margeG - margeD;
    int nbCols = table->columnCount();
    int largeurCol = largeurTotale / nbCols;
    int hauteurEntete = 120;
    int hauteurLigne = 90;
    int y = 100;

    // fond blanc
    painter.fillRect(page, Qt::white);

    // titre
    QFont fontTitre;
    fontTitre.setBold(true);
    fontTitre.setPixelSize(80);
    painter.setFont(fontTitre);
    painter.setPen(Qt::black);
    painter.drawText(margeG, y, titre);
    y += 100;

    // date d'export
    QFont fontSousTitre;
    fontSousTitre.setPixelSize(45);
    fontSousTitre.setItalic(true);
    painter.setFont(fontSousTitre);
    painter.setPen(QColor(100, 100, 100));
    painter.drawText(margeG, y, QString("Exporté le %1").arg(QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm")));
    y += 80;

    // ligne de séparation
    painter.setPen(QPen(QColor(50, 50, 50), 3));
    painter.drawLine(margeG, y, page.width() - margeD, y);
    y += 20;

    // entêtes du tableau
    QFont fontEntete;
    fontEntete.setBold(true);
    fontEntete.setPixelSize(50);
    painter.setFont(fontEntete);

    // fond de l'entête
    painter.fillRect(margeG, y, largeurTotale, hauteurEntete, QColor(40, 40, 40));

    painter.setPen(Qt::white);
    for (int col = 0; col < nbCols; col++) {
        QString entete = table->horizontalHeaderItem(col)
        ? table->horizontalHeaderItem(col)->text() : "";
        painter.drawText(margeG + col * largeurCol + 10, y, largeurCol - 10, hauteurEntete, Qt::AlignVCenter | Qt::AlignLeft, entete);
    }
    y += hauteurEntete;

    // lignes du tableau
    QFont fontLigne;
    fontLigne.setPixelSize(42);
    painter.setFont(fontLigne);

    for (int row = 0; row < table->rowCount(); row++) {
        // alternance de couleur des lignes
        QColor fondLigne = (row % 2 == 0) ? QColor(245, 245, 245) : Qt::white;
        painter.fillRect(margeG, y, largeurTotale, hauteurLigne, fondLigne);

        // bordure basse de la ligne
        painter.setPen(QPen(QColor(200, 200, 200), 1));
        painter.drawLine(margeG, y + hauteurLigne, page.width() - margeD, y + hauteurLigne);

        painter.setPen(Qt::black);
        for (int col = 0; col < nbCols; col++) {
            QString valeur = table->item(row, col)
            ? table->item(row, col)->text() : "";
            painter.drawText(margeG + col * largeurCol + 10, y, largeurCol - 10, hauteurLigne, Qt::AlignVCenter | Qt::AlignLeft, valeur);
        }

        y += hauteurLigne;

        if (y > page.height() - 200) {
            printer.newPage();
            painter.fillRect(page, Qt::white);
            y = 100;
        }
    }

    // bordure du tableau
    painter.setPen(QPen(QColor(50, 50, 50), 2));
    painter.drawRect(margeG, 300, largeurTotale,hauteurEntete + hauteurLigne * table->rowCount());

    // pied de page
    QFont fontPied;
    fontPied.setPixelSize(35);
    fontPied.setItalic(true);
    painter.setFont(fontPied);
    painter.setPen(QColor(150, 150, 150));
    painter.drawText(margeG, page.height() - 60, QString("Le Problème à Trois Corps  |  %1 lignes").arg(table->rowCount()));

    painter.end();
    QMessageBox::information(this, "Exporté", "PDF exporté avec succès.");
}

void HistoryDialog::exporterTraceExperienceActuelle()
{
    if (m_records.isEmpty()) {
        QMessageBox::warning(this, "Aucune expérience", "Aucune expérience à exporter.");
        return;
    }
    // on exporte toujours le record le plus récent (index 0)
    int idx = 0;
    // on réutilise directement le code d'export en passant l'index
    exporterTrace(idx);
}

void HistoryDialog::onBtnExportTraceXpClicked()
{
    int idx = indexSelectionne();
    if (idx < 0 || idx >= m_records.size()) return;
    exporterTrace(idx);
}

void HistoryDialog::exporterTrace(int idx)
{
    if (idx < 0 || idx >= m_records.size()) return;

    const ExperienceRecord &r = m_records[idx];
    if (r.corps.empty()) {
        QMessageBox::warning(this, "Trace vide", "Aucune trace disponible.");
        return;
    }

    QString chemin = QFileDialog::getSaveFileName(
        this, "Exporter trace", "trace_experience.pdf", "PDF (*.pdf)"
        );
    if (chemin.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(chemin);
    printer.setPageSize(QPageSize(QSizeF(200, 200), QPageSize::Millimeter)); // page carrée
    printer.setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);

    QPainter painter(&printer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le PDF.");
        return;
    }

    QRect page = painter.window();
    int cx = page.width() / 2;
    int cy = page.height() / 2;
    float scale = 8.0f;

    // fond blanc
    painter.fillRect(page, Qt::white);

    // grille
    float espacementPx = scale * 50.0f;
    QPen styloGrille(QColor(200, 200, 200, 180), 1.5f);
    painter.setPen(styloGrille);

    float debutX = std::fmod((float)cx, espacementPx);
    int nbLignesV = (int)((float)page.width() / espacementPx) + 1;
    for (int k = 0; k <= nbLignesV; k++) {
        float x = debutX + k * espacementPx;
        if (x > (float)page.width()) break;
        painter.drawLine(QPointF(x, 0), QPointF(x, (float)page.height()));
    }

    float debutY = std::fmod((float)cy, espacementPx);
    int nbLignesH = (int)((float)page.height() / espacementPx) + 1;
    for (int k = 0; k <= nbLignesH; k++) {
        float y = debutY + k * espacementPx;
        if (y > (float)page.height()) break;
        painter.drawLine(QPointF(0, y), QPointF((float)page.width(), y));
    }

    // axes centraux
    QPen styloAxe(QColor(150, 150, 150, 200), 2.0f);
    painter.setPen(styloAxe);
    painter.drawLine(QPointF(cx, 0), QPointF(cx, page.height()));
    painter.drawLine(QPointF(0, cy), QPointF(page.width(), cy));

    // traces
    int teinte = 0;
    for (const Corps &c : r.corps) {
        const std::vector<Vect> &trace = c.GetTrace();
        if (trace.size() < 2) { teinte += 60; continue; }

        QColor couleur = QColor::fromHsv(teinte % 360, 200, 100); // couleurs sombres sur fond blanc
        teinte += 60;

        for (int j = 1; j < (int)trace.size(); j++) {
            float x1 = cx + trace[j-1].GetX() * scale;
            float y1 = cy + trace[j-1].GetY() * scale;
            float x2 = cx + trace[j].GetX() * scale;
            float y2 = cy + trace[j].GetY() * scale;
            painter.setPen(QPen(couleur, 2));
            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
        teinte += 60;
    }

    // infos en bas
    int margeInfos = page.height() - 120;
    QFont fontInfos;
    fontInfos.setPixelSize(50);
    painter.setFont(fontInfos);
    painter.setPen(Qt::black);

    int largeurCol = page.width() / 4;
    painter.drawText(0, margeInfos, largeurCol, 120, Qt::AlignCenter, QString("Date : %1").arg(r.dateHeure.toString("dd/MM hh:mm")));
    painter.drawText(largeurCol, margeInfos, largeurCol, 120, Qt::AlignCenter, QString("Corps : %1").arg(r.nbCorps));
    painter.drawText(largeurCol * 2, margeInfos, largeurCol, 120, Qt::AlignCenter, QString("Durée : %1 s").arg(QString::number(r.dureeTicks, 'f', 2)));
    painter.drawText(largeurCol * 3, margeInfos, largeurCol, 120, Qt::AlignCenter, QString("Énergie : %1").arg(QString::number(r.energieTotale, 'f', 4)));

    painter.end();
    QMessageBox::information(this, "Exporté", "Trace exportée avec succès.");
}

void HistoryDialog::onExperienceSelectionnee()
{
    int idx = indexSelectionne();
    bool valide = (idx >= 0 && idx < m_records.size());

    m_btnExportTraceXp->setEnabled(valide);
    m_btnRelancer->setEnabled(valide);

    if (!valide) {
        m_btnSauvegarder->setEnabled(false);
        m_tableCorps->setRowCount(0);
        return;
    }

    m_btnSauvegarder->setEnabled(!m_records[idx].sauvegardee);

    rafraichirTableauCorps(idx);
}

void HistoryDialog::onBtnSauvegarderClicked()
{
    int idx = indexSelectionne();
    if (idx < 0 || idx >= m_records.size()) return;
    if (m_records[idx].sauvegardee) {
        QMessageBox::warning(this, "Déjà enregistrée", QString("L'expérience \"%1\" est déjà enregistrée.").arg(m_records[idx].nomTemplate));
        return;
    }
    emit sauvegarderDemandee(idx);
}

void HistoryDialog::onBtnExportTableauXpClicked()
{
    exporterTableauEnPdf(m_tableXp, "historique_experiences");
}

void HistoryDialog::onBtnExportTableauCorpsClicked()
{
    exporterTableauEnPdf(m_tableCorps, "tableau_corps");
}

void HistoryDialog::onBtnRelancerClicked()
{
    int idx = indexSelectionne();
    if (idx < 0 || idx >= m_records.size()) return;
    emit relancerDemande(idx);
}

ExperienceRecord& HistoryDialog::getRecordModifiable(int index)
{
    return m_records[index];
}

void HistoryDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    m_titreCorps->setText("Corps de l'expérience sélectionnée");
    m_tableCorps->setRowCount(0);
    rafraichirTableauXp();
    mettreAJourIndicateur();
}
