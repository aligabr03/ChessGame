#include "ChessWindow.h"

ChessWindow::ChessWindow() {
    Controller controller;
    initializeBoard(controller);
    initializeWhitePieces(controller);
    initializeBlackPieces(controller);
    qDebug() << "ChessWindow Constructor Called\n";
}

void ChessWindow::initializeBoard(Controller& controller) {
    QWidget* central_widget = new QWidget();
    setCentralWidget(central_widget);

    QGridLayout* grid_layout = new QGridLayout(central_widget);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QPushButton* button = new QPushButton();
            connect(button, &QPushButton::clicked, this, &ChessWindow::pieceClick);
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

void ChessWindow::initializeBlackPieces(Controller& controller) {
    QPixmap bishop("bishop1.png");
    QPixmap queen("queen1.png");
    QPixmap king("king1.png");
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0) {
                switch (col) {
                case 2:
                case 5:
                    addPiece(controller, bishop, Piece::Color::Black, Piece::Type::Bishop, row, col);
                    break;
                case 3:
                    addPiece(controller, queen, Piece::Color::Black, Piece::Type::Queen, row, col);
                    break;
                case 4:
                    addPiece(controller, king, Piece::Color::Black, Piece::Type::King, row, col);
                    break;
                }
            }
        }
    }
}

void ChessWindow::initializeWhitePieces(Controller& controller) {
    QPixmap bishop("bishop.png");
    QPixmap queen("queen.png");
    QPixmap king("king.png");
    for (int row = 6; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 7) {
                switch (col) {
                case 2:
                case 5:
                    addPiece(controller, bishop, Piece::Color::White, Piece::Type::Bishop, row, col);
                    break;
                case 3:
                    addPiece(controller, queen, Piece::Color::White, Piece::Type::Queen, row, col);
                    break;
                case 4:
                    addPiece(controller, king, Piece::Color::White, Piece::Type::King, row, col);
                    break;
                }
            }
        }
    }
}

void ChessWindow::addPiece(Controller& controller, QPixmap icon, Piece::Color color, Piece::Type type, int row, int col) {
    Piece piece(color, type, row, col);
    buttons[row][col]->setIcon(icon);
    pieces.push_back(piece);
}


void ChessWindow::pieceClick() {
    qDebug() << "pieceClick Called\n";
    selectedButton = qobject_cast<QPushButton*>(sender());
    int row, col;
    if (pieceSelected == false) {
        int rowSpan, colSpan;
        QGridLayout* grid_layout = qobject_cast<QGridLayout*>(selectedButton->parentWidget()->layout());
        grid_layout->getItemPosition(grid_layout->indexOf(selectedButton), &row, &col, &rowSpan, &colSpan);

        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i].row() == row && pieces[i].col() == col) {
                selectedPiece = pieces[i];
            }
        }

        if (selectedPiece.row() != 99 && whiteTurn == true && selectedPiece.color() == Piece::White) {
            pieceSelected = true;
            selectedButton->setStyleSheet("background-color: yellow");
        } else if (selectedPiece.row() != 99 && whiteTurn == false && selectedPiece.color() == Piece::Black) {
            pieceSelected = true;
            selectedButton->setStyleSheet("background-color: yellow");
            qDebug() << "bl";

        }

    } else {

    }
}