// /*
// Nom: MoveGuard.h

// Description: classe implémentant le RAII pour qu’une fonction utilisant cette classe puisse mettre
// temporairement une pièce à un endroit sur l’échiquier,
// et que la pièce s’enlève automatiquement à la destruction de l’instance.

// Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
// Date: 14 Avril 2023
// */


#include "Piece.h"
#include <qpushbutton.h>

#ifndef MOVEGUARD_H
#define MOVEGUARD_H

// Classe RAII
class MoveGuard
{
public:
    MoveGuard(QPushButton *&selectedButton, QPushButton *&lastValidButton, std::shared_ptr<model::Piece> &piece, int rowDest, int colDest, bool *&undo) : m_row(piece->row()), m_col(piece->col()), m_selectedButton(selectedButton), m_lastValidButton(lastValidButton), m_piece(piece), m_undo(undo)
    {
        m_piece->setRow(rowDest);
        m_piece->setCol(colDest);
    }

    ~MoveGuard()
    {
        if (*m_undo == true)
        {
            m_piece->setRow(m_row);
            m_piece->setCol(m_col);
        }
        else
        {
            m_selectedButton->setIcon(m_piece->icon());
            m_selectedButton->setIconSize(QSize(45, 45));
            m_lastValidButton->setIcon(QIcon());
        }
    }

private:
    int m_row, m_col;
    std::shared_ptr<model::Piece> m_piece;
    QPushButton *m_selectedButton;
    QPushButton *m_lastValidButton;
    bool *m_undo;
};

#endif