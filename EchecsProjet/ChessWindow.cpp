#include "ChessWindow.h"

ChessWindow::ChessWindow() {
    initializeBoard();
    initializeWhitePieces();
    initializeBlackPieces();
    qDebug() << "ChessWindow Constructor Called\n";
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
    QPixmap bishopb("bishop1.png");
    QPixmap queenb("queen1.png");
    QPixmap kingb("king1.png");
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0) {
                switch (col) {
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
                    addPiece(bishop, Piece::Color::White, Piece::Type::Bishop, row, col);
                    break;
                case 3:
                    addPiece(queen, Piece::Color::White, Piece::Type::Queen, row, col);
                    break;
                case 4:
                    addPiece(king, Piece::Color::White, Piece::Type::King, row, col);
                    break;
                }
            }
        }
    }
}

void ChessWindow::addPiece(QPixmap icon, Piece::Color color, Piece::Type type, int row, int col) {
    Piece piece(icon, color, type, row, col);
    buttons[row][col]->setIcon(icon);
    pieces.push_back(piece);
}

void ChessWindow::movePiece(){
    selectedButton->setIcon(selectedPiece->icon());
    
}

void ChessWindow::pieceClick() {
    qDebug() << "pieceClick Called\n";
    int row, col;
    int rowSpan, colSpan;
    Controller controller;
    QPushButton* previousButton;

    previousButton = selectedButton;
    selectedButton = qobject_cast<QPushButton*>(sender());

    QGridLayout* grid_layout = qobject_cast<QGridLayout*>(selectedButton->parentWidget()->layout());
    grid_layout->getItemPosition(grid_layout->indexOf(selectedButton), &row, &col, &rowSpan, &colSpan);

    if (isPieceSelected == false) {
        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i].row() == row && pieces[i].col() == col) {
                selectedPiece = &pieces[i];
            }
        }
        originalStyle = selectedButton->styleSheet();
        isPieceSelected = controller.checkTurn(whiteTurn, selectedPiece, selectedButton);

    } else if (isPieceSelected == true) {
        if (controller.validMove((*selectedPiece), pieces, row, col)) {
            selectedButton->setIcon(selectedPiece->icon());
            selectedPiece->setCol(col);
            selectedPiece->setRow(row);
            isPieceSelected = false;
            previousButton->setStyleSheet(originalStyle);
        }
    }
    qDebug() << isPieceSelected;

}