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
                button->setStyleSheet("background-color: rgb(50,50,50)");
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

void ChessWindow::movePiece(int row, int col){
    selectedButton->setIcon(selectedPiece->icon());
    selectedPiece->setCol(col);
    selectedPiece->setRow(row);
    isPieceSelected = false;
    lastValidButton->setIcon(QIcon());
    whiteTurn = !whiteTurn;

    qDebug() << whiteTurn;

    for (auto i : pieces) {
        qDebug() << i.type() << i.color() << "ligne:" << i.row() << "colonne:" << i.col() << "\n";
    }
}

void ChessWindow::selectPiece(int row, int col) {
    Controller controller;
    for (auto it = pieces.begin(); it != pieces.end(); it++) {
        if ((*it).row() == row && (*it).col() == col) {
            selectedPiece = &(*it);
            isPieceSelected = controller.checkTurn(whiteTurn, selectedPiece, selectedButton);
            lastValidButton = selectedButton;
            break;
        }
    }
}

void ChessWindow::highlightValidByTurn(Piece* piece, QGridLayout* gridLayout) {
    Controller controller;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (controller.validMove(piece, pieces, row, col)) {
                QLayoutItem* item = gridLayout->itemAtPosition(row, col);
                if (item != nullptr) {
                    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                    button->setStyleSheet("background-color: rgb(100,200,200)");
                }
            }
        }
    }
}

void ChessWindow::highlightValid(Piece* piece, QGridLayout* gridLayout) {
    Controller controller;
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
                    button->setStyleSheet("background-color: rgb(220,220,220)");
                }
                else {
                    button->setStyleSheet("background-color: rgb(50,50,50)");
                }
            }
        }
    }
}

void ChessWindow::capture(int row, int col) {
    Controller controller;
    if (controller.isPieceAt(row, col, pieces) != 0) {
        for (auto it = pieces.begin(); it != pieces.end(); it++) {
            if ((*it).row() == row && (*it).col() == col) {
                pieces.erase(it); 
                break;
            }
        }
    }
}

void ChessWindow::pieceClick() {
    int row, col;
    int rowSpan, colSpan;
    Controller controller;

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
        if (controller.validMove(selectedPiece, pieces, row, col)) {
            capture(row, col);
            movePiece(row, col);
            resetColors(gridLayout);
        }
        else {
            selectedButton->setStyleSheet("background-color: red");
        }
    }
}