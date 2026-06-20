#ifndef BODYPANEL_H
#define BODYPANEL_H

#include <QWidget>
#include <QDialog>
#include <QColor>

namespace Ui {
class BodyPanel;
}

class BodyPanel : public QDialog
{
    Q_OBJECT

public:
    explicit BodyPanel(QWidget *parent = nullptr);
    ~BodyPanel();

    //charge les données du corps d'index i
    void chargerCorps(int index);

private slots:
    void rafraichir(); // appelé toutes les 100ms pour mettre à jour position et vitesse
private:
    Ui::BodyPanel *ui;
    int m_indexCorps = -1;
    QTimer *m_timer;//timer pour actualiser les paramètres dans le bodypanel
};

#endif
