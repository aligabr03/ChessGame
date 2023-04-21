/*
Nom: Piece.h
Description: Main permettant de lancer le jeu.
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 14 Avril 2023
*/
#include "ChessWindow.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try
    {
        // Creer la fenetre de jeu
        view::ChessWindow w;
        w.show();

        // Executer l'application
        return a.exec();
    }
    catch (const std::runtime_error &error)
    {
        // Afficher un message d'erreur
        QMessageBox::critical(nullptr, "Error", error.what());
        return 1;
    }
}