#ifndef SIMVIEW_H
#define SIMVIEW_H
//cette classe est la version améliorer de vuesimulation de la première version du projet

/*L'objectif de cette classe est de laisser dessiné toutes simulations avec les traces etc. Egalement de laisser soit la possiblité de créer des corps avec des couleurs choisient par
l'utilisateur ou bien de généré des couleurs aléatoires pour les expériences aléatoires*/
#include <QWidget>
#include <QColor>
#include <QMap>

class SimView : public QWidget
{
    Q_OBJECT
private:

    QMap<int, QColor> m_couleurs;//permet d'avoir un tableau associatif, reliant un entier à une couleur m_couleurs[i] = rouge
    QColor getCouleurCorps(int numero); // on regarde si la map contient déjà une couleur pour ce numéro. Si oui on la retourne, sinon on en génère une aléatoire, on la stocke, et on la retourne.
    void drawBackground(QPainter& painter);//Permet de mettre l'espace de simulation sur un fond noir

    float m_scale  = 0.7f; // facteur d'échelle pixels/unité physique
    void drawTraces (QPainter& painter, int centerX, int centerY);
    void drawCorps (QPainter& painter, int centerX, int centerY);


    // --- DÉPLACEMENT (pan) ---
    QPointF m_offset;          // décalage de la caméra en pixels (initialisé à 0,0)
    QPointF m_dragStart;       // position souris au début du drag
    bool    m_dragging = false; // est-ce qu'on est en train de dragger ?

    // --- VECTEURS VITESSE ---
    bool m_showVitesse = false; // affichage activé ou non

    // --- grille ----
    bool m_showGrille = true;

    // --- Affichage des noms ---
    bool m_showNoms = false;

public:
    explicit SimView(QWidget *parent = nullptr);
    //retourne l'index du corps sous le curseur, -1 si aucun
    void resetVue();

    void drawGrille(QPainter &painter, float centerX, float centerY);

    // --- VECTEURS VITESSE ---
    void drawVitesses(QPainter& painter, float centerX, float centerY);
    // On utilise float pour centerX/centerY maintenant (cohérent avec le pan)

protected:
    // Qt appelle paintEvent à chaque update() — c'est ici que tout est dessiné
    void paintEvent(QPaintEvent *event)override ;

    // --- ZOOM ---
    // Le zoom se fait en multipliant/divisant m_scale selon la molette
    void wheelEvent(QWheelEvent *event) override;

    // --- DÉPLACEMENT (pan) ---
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)  override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void toggleVitesses();
    void toggleGrille();
    void toggleNoms();
    void setCouleurCorps(int index, QColor couleur);
    void clearCouleurs();

signals:
    void corpsClique(int index); // émis quand l'utilisateur clique sur un corps
};

#endif
