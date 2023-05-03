/*
Nom: MoveGuard.cpp
Description: Implementation des du constructeur et destructeur de la classe MoveGuard
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#include "MoveGuard.h"

model::MoveGuard::MoveGuard(QPushButton *&selectedButton, QPushButton *&lastValidButton, std::shared_ptr<model::Piece> &piece, int rowDest, int colDest, bool *&undo) : m_row_(piece->row()), m_col_(piece->col()), m_piece_(piece), m_selectedButton_(selectedButton), m_lastValidButton_(lastValidButton), m_undo_(undo)
{
    m_piece_->setRow(rowDest);
    m_piece_->setCol(colDest);
}

model::MoveGuard::~MoveGuard()
{
    const int ICON_SIZE = 45;
    if (*m_undo_ == true)
    {
        m_piece_->setRow(m_row_);
        m_piece_->setCol(m_col_);
    }
    else
    {
        m_selectedButton_->setIcon(m_piece_->icon());
        m_selectedButton_->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        m_lastValidButton_->setIcon(QIcon());
    }
}