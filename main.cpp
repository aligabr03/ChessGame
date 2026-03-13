/*
Nom: main.cpp
Description: Main permettant de lancer le jeu.
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#include "ChessWindow.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    view::ChessWindow w;
    w.show();

    // Executer l'application
    return a.exec();
}