#include "bodypanel.h"
#include "ui_bodypanel.h"
#include "corps.h"
#include <QTimer>



BodyPanel::BodyPanel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BodyPanel)
{
    ui->setupUi(this);
    setFixedSize(300, 500);//fixation de la taille de la fenêtre
    setWindowTitle("Paramètre du corps");

    m_timer = new QTimer(this);//instantation du timer
    connect(m_timer,SIGNAL(timeout()),this,SLOT(rafraichir()));//on connecte le timeout effectuer par m_timer avec la méthode rafraichir
    m_timer->start(100);// rafraîchissement toutes les 100ms
}


void BodyPanel :: chargerCorps(int index){
    m_indexCorps = index;

    Corps &c = Corps::GetIndex()[index];//récupère une référence du corps à l'index voulu
    //chargement dans le bodypanel de toutes les données pour le corps séléctionné
    ui->labelNomCorps->setText(QString::fromStdString(c.GetNom()));
    ui->editNom->setText(QString::fromStdString(c.GetNom()));
    ui->editMasse->setText(QString::number(c.getMasse()));
    ui->editX->setText(QString::number(c.GetPosition().GetX()));
    ui->editY->setText(QString::number(c.GetPosition().GetY()));
    ui->editVx->setText(QString::number(c.GetVitesse().GetX()));
    ui->editVy->setText(QString::number(c.GetVitesse().GetY()));

    show(); // ouvre le dialog
    move(1100, 200); // décale le panel vers la droite pour continuer à voir la simulation
}

void BodyPanel::rafraichir(){
    if (m_indexCorps == -1){
        return; // si pas de corps sélectionné
    }
    Corps &c = Corps::GetIndex()[m_indexCorps];
    //rafraichissement de toutes les données du corps lors de l'ouverture du bodypanel toutes les 100ms
    ui->editX->setText(QString::number(c.GetPosition().GetX()));
    ui->editY->setText(QString::number(c.GetPosition().GetY()));
    ui->editVx->setText(QString::number(c.GetVitesse().GetX()));
    ui->editVy->setText(QString::number(c.GetVitesse().GetY()));
}


BodyPanel::~BodyPanel()
{
    delete ui;
}
