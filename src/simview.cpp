#include "simview.h"
#include <QRandomGenerator> //utiliser pour généré des couleurs aléatoires
#include <QWheelEvent> //utilisé pour le zoom
#include <QMouseEvent> //utilisé pour le pan
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <math.h> //sqrt
#include <cmath>
#include "vect.h"
#include "corps.h"

SimView::SimView(QWidget *parent)
    : QWidget(parent)
{
    // constructeur
}

void SimView::wheelEvent(QWheelEvent *event)
{
    // angleDelta().y() > 0 = molette vers le haut = zoom avant
    float facteur = (event->angleDelta().y() > 0) ? 1.1f : 0.9f;
    m_scale *= facteur;

    // On borne le zoom pour éviter des valeurs absurdes
    m_scale = qBound(0.1f, m_scale, 50.0f);

    update(); // redessine immédiatement
}

void SimView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        float centerX = width()  / 2.0f + m_offset.x();
        float centerY = height() / 2.0f + m_offset.y();

        // On vérifie si le clic tombe sur un corps
        std::vector<Corps>& bodies = Corps::GetIndex();
        int n = Corps::GetNbCorps();
        for (int i = 0; i < n; i++) {
            Vect pos = bodies[i].GetPosition();
            float px = centerX + pos.GetX() * m_scale;
            float py = centerY + pos.GetY() * m_scale;

            float dx = event->position().x() - px;
            float dy = event->position().y() - py;
            float distance = std::sqrt(dx*dx + dy*dy);

            if (distance <= 12.0f) {
                emit corpsClique(i); // ouvre le BodyPanel pour ce corps
                return;              // pas de pan
            }
        }

        // Aucun corps cliqué → pan normal
        m_dragStart = event->position();
        m_dragging  = true;
    }
}

void SimView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        QPointF delta = event->position() - m_dragStart; // déplacement depuis le clic
        m_offset   += delta;   // on décale la caméra
        m_dragStart = event->position(); // on réinitialise pour le prochain move
        update();
    }
}

void SimView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
    }
}

void SimView::resetVue()
{
    m_scale  = 0.7f;
    m_offset = QPointF(0, 0);
    update();
}


QColor SimView:: getCouleurCorps(int numero){
    //Si une couleur existe déjà pour le corps en question on renvoie la couleur du corps
    if(m_couleurs.contains(numero)){
        return m_couleurs[numero];
    }

    //Dans le cas ou le corps en question n'a pas de couleur on lui créer une couleur aléatoire
    //On utilise des couleurs Hsv au lieu de RGB pour éviter des couleurs soit trop flashi ou bien trop sombres

    // - teinte (hue) : 0-359, valeur aléatoire
    // - saturation  : fixée à 220/255 → couleurs vives mais pas agressives
    // - valeur      : fixée à 230/255 → jamais trop sombre sur fond noir
    int random = QRandomGenerator::global()->bounded(360);
    QColor couleur = QColor::fromHsv(random, 220, 230);

    // On la mémorise pour que ce corps garde toujours la même couleur
    m_couleurs[numero] = couleur;
    return couleur;

}

void SimView::toggleVitesses() {
    m_showVitesse = !m_showVitesse;
    update();
}

void SimView::toggleGrille()
{
    m_showGrille = !m_showGrille;
    update();
}

void SimView::toggleNoms()
{
    m_showNoms = !m_showNoms;
    update();
}

void SimView::setCouleurCorps(int index, QColor couleur)
{
    // Met à jour la couleur du corps dans la map et redessine
    m_couleurs[index] = couleur;
    update();
}

void SimView::clearCouleurs()
{
    m_couleurs.clear();
}

void SimView::drawBackground(QPainter& painter)
{
    painter.fillRect(rect(), Qt::black);//fillRect permet de remplir un rectangle avec une couleur, rect()retourne un QRect qui représente les dimensions de l'espace de simulation quand on l'appelle
}

void SimView::drawTraces(QPainter& painter, int centerX, int centerY)
{
    int n = Corps::GetNbCorps();
    std::vector<Corps>& bodies = Corps::GetIndex();

    for(int i = 0; i < n; i++)
    {
        const std::vector<Vect>& trace = bodies[i].GetTrace(); //on récupère ici dans trace, toutes les anciennes positions du ième corps pour dessiner sa trace
        QColor couleur = getCouleurCorps(i);//retourne une couleur si i présent dans le tableau ou alors crée cette couleur

        for(int j = 1; j < trace.size(); j++)//on parcours toutes les anciennes positions du ième corps
        {
            //point précédent
            float x1 = centerX + trace[j-1].GetX() * m_scale;
            float y1 = centerY + trace[j-1].GetY() * m_scale;
            //point actuel
            float x2 = centerX + trace[j].GetX() * m_scale;
            float y2 = centerY + trace[j].GetY() * m_scale;

            couleur.setAlpha(178); // 70% d'opacité
            painter.setPen(QPen(couleur, 1));//définition du craillon utilisé, avec la couleur et la taille adapté
            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));//permet de dessiner une ligne entre les deux points
        }
    }
}


void SimView::drawCorps(QPainter& painter, int centerX, int centerY)// X et Y servent à centré la simulation, sans eux des corps pourraient être invisibles
{
    int n = Corps::GetNbCorps();
    std::vector<Corps>& bodies = Corps::GetIndex();
    painter.setPen(Qt::NoPen);//pour ne pas dessiner le contour et uniquement remplir

    for(int i = 0; i < n; i++)
    {
        Vect pos = bodies[i].GetPosition();
        float x = centerX + pos.GetX() * m_scale;
        float y = centerY + pos.GetY() * m_scale;
        QColor couleur = getCouleurCorps(i);
        // halo avec fondu radial EN PREMIER
        QRadialGradient gradient(QPointF(x, y), 20);
        gradient.setColorAt(0, QColor(couleur.red(), couleur.green(), couleur.blue(), 150));
        gradient.setColorAt(1, QColor(couleur.red(), couleur.green(), couleur.blue(), 0));
        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPointF(x, y), 26, 26);

        // corps principal PAR DESSUS
        couleur.setAlpha(255);
        painter.setBrush(couleur);
        painter.drawEllipse(QPointF(x, y), 12, 12);
        if (m_showNoms) {
            painter.setPen(Qt::white);
            QString nom = QString::fromStdString(bodies[i].GetNom());
            QFontMetrics fm(painter.font());
            float largeurTexte = fm.horizontalAdvance(nom);
            painter.drawText(QPointF(x - largeurTexte / 2, y + 20), nom);
        }
    }
}

void SimView::drawVitesses(QPainter& painter, float centerX, float centerY)
{
    if (!m_showVitesse) return;

    int n = Corps::GetNbCorps();
    std::vector<Corps>& bodies = Corps::GetIndex();

    for (int i = 0; i < n; i++) {
        Vect pos = bodies[i].GetPosition();
        Vect vit = bodies[i].GetVitesse();

        // Point d'origine de la flèche : centre du corps en coordonnées écran
        float x1 = centerX + pos.GetX() * m_scale;
        float y1 = centerY + pos.GetY() * m_scale;

        // Point final de la flèche (pointe du triangle)
        float echelleVit = 6.0f;
        float x2 = x1 + vit.GetX() * echelleVit;
        float y2 = y1 + vit.GetY() * echelleVit;

        // Vecteur direction de la flèche
        float dx = x2 - x1;
        float dy = y2 - y1;
        float longueur = std::sqrt(dx*dx + dy*dy);
        if (longueur < 1.0f) continue; // vitesse quasi nulle, on saute

        // Vecteur unitaire dans la direction de la vitesse
        float ux = dx / longueur;
        float uy = dy / longueur;

        QColor couleur = getCouleurCorps(i);
        couleur.setAlpha(200);

        // Base du triangle : on recule depuis la pointe d'une taillePointe
        // La tige s'arrête ici pour ne pas recouvrir le triangle
        float taillePointe = 8.0f;
        float baseX = x2 - ux * taillePointe;
        float baseY = y2 - uy * taillePointe;

        // Tige : du centre du corps jusqu'à la base du triangle
        painter.setPen(QPen(couleur, 2));
        painter.drawLine(QPointF(x1, y1), QPointF(baseX, baseY));

        // Les deux coins de la base du triangle (perpendiculaires à la direction)
        QPointF p1(baseX + uy * taillePointe * 0.5f, baseY - ux * taillePointe * 0.5f);
        QPointF p2(baseX - uy * taillePointe * 0.5f, baseY + ux * taillePointe * 0.5f);

        // Triangle : pointe en (x2,y2), base en p1 et p2
        painter.setBrush(couleur);
        painter.setPen(Qt::NoPen);
        QPolygonF fleche;
        fleche << QPointF(x2, y2) << p1 << p2;
        painter.drawPolygon(fleche);
    }
}

void SimView::drawGrille(QPainter &painter, float centerX, float centerY)
{
    if (!m_showGrille) return;
    // espacement entre les lignes de la grille en unités physiques
    float espacement = 50.0f;
    float espacementPx = espacement * m_scale;

    QPen styloGrille(QColor(255, 255, 255, 25), 0.5f);
    painter.setPen(styloGrille);

    // lignes verticales
    float debutX = std::fmod(centerX, espacementPx);
    int nbLignesV = (int)((float)width() / espacementPx) + 1;
    for (int k = 0; k <= nbLignesV; k++) {
        double x = debutX + k * espacementPx;
        if (x > (double)width()) break;
        painter.drawLine(QPointF(x, 0), QPointF(x, (double)height()));
    }
    float debutY = std::fmod(centerY, espacementPx);
    int nbLignesH = (int)((float)height() / espacementPx) + 1;
    for (int k = 0; k <= nbLignesH; k++) {
        double y = debutY + k * espacementPx;
        if (y > (double)height()) break;
        painter.drawLine(QPointF(0, y), QPointF((double)width(), y));
    }

    // axes centraux légèrement plus visibles
    QPen styloAxe(QColor(255, 255, 255, 60), 0.8f);
    painter.setPen(styloAxe);
    painter.drawLine(QPointF(centerX, 0), QPointF(centerX, height()));
    painter.drawLine(QPointF(0, centerY), QPointF(width(), centerY));
}

void SimView::paintEvent(QPaintEvent *event)//appelé automatiquement quand la fenêtre apparaît, est redimensionnée, rafraîchie, donc Qt l'appel tout seul
{
    QWidget::paintEvent(event);//On appel la méthode QPaintEvent par défaut dans un premier temps pour éviter les beugs
    QPainter painter(this); //On crée un "pinceau" sur l'espace de simulation
    painter.setRenderHint(QPainter::Antialiasing);//l'antialiasing permet d'avoir un rendu plus lisse

    //On met l'origine au centre, car pour Qt (0,0) est en haut à gauche de l'écran
    // On applique l'offset de caméra en plus du centrage de base
    float centerX = width()  / 2.0f + m_offset.x();
    float centerY = height() / 2.0f + m_offset.y();

    drawBackground(painter);
    drawGrille(painter, centerX, centerY);
    drawTraces(painter, centerX, centerY);
    drawVitesses(painter, centerX, centerY);
    drawCorps(painter, centerX, centerY);
}




