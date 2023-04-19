/*
Nom: Piece.cpp
Description: Definit les methodes des classes derivees de Piece
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 14 Avril 2023
*/

#include "Piece.h"

int model::Piece::s_kingCount = 0;

int model::Piece::isPieceAt(int row, int col, std::list<std::shared_ptr<Piece>> pieces)
{
    for (const std::shared_ptr<Piece> piece : pieces)
    {
        if (piece->row() == row && piece->col() == col)
        {
            if (piece->color() == Piece::Color::White)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }
    return 0;
}

bool model::King::validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest)
{
    // verifier que source != destination
    if (m_row == rowDest && m_col == colDest)
    {
        return false;
    }

    // Verification que le roi se deplace d'une case maximum dans n'importe quelle direction
    if (abs(rowDest - m_row) > 1 || abs(colDest - m_col) > 1)
    {
        return false;
    }

    // Verification que le roi ne se deplace pas sur une case deja occupee par une autre piece de sa couleur
    if (isPieceAt(rowDest, colDest, pieces) == 1 && m_color == Piece::Color::White)
    {
        return false;
    }
    else if (isPieceAt(rowDest, colDest, pieces) == 2 && m_color == Piece::Color::Black)
    {
        return false;
    }

    // Verification que le mouvement ne mettrai pas le roi en echec
    for (const std::shared_ptr<Piece> piece : pieces)
    {
        if (piece->color() != m_color)
        {
            if (piece->validMove(pieces, rowDest, colDest))
            {
                return false;
            }
        }
    }

    // Si toutes les conditions sont remplies, le deplacement est valide
    return true;
}

bool model::Queen::validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest)
{
    // verifier que source != destination
    if (m_row == rowDest && m_col == colDest)
    {
        return false;
    }

    // Verification que la reine se deplace en ligne droite ou en diagonale
    if (rowDest != m_row && colDest != m_col && abs(rowDest - m_row) != abs(colDest - m_col))
    {
        return false;
    }

    // Verification qu'il n'y a pas d'obstacles sur la trajectoire de la reine
    int rowDirection = (rowDest > m_row) - (rowDest < m_row);
    int colDirection = (colDest > m_col) - (colDest < m_col);
    int r = m_row + rowDirection;
    int c = m_col + colDirection;
    while (r != rowDest || c != colDest)
    {
        for (const std::shared_ptr<Piece> piece : pieces)
        {
            if (piece->row() == r && piece->col() == c)
            {
                return false;
            }
        }
        r += rowDirection;
        c += colDirection;
    }

    // Verification que le roi ne se deplace pas sur une case deja occupee par une autre piece de sa couleur
    if (isPieceAt(rowDest, colDest, pieces) == 1 && m_color == Piece::Color::White)
    {
        return false;
    }
    else if (isPieceAt(rowDest, colDest, pieces) == 2 && m_color == Piece::Color::Black)
    {
        return false;
    }

    // Si toutes les conditions sont remplies, le deplacement est valide
    return true;
}

bool model::Bishop::validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest)
{
    // verifier que source != destination
    if (m_row == rowDest && m_col == colDest)
    {
        return false;
    }

    // verifier que le mouvement est bien diagonal
    int rowDiff = std::abs(m_row - rowDest);
    int colDiff = std::abs(m_col - colDest);
    if (rowDiff != colDiff)
    {
        return false;
    }

    // verifier qu'il n'y a pas de pieces qui bloquent le trajet
    int rowDir = (m_row < rowDest) ? 1 : -1;
    int colDir = (m_col < colDest) ? 1 : -1;
    int i = m_row + rowDir;
    int j = m_col + colDir;
    while (i != rowDest && j != colDest)
    {
        if (isPieceAt(i, j, pieces) != 0)
        {
            return false;
        }
        i += rowDir;
        j += colDir;
    }

    // verifier qu'il n'y a pas de piece de la meme couleur a la destination
    if (isPieceAt(rowDest, colDest, pieces) == 1 && m_color == Piece::Color::White)
    {
        return false;
    }
    else if (isPieceAt(rowDest, colDest, pieces) == 2 && m_color == Piece::Color::Black)
    {
        return false;
    }

    return true;
}