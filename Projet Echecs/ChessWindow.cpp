#include "ChessWindow.hpp"

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

void ChessWindow::initializeWhitePieces() {
    QPixmap rookw("rook.png");
    QPixmap knightw("knight.png");
    QPixmap bishopw("bishop.png");
    QPixmap queenw("queen.png");
    QPixmap kingw("king.png");
    QPixmap pawnw("pawn.png");
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0) {
                switch(col) {
                    case 0:
                    case 7:
                        addPiece(rookw, Piece::Color::White, Piece::Type::Rook, row, col);
                        break;
                    case 1:
                    case 6:
                        addPiece(knightw, Piece::Color::White, Piece::Type::Knight, row, col);
                        break;
                    case 2:
                    case 5:
                        addPiece(bishopw, Piece::Color::White, Piece::Type::Bishop, row, col);
                        break;
                    case 3:
                        addPiece(queenw, Piece::Color::White, Piece::Type::Queen, row, col);
                        break;
                    case 4:
                        addPiece(kingw, Piece::Color::White, Piece::Type::King, row, col);
                        break;
                }
            } else {
                addPiece(pawnw, Piece::Color::White, Piece::Type::Pawn, row, col);
            }
        }
    }
}

void ChessWindow::initializeBlackPieces() {
    QPixmap rookb("rook1.png");
    QPixmap knightb("knight1.png");
    QPixmap bishopb("bishop1.png");
    QPixmap queenb("queen1.png");
    QPixmap kingb("king1.png");
    QPixmap pawnb("pawn1.png");
    for (int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 7) {
                switch (col) {
                case 0:
                case 7:
                    addPiece(rookb, Piece::Color::Black, Piece::Type::Rook, row, col);
                    break;
                case 1:
                case 6:
                    addPiece(knightb, Piece::Color::Black, Piece::Type::Knight, row, col);
                    break;
                case 2:
                case 5:
                    addPiece(bishopb, Piece::Color::Black, Piece::Type::Bishop, row, col);
                    break;
                case 3:
                    addPiece(queenb, Piece::Color::Black, Piece::Type::Queen, row, col);
                    break;
                case 4:
                    addPiece(kingb, Piece::Color::Black, Piece::Type::King, row, col);
                    break;
                }
            }
            else {
                addPiece(pawnb, Piece::Color::Black, Piece::Type::Pawn, row, col);
            }
        }
    }
}

void ChessWindow::addPiece(QPixmap icon,Piece::Color color, Piece::Type type, int row, int col) {
    Piece piece(color, type, row, col);
    buttons[row][col]->setIcon(icon);
    pieces.push_back(piece);
}