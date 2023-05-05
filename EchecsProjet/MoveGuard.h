/*
Nom: MoveGuard.h
Description: classe implementant le RAII pour qu'une fonction utilisant cette classe puisse mettre temporairement une piece a un endroit sur l'echiquier,
et que la piece s'enleve automatiquement a la destruction de l'instance
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 5 Mai 2023
*/

#ifndef MOVEGUARD_H
#define MOVEGUARD_H

#include "Piece.h"
#include <qpushbutton.h>

namespace model
{
    // Classe RAII
    class MoveGuard
    {
    public:
        MoveGuard(QPushButton*& selectedButton, QPushButton*& lastValidButton, std::list<std::shared_ptr<Piece>>& pieces, std::shared_ptr<model::Piece>& piece, int rowDest, int colDest, bool*& undo);
        ~MoveGuard();

    private:
        int row_, col_;
        std::shared_ptr<model::Piece> piece_;
        std::shared_ptr<model::Piece> removedPiece_;
        QPushButton* selectedButton_;
        QPushButton* lastValidButton_;
        bool*& undo_;
        std::list<std::shared_ptr<Piece>> pieces_;
    };
}

#endif