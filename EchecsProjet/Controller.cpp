#include "Controller.h"

// bool Controller::validMove(Piece piece, std::vector<Piece> pieces, int rowDest, int colDest)
// {

//     switch (piece.type())
//     {
//     case Piece::King:
//         return validMoveKing(piece, pieces, rowDest, colDest);
//         break;
//     case Piece::Queen:
//         return validMoveQueen(piece, pieces, rowDest, colDest);
//         break;
//     case Piece::Bishop:
//         return validMoveBishop(piece, pieces, rowDest, colDest);
//         break;
//     }
// }

// bool Controller::validMoveBishop(Piece bishop, std::vector<Piece> pieces, int rowDest, int colDest)
// {
//     int rowSrc = bishop.row();
//     int colSrc = bishop.col();

//     // verifier que source != destination
//     if (rowSrc == rowDest && colSrc == colDest)
//     {
//         return false;
//     }

//     // verifier que le mouvement est bien diagonal
//     int rowDiff = std::abs(rowSrc - rowDest);
//     int colDiff = std::abs(colSrc - colDest);
//     if (rowDiff != colDiff)
//     {
//         return false;
//     }

//     // verifier qu'il n'y a pas de pieces qui bloquent le trajet
//     int rowDir = (rowSrc < rowDest) ? 1 : -1;
//     int colDir = (colSrc < colDest) ? 1 : -1;
//     int i = rowSrc + rowDir;
//     int j = colSrc + colDir;
//     while (i != rowDest && j != colDest)
//     {
//         if (isPieceAt(i, j, pieces) != 0)
//         {
//             return false;
//         }
//         i += rowDir;
//         j += colDir;
//     }

//     // verifier qu'il n'y a pas de piece de la meme couleur a la destination
//     if (isPieceAt(rowDest, colDest, pieces) == 1 && bishop.color() == Piece::Color::White)
//     {
//         return false;
//     }
//     else if (isPieceAt(rowDest, colDest, pieces) == 2 && bishop.color() == Piece::Color::Black)
//     {
//         return false;
//     }

//     // Si toutes les conditions sont remplies, le déplacement est valide
//     return true;
// }

// bool Controller::validMoveKing(Piece king, std::vector<Piece> pieces, int rowDest, int colDest)
// {
//     int rowSrc = king.row();
//     int colSrc = king.col();

//     // verifier que source != destination
//     if (rowSrc == rowDest && colSrc == colDest)
//     {
//         return false;
//     }

//     // Vérification que le roi se déplace d'une case maximum dans n'importe quelle direction
//     if (abs(rowDest - rowSrc) > 1 || abs(colDest - colSrc) > 1)
//     {
//         return false;
//     }

//     // Vérification que le roi ne se déplace pas sur une case déjà occupée par une autre pièce de sa couleur
//     if (isPieceAt(rowDest, colDest, pieces) == 1 && king.color() == Piece::Color::White)
//     {
//         return false;
//     }
//     else if (isPieceAt(rowDest, colDest, pieces) == 2 && king.color() == Piece::Color::Black)
//     {
//         return false;
//     }

//     // Si toutes les conditions sont remplies, le déplacement est valide
//     return true;
// }

// bool Controller::validMoveQueen(Piece queen, std::vector<Piece> pieces, int rowDest, int colDest)
// {
//     int rowSrc = queen.row();
//     int colSrc = queen.col();

//     // verifier que source != destination
//     if (rowSrc == rowDest && colSrc == colDest)
//     {
//         return false;
//     }

//     // Vérification que la reine se déplace en ligne droite ou en diagonale
//     if (rowDest != rowSrc && colDest != colSrc && abs(rowDest - rowSrc) != abs(colDest - colSrc))
//     {
//         return false;
//     }

//     // Vérification qu'il n'y a pas d'obstacles sur la trajectoire de la reine
//     int rowDirection = (rowDest > rowSrc) - (rowDest < rowSrc);
//     int colDirection = (colDest > colSrc) - (colDest < colSrc);
//     int r = rowSrc + rowDirection;
//     int c = colSrc + colDirection;
//     while (r != rowDest || c != colDest)
//     {
//         for (Piece piece : pieces)
//         {
//             if (piece.row() == r && piece.col() == c)
//             {
//                 return false;
//             }
//         }
//         r += rowDirection;
//         c += colDirection;
//     }

//     // Vérification que le roi ne se déplace pas sur une case déjà occupée par une autre pièce de sa couleur
//     if (isPieceAt(rowDest, colDest, pieces) == 1 && queen.color() == Piece::Color::White)
//     {
//         return false;
//     }
//     else if (isPieceAt(rowDest, colDest, pieces) == 2 && queen.color() == Piece::Color::Black)
//     {
//         return false;
//     }

//     // Si toutes les conditions sont remplies, le déplacement est valide
//     return true;
// }

// retourne 0 pour aucune piece, 1 pour blanc, 2 pour noire
int Controller::isPieceAt(int row, int col, std::vector<Piece> pieces)
{
    for (Piece &piece : pieces)
    {
        if (piece.row() == row && piece.col() == col)
        {
            if (piece.color() == Piece::Color::White)
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

// verifie que la piece jouee correspond a la bonne couleur, si oui, colorie la case en jaune pour indiquer la selection
bool Controller::checkTurn(bool whiteTurn, Piece *selectedPiece, QPushButton *selectedButton)
{
    if (selectedPiece->row() != 99 && whiteTurn == true && selectedPiece->color() == Piece::White)
    {
        selectedButton->setStyleSheet("background-color: yellow");
        return true;
    }
    else if (selectedPiece->row() != 99 && whiteTurn == false && selectedPiece->color() == Piece::Black)
    {
        selectedButton->setStyleSheet("background-color: yellow");
        return true;
    }
    return false;
}