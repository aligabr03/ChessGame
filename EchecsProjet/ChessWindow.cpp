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
            buttons[row][col] = button;
            button->setFixedSize(50, 50);
            if ((row + col) % 2 == 0) {
                button->setStyleSheet("background-color: rgb(220,220,220)");
            }
            else {
                button->setStyleSheet("background-color: green");
            }
            grid_layout->addWidget(button, row, col);
        }
    }
    setFixedSize(400, 400);
}

void ChessWindow::initializeBlackPieces() {
    QPixmap bishop("bishop1.png");
    QPixmap queen("queen1.png");
    QPixmap king("king1.png");
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0) {
                switch (col) {
                case 2:
                case 5:
                    addPiece(bishop, Piece::Color::Black, Piece::Type::Bishop, row, col);
                    break;
                case 3:
                    addPiece(queen, Piece::Color::Black, Piece::Type::Queen, row, col);
                    break;
                case 4:
                    addPiece(king, Piece::Color::Black, Piece::Type::King, row, col);
                    break;
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
                case 5:
                    addPiece(bishop, Piece::Color::Black, Piece::Type::Bishop, row, col);
                    break;
                case 3:
                    addPiece(queen, Piece::Color::Black, Piece::Type::Queen, row, col);
                    break;
                case 4:
                    addPiece(king, Piece::Color::Black, Piece::Type::King, row, col);
                    break;
                }
            }
        }
    }
}

void ChessWindow::addPiece(QPixmap icon, Piece::Color color, Piece::Type type, int row, int col) {
    Piece piece(color, type, row, col);
    buttons[row][col]->setIcon(icon);
    pieces.push_back(piece);
}
