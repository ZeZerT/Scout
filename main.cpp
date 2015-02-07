#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/* TODO
 *
 * Garder l'appli au premier plan
 * barre de chargement pour voir environ le %
 */
