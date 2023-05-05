/*
Nom: MoveGuard.cpp
Description: Implementation des du constructeur et destructeur de la classe MoveGuard
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 5 Mai 2023
*/

#include "MoveGuard.h"

namespace model {

    MoveGuard::MoveGuard(QPushButton*& selectedButton, QPushButton*& lastValidButton, std::list<std::shared_ptr<Piece>>& pieces, std::shared_ptr<model::Piece>& piece, int rowDest, int colDest, bool*& undo) : row_(piece->row()), col_(piece->col()), piece_(piece), selectedButton_(selectedButton), lastValidButton_(lastValidButton), undo_(undo), pieces_(pieces)
    {
        piece_->setRow(rowDest);
        piece_->setCol(colDest);
    }

    MoveGuard::~MoveGuard()
    {
        const int ICON_SIZE = 45;
        if (*undo_ == true)
        {
            piece_->setRow(row_);
            piece_->setCol(col_);
            pieces_.push_back(removedPiece_);
        }
        else
        {
            selectedButton_->setIcon(piece_->icon());
            selectedButton_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
            lastValidButton_->setIcon(QIcon());
        }
    }
}