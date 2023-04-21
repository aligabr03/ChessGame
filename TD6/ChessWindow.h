/*
Nom: ChessWindow.h
Description: Gere la vue du jeu
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <qmainwindow.h>
#include <qgridlayout.h>
#include <qpushbutton.h>

#include "MoveGuard.h"

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
        bool isChecked();
        bool checkTurn();

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

#endif