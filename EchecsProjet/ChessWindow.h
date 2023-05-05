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
#include <qmenu.h>
#include <qaction.h>
#include <QInputDialog>

#include "MoveGuard.h"

namespace view
{
    class ChessWindow : public QMainWindow
    {
    public:
        ChessWindow();
        void initializeWhitePieces();
        void initializeBlackPieces();
        void chooseStartPositionWhitePieces();
        void chooseStartPositionBlackPieces();
        void initializeBoard();

        void clearBoard();
        void startNormal();
        void startKingOnly();
        void chooseStartingPositions();

        void movePiece(int row, int col);
        void selectPiece(int row, int col);
        void capture(int row, int col);

        void highlightValid(std::shared_ptr<model::Piece> piece, QGridLayout *gridLayout);
        void highlightValidByTurn(std::shared_ptr<model::Piece> piece, QGridLayout *gridLayout);
        void resetColors(QGridLayout *gridLayout);
        bool isChecked();
        bool checkTurn();

    private slots:
        void pieceClick();

    private:
        static const int CHESSBOARD_SIZE_ = 8;
        QPushButton *buttons[CHESSBOARD_SIZE_][CHESSBOARD_SIZE_];
        std::list<std::shared_ptr<model::Piece>> pieces_;

        QPushButton *selectedButton_ = nullptr;
        QPushButton *lastValidButton_ = nullptr;
        std::shared_ptr<model::Piece> selectedPiece_ = nullptr;

        bool isPieceSelected_ = false;
        bool whiteTurn_ = true;
    };
}

#endif