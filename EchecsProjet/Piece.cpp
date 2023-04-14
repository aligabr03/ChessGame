#include "Piece.h"

bool Bishop::validMove(std::vector<Piece> pieces, int rowDest, int colDest)
{
    int rowSrc = m_row;
    int colSrc = m_col;

    // verifier que source != destination
    if (rowSrc == rowDest && colSrc == colDest)
    {
        return false;
    }

    // verifier que le mouvement est bien diagonal
    int rowDiff = std::abs(rowSrc - rowDest);
    int colDiff = std::abs(colSrc - colDest);
    if (rowDiff != colDiff)
    {
        return false;
    }

    // verifier qu'il n'y a pas de pieces qui bloquent le trajet
    int rowDir = (rowSrc < rowDest) ? 1 : -1;
    int colDir = (colSrc < colDest) ? 1 : -1;
    int i = rowSrc + rowDir;
    int j = colSrc + colDir;
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
    if (isPieceAt(rowDest, colDest, pieces) == 1 && bishop.color() == Piece::Color::White)
    {
        return false;
    }
    else if (isPieceAt(rowDest, colDest, pieces) == 2 && bishop.color() == Piece::Color::Black)
    {
        return false;
    }

    // Si toutes les conditions sont remplies, le déplacement est valide
    return true;
};

bool King::validMove(std::vector<Piece> pieces, int rowDest, int colDest)
{
    int rowSrc = m_row;
    int colSrc = m_col;

    // verifier que source != destination
    if (rowSrc == rowDest && colSrc == colDest)
    {
        return false;
    }

    // Vérification que le roi se déplace d'une case maximum dans n'importe quelle direction
    if (abs(rowDest - rowSrc) > 1 || abs(colDest - colSrc) > 1)
    {
        return false;
    }

    // Vérification que le roi ne se déplace pas sur une case déjà occupée par une autre pièce de sa couleur
    if (isPieceAt(rowDest, colDest, pieces) == 1 && king.color() == Piece::Color::White)
    {
        return false;
    }
    else if (isPieceAt(rowDest, colDest, pieces) == 2 && king.color() == Piece::Color::Black)
    {
        return false;
    }

    // Si toutes les conditions sont remplies, le déplacement est valide
    return true;
};

bool Queen::validMove(std::vector<Piece> pieces, int rowDest, int colDest)
{
    int rowSrc = m_row;
    int colSrc = m_col;

    // verifier que source != destination
    if (rowSrc == rowDest && colSrc == colDest)
    {
        return false;
    }

    // Vérification que la reine se déplace en ligne droite ou en diagonale
    if (rowDest != rowSrc && colDest != colSrc && abs(rowDest - rowSrc) != abs(colDest - colSrc))
    {
        return false;
    }

    // Vérification qu'il n'y a pas d'obstacles sur la trajectoire de la reine
    int rowDirection = (rowDest > rowSrc) - (rowDest < rowSrc);
    int colDirection = (colDest > colSrc) - (colDest < colSrc);
    int r = rowSrc + rowDirection;
    int c = colSrc + colDirection;
    while (r != rowDest || c != colDest)
    {
        for (Piece piece : pieces)
        {
            if (piece.row() == r && piece.col() == c)
            {
                return false;
            }
        }
        r += rowDirection;
        c += colDirection;
    }

    // Vérification que le roi ne se déplace pas sur une case déjà occupée par une autre pièce de sa couleur
    if (isPieceAt(rowDest, colDest, pieces) == 1 && queen.color() == Piece::Color::White)
    {
        return false;
    }
    else if (isPieceAt(rowDest, colDest, pieces) == 2 && queen.color() == Piece::Color::Black)
    {
        return false;
    }

    // Si toutes les conditions sont remplies, le déplacement est valide
    return true;
};