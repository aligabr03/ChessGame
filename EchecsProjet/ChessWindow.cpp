/*
Nom: ChessWindow.cpp
Description: Gere la vue du jeu et implemente les fonctions definit dans la classe ChessWindows.h
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 14 Avril 2023
*/

#include "ChessWindow.h"

ChessWindow::ChessWindow() {
    initializeBoard();
    initializeWhitePieces();
    initializeBlackPieces();
}

void ChessWindow::initializeBoard() {
    QWidget* central_widget = new QWidget();
    setCentralWidget(central_widget);

    QGridLayout* grid_layout = new QGridLayout(central_widget);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QPushButton* button = new QPushButton();
            connect(button, &QPushButton::clicked, this, &ChessWindow::pieceClick);
            buttons[row][col] = button;
            button->setFixedSize(75, 75);
            if ((row + col) % 2 == 0) {
                button->setStyleSheet("background-color: #769656");
            }
            else {
                button->setStyleSheet("background-color: #eeeed2");
            }
            grid_layout->addWidget(button, row, col);
        }
    }
    setFixedSize(600, 600);
}

void ChessWindow::initializeBlackPieces() {
    QPixmap bishopb("bishop1.png");
    QPixmap queenb("queen1.png");
    QPixmap kingb("king1.png");
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0) {
                switch (col) {
                case 2:
                case 5: {
                    buttons[row][col]->setIcon(bishopb);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<Bishop>(bishopb, Piece::Black, row, col));
                    break;
                }
                case 3: {
                    buttons[row][col]->setIcon(queenb);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<Queen>(queenb, Piece::Black, row, col));
                    break;
                }
                case 4: {
                    buttons[row][col]->setIcon(kingb);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<King>(kingb, Piece::Black, row, col));
                    break;
                }
                }
            }
        }
    }
}

void ChessWindow::initializeWhitePieces() {
    QPixmap bishop("bishop.png");
    QPixmap queen("queen.png");
    QPixmap king("king.png");
    for (int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 7) {
                switch (col) {
                case 2:
                case 5: {
                    buttons[row][col]->setIcon(bishop);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<Bishop>(bishop, Piece::White, row, col));
                    break;
                }
                case 3: {
                    buttons[row][col]->setIcon(queen);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<Queen>(queen, Piece::White, row, col));
                    break;
                }
                case 4: {
                    buttons[row][col]->setIcon(king);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<King>(king, Piece::White, row, col));
                    break;
                }
                }
            }
        }
    }
}

void ChessWindow::movePiece(int row, int col){
    selectedButton->setIcon(selectedPiece->icon());
    selectedButton->setIconSize(QSize(45, 45));
    selectedPiece->setCol(col);
    selectedPiece->setRow(row);
    lastValidButton->setIcon(QIcon());
    whiteTurn = !whiteTurn;
}

void ChessWindow::selectPiece(int row, int col) {
    for (auto it = pieces.begin(); it != pieces.end(); it++) {
        if ((*it)->row() == row && (*it)->col() == col) {
            selectedPiece = *it;
            isPieceSelected = checkTurn(whiteTurn, selectedPiece, selectedButton);
            lastValidButton = selectedButton;
            break;
        }
    }
}

bool ChessWindow::checkTurn(bool whiteTurn, std::shared_ptr<Piece> selectedPiece, QPushButton* selectedButton) {
    if (selectedPiece->row() != 99 && whiteTurn == true && selectedPiece->color() == Piece::White) {
        selectedButton->setStyleSheet("background-color: rgb(200,200,100)");
        return true;
    }
    else if (selectedPiece->row() != 99 && whiteTurn == false && selectedPiece->color() == Piece::Black) {
        selectedButton->setStyleSheet("background-color: rgb(200,200,100)");
        return true;
    }
    return false;
}

void ChessWindow::highlightValidByTurn(std::shared_ptr<Piece> piece, QGridLayout* gridLayout) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (piece->validMove(pieces, row, col)) {
                QLayoutItem* item = gridLayout->itemAtPosition(row, col);
                if (item != nullptr) {
                    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                    button->setStyleSheet("background-color: rgb(200,200,100)");
                }
            }
        }
    }
}

void ChessWindow::highlightValid(std::shared_ptr<Piece> piece, QGridLayout* gridLayout) {
    if (selectedPiece != nullptr) {
        if (selectedPiece->row() != 99 && whiteTurn == true && selectedPiece->color() == Piece::White) {
            highlightValidByTurn(piece, gridLayout);
        }
        else if (selectedPiece->row() != 99 && whiteTurn == false && selectedPiece->color() == Piece::Black) {
            highlightValidByTurn(piece, gridLayout);
        }
    }
}

void ChessWindow::resetColors(QGridLayout* gridLayout) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QLayoutItem* item = gridLayout->itemAtPosition(row, col);
            if (item != nullptr) {
                QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                if ((row + col) % 2 == 0) {
                    button->setStyleSheet("background-color: #769656");
                }
                else {
                    button->setStyleSheet("background-color: #eeeed2");
                }
            }
        }
    }
}

void ChessWindow::capture(int row, int col) {
    if (selectedPiece->isPieceAt(row, col, pieces) != 0) {
        for (auto it = pieces.begin(); it != pieces.end(); it++) {
            if ((*it)->row() == row && (*it)->col() == col) {
                pieces.erase(it); 
                break;
            }
        }
    }
}

void ChessWindow::pieceClick() {
    int row, col;
    int rowSpan, colSpan;

    selectedButton = qobject_cast<QPushButton*>(sender());
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(selectedButton->parentWidget()->layout());
    gridLayout->getItemPosition(gridLayout->indexOf(selectedButton), &row, &col, &rowSpan, &colSpan);

    if (isPieceSelected == false)
    {
        selectPiece(row, col);
        highlightValid(selectedPiece, gridLayout);
    }
    else if (isPieceSelected == true)
    {
        if (selectedPiece->validMove(pieces, row, col)) {
            capture(row, col);
            movePiece(row, col);
            resetColors(gridLayout);
            isPieceSelected = false;
        }
        else {
            selectedButton->setStyleSheet("background-color: red");
        }
    }
}