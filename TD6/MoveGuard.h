#include "Piece.h"
#include <qpushbutton.h>

//Classe RAII
class MoveGuard {
public:
    MoveGuard(QPushButton*& selectedButton, QPushButton*& lastValidButton, std::shared_ptr<model::Piece>& piece, int rowDest, int colDest, bool*& undo) :
        m_row(piece->row()), m_col(piece->col()), m_selectedButton(selectedButton), m_lastValidButton(lastValidButton), m_piece(piece), m_undo(undo)
    {
        m_selectedButton->setIcon(piece->icon());
        m_selectedButton->setIconSize(QSize(45, 45));
        m_piece->setRow(rowDest);
        m_piece->setCol(colDest);
        m_lastValidButton->setIcon(QIcon());
    }

    ~MoveGuard()
    {
        if (*m_undo == true) {
            m_selectedButton->setIcon(QIcon());
            m_piece->setRow(m_row);
            m_piece->setCol(m_col);
            m_lastValidButton->setIcon(m_piece->icon());
            m_lastValidButton->setIconSize(QSize(45, 45));
        }
    }

    
private:
    int m_row, m_col;
    std::shared_ptr<model::Piece> m_piece;
    QPushButton* m_selectedButton;
    QPushButton* m_lastValidButton;
    bool* m_undo;
};


