#include "Controller.h"

bool Controller::validMoveBishop(Piece bishop, std::vector<Piece> pieces, int rowDest, int colDest) {
    int rowSrc = bishop.row();
    int colSrc = bishop.col();

    if (rowSrc == rowDest && colSrc == colDest) {
        return false;
    }

    int rowDiff = std::abs(rowSrc - rowDest);
    int colDiff = std::abs(colSrc - colDest);
    if (rowDiff != colDiff) {
        return false;
    }

    int rowDir = (rowSrc < rowDest) ? 1 : -1;
    int colDir = (colSrc < colDest) ? 1 : -1;
    int i = rowSrc + rowDir;
    int j = colSrc + colDir;
    while (i != rowDest && j != colDest) {
        if (isPieceAt(i, j, pieces) != 0) {
            return false;
        }
        i += rowDir;
        j += colDir;
    }

    if (isPieceAt(rowDest, colDest, pieces) == 1 && bishop.color() == Piece::Color::White) {
        return false;
    } else if (isPieceAt(rowDest, colDest, pieces) == 2 && bishop.color() == Piece::Color::Black) {
        return false;
    }

    return true;
}

bool Controller::validMoveKing(Piece king, std::vector<Piece> pieces, int rowDest, int colDest) {
    return false;
}

bool Controller::validMoveQueen(Piece queen, std::vector<Piece> pieces, int rowDest, int colDest) {
    return false;
}

int Controller::isPieceAt(int row, int col, std::vector<Piece> pieces) {
    for (Piece& piece : pieces) {
        if (piece.row() == row && piece.col() == col) {
            if (piece.color() == Piece::Color::White) {
                return 1;
            }
            else {
                return 2;
            }
        }
    }
    return 0;
}