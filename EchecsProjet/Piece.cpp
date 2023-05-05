/*
Nom: Piece.cpp
Description: Definit les methodes des classes derivees de Piece
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 5 Mai 2023
*/

#include "Piece.h"

namespace model
{
    int King::s_kingCount = 0;

    int Piece::isPieceAt(int row, int col, std::list<std::shared_ptr<Piece>> pieces)
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

    bool King::validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest)
    {

        // verifier que source != destination
        if (row_ == rowDest && col_ == colDest)
        {
            return false;
        }

        // Verification que le roi se deplace d'une case maximum dans n'importe quelle direction
        if (abs(rowDest - row_) > 1 || abs(colDest - col_) > 1)
        {
            return false;
        }

        // Verification que le roi ne se deplace pas sur une case deja occupee par une autre piece de sa couleur
        if (isPieceAt(rowDest, colDest, pieces) == 1 && color_ == Piece::Color::White)
        {
            return false;
        }
        else if (isPieceAt(rowDest, colDest, pieces) == 2 && color_ == Piece::Color::Black)
        {
            return false;
        }

        // Verification que le mouvement ne mettrai pas le roi en echec
        //for (const std::shared_ptr<Piece> piece : pieces)
        //{
        //    if (piece->color() != color_)
        //    {
        //        if (piece->validMove(pieces, rowDest, colDest)) // si le roi met le roi en echec King::validMove s'appelle lui meme -> crash quand 2 rois s'approchent
        //        {
        //            return false;
        //        }
        //    }
        //}

        // Si toutes les conditions sont remplies, le deplacement est valide
        return true;
    }

    bool Queen::validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest)
    {

        // verifier que source != destination
        if (row_ == rowDest && col_ == colDest)
        {
            return false;
        }

        // Verification que la reine se deplace en ligne droite ou en diagonale
        if (rowDest != row_ && colDest != col_ && abs(rowDest - row_) != abs(colDest - col_))
        {
            return false;
        }

        // Verification qu'il n'y a pas d'obstacles sur la trajectoire de la reine
        int rowDirection = (rowDest > row_) - (rowDest < row_);
        int colDirection = (colDest > col_) - (colDest < col_);
        int r = row_ + rowDirection;
        int c = col_ + colDirection;
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

        // Verification que la reine ne se deplace pas sur une case deja occupee par une autre piece de sa couleur
        if (isPieceAt(rowDest, colDest, pieces) == 1 && color_ == Piece::Color::White)
        {
            return false;
        }
        else if (isPieceAt(rowDest, colDest, pieces) == 2 && color_ == Piece::Color::Black)
        {
            return false;
        }

        // Si toutes les conditions sont remplies, le deplacement est valide
        return true;
    }

    bool Bishop::validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest)
    {

        // verifier que source != destination
        if (row_ == rowDest && col_ == colDest)
        {
            return false;
        }

        // verifier que le mouvement est bien diagonal
        int rowDiff = std::abs(row_ - rowDest);
        int colDiff = std::abs(col_ - colDest);
        if (rowDiff != colDiff)
        {
            return false;
        }

        // verifier qu'il n'y a pas de pieces qui bloquent le trajet
        int rowDir = (row_ < rowDest) ? 1 : -1;
        int colDir = (col_ < colDest) ? 1 : -1;
        int i = row_ + rowDir;
        int j = col_ + colDir;
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
        if (isPieceAt(rowDest, colDest, pieces) == 1 && color_ == Piece::Color::White)
        {
            return false;
        }
        else if (isPieceAt(rowDest, colDest, pieces) == 2 && color_ == Piece::Color::Black)
        {
            return false;
        }

        return true;
    }
}