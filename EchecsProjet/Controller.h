
#include "Piece.h"

class Controller {


    bool validMoveBishop(Piece bishop, std::vector<Piece> pieces, int rowDest, int colDest);
    bool validMoveKing(Piece king, std::vector<Piece> pieces, int rowDest, int colDest);
    bool validMoveQueen(Piece queen, std::vector<Piece> pieces, int rowDest, int colDest);

    int isPieceAt(int row, int col, std::vector<Piece> pieces); //Retourne 0 pour aucune piece, 1 pour blanc, 2 pour noire
private:
	Piece selected;

};