/*
Nom: ChessWindow.h
Description: Gere la vue du jeu
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 14 Avril 2023
*/

#include <qmainwindow.h>
#include <qgridlayout.h>
#include <qpushbutton.h>

#include "Piece.h"

namespace view
{
    class ChessWindow : public QMainWindow {
    public:
        ChessWindow();
        void initializeWhitePieces();
        void initializeBlackPieces();
        void initializeBoard();

        void movePiece(int row, int col);
        void selectPiece(int row, int col);
        void capture(int row, int col);

        void highlightValid(std::shared_ptr<model::Piece> piece, QGridLayout* gridLayout);
        void highlightValidByTurn(std::shared_ptr<model::Piece> piece, QGridLayout* gridLayout);
        void resetColors(QGridLayout* gridLayout);
        bool checkTurn();
        int isChecked();

        std::list<std::shared_ptr<model::Piece>> getPieces() { return pieces; }
        bool getTurn() { return whiteTurn; }

    private slots:
        void pieceClick();

    private:
        QPushButton* buttons[8][8];
        std::list<std::shared_ptr<model::Piece>> pieces;

        QPushButton* selectedButton = nullptr;
        QPushButton* lastValidButton = nullptr;
        std::shared_ptr<model::Piece> selectedPiece = nullptr;

        bool isPieceSelected = false;
        bool whiteTurn = true;
    };
}
