/*
Nom: MoveGuard.h
Description: classe implementant le RAII pour qu'une fonction utilisant cette classe puisse mettre temporairement une piece a un endroit sur l'echiquier,
et que la piece s'enleve automatiquement a la destruction de l'instance
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#ifndef MOVEGUARD_H
#define MOVEGUARD_H

#include "Piece.h"
#include <qpushbutton.h>

namespace model {
    //Classe RAII
    class MoveGuard {
    public:
        MoveGuard(QPushButton*& selectedButton, QPushButton*& lastValidButton, std::shared_ptr<model::Piece>& piece, int rowDest, int colDest, bool*& undo);
        ~MoveGuard();

    private:
        int m_row, m_col;
        std::shared_ptr<model::Piece> m_piece;
        QPushButton* m_selectedButton;
        QPushButton* m_lastValidButton;
        bool* m_undo;
    };
}

#endif


