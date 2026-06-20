#include "mainwindow.h"
#include "modele.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Important : à définir AVANT QStandardPaths pour que le chemin soit stable
    QCoreApplication::setOrganizationName("ProjetTroisCorps");
    QCoreApplication::setApplicationName("ProblemeATroisCorps");

    // Recharge les templates perso sauvegardées lors des sessions précédentes
    Modele::ChargerDepuisDisque();

    MainWindow w;
    w.show();
    return a.exec();
}
