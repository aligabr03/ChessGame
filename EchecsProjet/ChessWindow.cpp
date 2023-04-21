/*
Nom: ChessWindow.cpp
Description: Gere la vue du jeu et implemente les methodes definies dans la classe ChessWindow.h
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 14 Avril 2023
*/

#include "ChessWindow.h"

view::ChessWindow::ChessWindow()
{
    initializeBoard();
    initializeWhitePieces();
    initializeBlackPieces();
}

void view::ChessWindow::initializeBoard()
{
    QWidget *central_widget = new QWidget();
    setCentralWidget(central_widget);

    QGridLayout *grid_layout = new QGridLayout(central_widget);

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QPushButton *button = new QPushButton();
            connect(button, &QPushButton::clicked, this, &ChessWindow::pieceClick);
            buttons[row][col] = button;
            button->setFixedSize(75, 75);
            if ((row + col) % 2 == 0)
            {
                button->setStyleSheet("background-color: #769656");
            }
            else
            {
                button->setStyleSheet("background-color: #eeeed2");
            }
            grid_layout->addWidget(button, row, col);
        }
    }
    setFixedSize(600, 600);
}

void view::ChessWindow::initializeBlackPieces()
{
    QPixmap bishopb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/bishop1.png");
    QPixmap queenb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/queen1.png");
    QPixmap kingb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/king1.png");
    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (row == 0)
            {
                switch (col)
                {
                case 2:
                case 5:
                {
                    buttons[row][col]->setIcon(bishopb);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<model::Bishop>(bishopb, model::Piece::Black, row, col));
                    break;
                }
                case 3:
                {
                    buttons[row][col]->setIcon(queenb);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<model::Queen>(queenb, model::Piece::Black, row, col));
                    break;
                }
                case 4:
                {
                    buttons[row][col]->setIcon(kingb);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<model::King>(kingb, model::Piece::Black, row, col));
                    break;
                }
                }
            }
        }
    }
}

void view::ChessWindow::initializeWhitePieces()
{
    QPixmap bishop("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/bishop.png");
    QPixmap queen("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/queen.png");
    QPixmap king("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/king.png");
    for (int row = 6; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (row == 7)
            {
                switch (col)
                {
                case 2:
                case 5:
                {
                    buttons[row][col]->setIcon(bishop);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<model::Bishop>(bishop, model::Piece::White, row, col));
                    break;
                }
                case 3:
                {
                    buttons[row][col]->setIcon(queen);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<model::Queen>(queen, model::Piece::White, row, col));
                    break;
                }
                case 4:
                {
                    buttons[row][col]->setIcon(king);
                    buttons[row][col]->setIconSize(QSize(45, 45));
                    pieces.push_back(std::make_shared<model::King>(king, model::Piece::White, row, col));
                    break;
                }
                }
            }
        }
    }
}

void view::ChessWindow::movePiece(int row, int col)
{
    bool *undo;
    MoveGuard guard(selectedButton, lastValidButton, selectedPiece, row, col, undo);
    if (isChecked())
    {
        *undo = true;
    }
    else
    {
        *undo = false;
        whiteTurn = !whiteTurn;
    }
    // selectedButton->setIcon(selectedPiece->icon());
    // selectedButton->setIconSize(QSize(45, 45));
    // selectedPiece->setCol(col);
    // selectedPiece->setRow(row);
    // lastValidButton->setIcon(QIcon());
}

void view::ChessWindow::selectPiece(int row, int col)
{
    for (auto it = pieces.begin(); it != pieces.end(); it++)
    {
        if ((*it)->row() == row && (*it)->col() == col)
        {
            selectedPiece = *it;
            isPieceSelected = checkTurn();
            lastValidButton = selectedButton;
            break;
        }
    }
}

bool view::ChessWindow::isChecked()
{
    for (std::shared_ptr<model::Piece> king : pieces)
    {
        if (king->type() == model::Piece::King)
        {
            for (std::shared_ptr<model::Piece> piece : pieces)
            {
                if (piece->type() != model::Piece::King)
                {
                    if (piece->color() == model::Piece::Black && whiteTurn && king->color() == model::Piece::White)
                    {
                        if (piece->validMove(pieces, king->row(), king->col()))
                        {
                            return true;
                        }
                    }
                    else if (piece->color() == model::Piece::White && !whiteTurn && king->color() == model::Piece::Black)
                    {
                        if (piece->validMove(pieces, king->row(), king->col()))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool view::ChessWindow::checkTurn()
{
    if (selectedPiece->row() != 99 && whiteTurn && selectedPiece->color() == model::Piece::White)
    {
        selectedButton->setStyleSheet("background-color: rgb(233,233,108)");
        return true;
    }
    else if (selectedPiece->row() != 99 && !whiteTurn && selectedPiece->color() == model::Piece::Black)
    {
        selectedButton->setStyleSheet("background-color: rgb(233,233,108)");
        return true;
    }
    return false;
}

void view::ChessWindow::highlightValidByTurn(std::shared_ptr<model::Piece> piece, QGridLayout *gridLayout)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (piece->validMove(pieces, row, col))
            {
                QLayoutItem *item = gridLayout->itemAtPosition(row, col);
                if (item != nullptr)
                {
                    QPushButton *button = qobject_cast<QPushButton *>(item->widget());
                    button->setStyleSheet("background-color: rgb(233,233,108)");
                }
            }
        }
    }
}

void view::ChessWindow::highlightValid(std::shared_ptr<model::Piece> piece, QGridLayout *gridLayout)
{
    if (selectedPiece != nullptr)
    {
        if (selectedPiece->row() != 99 && whiteTurn == true && selectedPiece->color() == model::Piece::White)
        {
            highlightValidByTurn(piece, gridLayout);
        }
        else if (selectedPiece->row() != 99 && whiteTurn == false && selectedPiece->color() == model::Piece::Black)
        {
            highlightValidByTurn(piece, gridLayout);
        }
    }
}

void view::ChessWindow::resetColors(QGridLayout *gridLayout)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QLayoutItem *item = gridLayout->itemAtPosition(row, col);
            if (item != nullptr)
            {
                QPushButton *button = qobject_cast<QPushButton *>(item->widget());
                if ((row + col) % 2 == 0)
                {
                    button->setStyleSheet("background-color: #769656");
                }
                else
                {
                    button->setStyleSheet("background-color: #eeeed2");
                }
            }
        }
    }
}

void view::ChessWindow::capture(int row, int col)
{
    if (selectedPiece->isPieceAt(row, col, pieces) != 0)
    {
        for (auto it = pieces.begin(); it != pieces.end(); it++)
        {
            if ((*it)->row() == row && (*it)->col() == col)
            {
                pieces.erase(it);
                break;
            }
        }
    }
}

void view::ChessWindow::pieceClick()
{
    int row, col;
    int rowSpan, colSpan;

    selectedButton = qobject_cast<QPushButton *>(sender());
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(selectedButton->parentWidget()->layout());
    gridLayout->getItemPosition(gridLayout->indexOf(selectedButton), &row, &col, &rowSpan, &colSpan);

    if (isPieceSelected == false)
    {
        selectPiece(row, col);
        highlightValid(selectedPiece, gridLayout);
    }
    else if (isPieceSelected == true)
    {
        if (selectedPiece->row() == row && selectedPiece->col() == col)
        {
            resetColors(gridLayout);
            isPieceSelected = false;
            selectedPiece = nullptr;
        }

        else if (selectedPiece->validMove(pieces, row, col))
        {
            capture(row, col);
            movePiece(row, col);
            resetColors(gridLayout);
            isPieceSelected = false;
            selectedPiece = nullptr;
        }
        else
        {
            selectedButton->setStyleSheet("background-color: red");
        }
    }
}
