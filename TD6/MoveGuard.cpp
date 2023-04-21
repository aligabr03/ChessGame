/*
Nom: MoveGuard.cpp
Description: Implementation des du constructeur et destructeur de la classe MoveGuard
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#include "MoveGuard.h"

model::MoveGuard::MoveGuard(QPushButton*& selectedButton, QPushButton*& lastValidButton, std::shared_ptr<model::Piece>& piece, int rowDest, int colDest, bool*& undo) :
    m_row(piece->row()), m_col(piece->col()), m_selectedButton(selectedButton), m_lastValidButton(lastValidButton), m_piece(piece), m_undo(undo) {
	m_piece->setRow(rowDest);
	m_piece->setCol(colDest);
}

model::MoveGuard::~MoveGuard() {
        if (*m_undo == true) {
            m_piece->setRow(m_row);
            m_piece->setCol(m_col);
        }
        else {
            m_selectedButton->setIcon(m_piece->icon());
            m_selectedButton->setIconSize(QSize(45, 45));
            m_lastValidButton->setIcon(QIcon());
        }
}