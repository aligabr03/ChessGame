#include <qobject.h>

#include "Piece.h"

class Controller : public QObject {
Q_OBJECT
public:
    Controller(){}

    bool validMove(Piece piece, std::vector<Piece> pieces, int rowDest, int colDest);
    bool validMoveBishop(Piece bishop, std::vector<Piece> pieces, int rowDest, int colDest);
    bool validMoveKing(Piece king, std::vector<Piece> pieces, int rowDest, int colDest);
    bool validMoveQueen(Piece queen, std::vector<Piece> pieces, int rowDest, int colDest);

    bool checkTurn(bool whiteTurn, Piece* selectedPiece, QPushButton* selectedButton);

    int isPieceAt(int row, int col, std::vector<Piece> pieces);
};