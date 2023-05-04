/*
Nom: ChessWindow.cpp
Description: Gere la vue du jeu et implemente les methodes definies dans la classe ChessWindow.h
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#include "ChessWindow.h"
#include <QMessageBox>

namespace view
{
    view::ChessWindow::ChessWindow()
    {
        initializeBoard();
        startNormal();
    }

    void view::ChessWindow::clearBoard()
    {
        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                buttons[row][col]->setIcon(QIcon());
            }
        }
        pieces_.clear();
        whiteTurn_ = true;
    }

    void view::ChessWindow::startNormal()
    {
        clearBoard();
        initializeWhitePieces();
        initializeBlackPieces();
    }

    void view::ChessWindow::startKingOnly()
    {
        const int ICON_SIZE = 45;
        std::pair<int, int> wkingStartPosition = {0, 4};
        std::pair<int, int> bkingStartPosition = {7, 4};
        clearBoard();
        QPixmap kingb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/king1.png");
        QPixmap king("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/king.png");

        buttons[wkingStartPosition.first][wkingStartPosition.second]->setIcon(kingb);
        buttons[wkingStartPosition.first][wkingStartPosition.second]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        pieces_.push_back(std::make_shared<model::King>(kingb, model::Piece::Black, wkingStartPosition.first, wkingStartPosition.second));

        buttons[bkingStartPosition.first][bkingStartPosition.second]->setIcon(king);
        buttons[bkingStartPosition.first][bkingStartPosition.second]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        pieces_.push_back(std::make_shared<model::King>(king, model::Piece::White, bkingStartPosition.first, bkingStartPosition.second));
    }

    void view::ChessWindow::initializeBoard()
    {
        const int BUTTONS_SIZE = 75;
        const int BOARD_SIZE = 600;
        QPushButton *menuButton = new QPushButton("Menu", this);

        QAction *onlyKings = new QAction("Only kings", this);
        QAction *normal = new QAction("New Game", this);

        connect(onlyKings, &QAction::triggered, this, &ChessWindow::startKingOnly);
        connect(normal, &QAction::triggered, this, &ChessWindow::startNormal);

        QMenu *menu = new QMenu(this);
        menu->addAction(normal);
        menu->addAction(onlyKings);

        connect(menuButton, &QPushButton::clicked, menu, [=]()
                { menu->popup(menuButton->mapToGlobal(QPoint(0, menuButton->height()))); });

        QWidget *central_widget = new QWidget();
        setCentralWidget(central_widget);

        QGridLayout *grid_layout = new QGridLayout(central_widget);

        grid_layout->addWidget(menuButton, CHESSBOARD_SIZE_, 0);

        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                QPushButton *button = new QPushButton();
                connect(button, &QPushButton::clicked, this, &ChessWindow::pieceClick);
                buttons[row][col] = button;
                button->setFixedSize(BUTTONS_SIZE, BUTTONS_SIZE);
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
        setFixedSize(BOARD_SIZE, BOARD_SIZE);
    }

    void view::ChessWindow::initializeBlackPieces()
    {
        const int ICON_SIZE = 45;
        const int BPIECES_START_ROWS = 2;
        QPixmap bishopb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/bishop1.png");
        QPixmap queenb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/queen1.png");
        QPixmap kingb("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/king1.png");
        for (int row = 0; row < BPIECES_START_ROWS; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                if (row == 0)
                {
                    switch (col)
                    {
                    case 2:
                    case 5:
                    {
                        buttons[row][col]->setIcon(bishopb);
                        buttons[row][col]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
                        pieces_.push_back(std::make_shared<model::Bishop>(bishopb, model::Piece::Black, row, col));
                        break;
                    }
                    case 3:
                    {
                        buttons[row][col]->setIcon(queenb);
                        buttons[row][col]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
                        pieces_.push_back(std::make_shared<model::Queen>(queenb, model::Piece::Black, row, col));
                        break;
                    }
                    case 4:
                    {
                        try
                        {
                            buttons[row][col]->setIcon(kingb);
                            buttons[row][col]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
                            pieces_.push_back(std::make_shared<model::King>(kingb, model::Piece::Black, row, col));
                            break;
                        }
                        catch (const std::runtime_error &error)
                        {
                            // Afficher un message d'erreur
                            QMessageBox::critical(nullptr, "Error", error.what());
                        }
                    }
                    }
                }
            }
        }

        // buttons[0][2]->setIcon(bishopb);
        // buttons[0][2]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::Bishop>(bishopb, model::Piece::Black, 0, 2));

        // buttons[0][5]->setIcon(bishopb);
        // buttons[0][5]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::Bishop>(bishopb, model::Piece::Black, 0, 5));

        // buttons[0][3]->setIcon(queenb);
        // buttons[0][3]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::Queen>(queenb, model::Piece::Black, 0, 3));

        // buttons[0][4]->setIcon(kingb);
        // buttons[0][4]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::King>(kingb, model::Piece::Black, 0, 4));
    }

    void view::ChessWindow::initializeWhitePieces()
    {
        const int ICON_SIZE = 45;
        const int WPIECES_START_ROWS = 6;
        QPixmap bishop("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/bishop.png");
        QPixmap queen("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/queen.png");
        QPixmap king("/Users/rayaneoth/Desktop/Cours/LOG/2eme_SESSION/INF1015/Github_LAB/inf1015td/EchecsProjet/king.png");
        for (int row = WPIECES_START_ROWS; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                if (row == 7)
                {
                    switch (col)
                    {
                    case 2:
                    case 5:
                    {
                        buttons[row][col]->setIcon(bishop);
                        buttons[row][col]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
                        pieces_.push_back(std::make_shared<model::Bishop>(bishop, model::Piece::White, row, col));
                        break;
                    }
                    case 3:
                    {
                        buttons[row][col]->setIcon(queen);
                        buttons[row][col]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
                        pieces_.push_back(std::make_shared<model::Queen>(queen, model::Piece::White, row, col));
                        break;
                    }
                    case 4:
                    {
                        try
                        {
                            buttons[row][col]->setIcon(king);
                            buttons[row][col]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
                            pieces_.push_back(std::make_shared<model::King>(king, model::Piece::White, row, col));
                            break;
                        }
                        catch (const std::runtime_error &error)
                        {
                            // Afficher un message d'erreur
                            QMessageBox::critical(nullptr, "Error", error.what());
                        }
                    }
                    }
                }
            }
        }

        // buttons[7][2]->setIcon(bishop);
        // buttons[7][2]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::Bishop>(bishop, model::Piece::White, 7, 2));

        // buttons[7][5]->setIcon(bishop);
        // buttons[7][5]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::Bishop>(bishop, model::Piece::White, 7, 5));

        // buttons[7][3]->setIcon(queen);
        // buttons[7][3]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::Queen>(queen, model::Piece::White, 7, 3));

        // buttons[7][4]->setIcon(king);
        // buttons[7][4]->setIconSize(QSize(45, 45));
        // pieces.push_back(std::make_shared<model::King>(king, model::Piece::White, 7, 4));
    }

    void view::ChessWindow::movePiece(int row, int col)
    {
        bool undo = false;
        bool *ptrUndo = &undo; // pointeur vers la variable booléenne
        model::MoveGuard guard(selectedButton_, lastValidButton_, selectedPiece_, row, col, ptrUndo);
        if (isChecked())
        {
            undo = true;
        }
        else
        {
            undo = false;
            whiteTurn_ = !whiteTurn_;
        }
    }

    void view::ChessWindow::selectPiece(int row, int col)
    {
        for (auto it = pieces_.begin(); it != pieces_.end(); it++)
        {
            if ((*it)->getRow() == row && (*it)->getCol() == col)
            {
                selectedPiece_ = *it;
                isPieceSelected_ = checkTurn();
                lastValidButton_ = selectedButton_;
                break;
            }
        }
    }

    bool view::ChessWindow::isChecked()
    {
        for (std::shared_ptr<model::Piece> king : pieces_)
        {
            if (king->getType() == model::Piece::King)
            {
                for (std::shared_ptr<model::Piece> piece : pieces_)
                {
                    if (piece->getType() != model::Piece::King)
                    {
                        if (piece->getColor() == model::Piece::Black && whiteTurn_ && king->getColor() == model::Piece::White)
                        {
                            if (piece->validMove(pieces_, king->getRow(), king->getCol()))
                            {
                                return true;
                            }
                        }
                        else if (piece->getColor() == model::Piece::White && !whiteTurn_ && king->getColor() == model::Piece::Black)
                        {
                            if (piece->validMove(pieces_, king->getRow(), king->getCol()))
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
        const int MAX_ROWS = 99;
        if (selectedPiece_->getRow() != MAX_ROWS && whiteTurn_ && selectedPiece_->getColor() == model::Piece::White)
        {
            selectedButton_->setStyleSheet("background-color: rgb(233,233,108)");
            return true;
        }
        else if (selectedPiece_->getRow() != MAX_ROWS && !whiteTurn_ && selectedPiece_->getColor() == model::Piece::Black)
        {
            selectedButton_->setStyleSheet("background-color: rgb(233,233,108)");
            return true;
        }
        return false;
    }

    void view::ChessWindow::highlightValidByTurn(std::shared_ptr<model::Piece> piece, QGridLayout *gridLayout)
    {
        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                if (piece->validMove(pieces_, row, col))
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
        const int MAX_ROWS = 99;
        if (selectedPiece_ != nullptr)
        {
            if (selectedPiece_->getRow() != MAX_ROWS && whiteTurn_ == true && selectedPiece_->getColor() == model::Piece::White)
            {
                highlightValidByTurn(piece, gridLayout);
            }
            else if (selectedPiece_->getRow() != MAX_ROWS && whiteTurn_ == false && selectedPiece_->getColor() == model::Piece::Black)
            {
                highlightValidByTurn(piece, gridLayout);
            }
        }
    }

    void view::ChessWindow::resetColors(QGridLayout *gridLayout)
    {
        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
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
        if (selectedPiece_->isPieceAt(row, col, pieces_) != 0)
        {
            for (auto it = pieces_.begin(); it != pieces_.end(); it++)
            {
                if ((*it)->getRow() == row && (*it)->getCol() == col)
                {
                    pieces_.erase(it);
                    break;
                }
            }
        }
    }

    void view::ChessWindow::pieceClick()
    {
        int row, col;
        int rowSpan, colSpan;

        selectedButton_ = qobject_cast<QPushButton *>(sender());
        QGridLayout *gridLayout = qobject_cast<QGridLayout *>(selectedButton_->parentWidget()->layout());
        gridLayout->getItemPosition(gridLayout->indexOf(selectedButton_), &row, &col, &rowSpan, &colSpan);

        if (isPieceSelected_ == false)
        {
            selectPiece(row, col);
            highlightValid(selectedPiece_, gridLayout);
        }
        else if (isPieceSelected_ == true)
        {
            if (selectedPiece_->getRow() == row && selectedPiece_->getCol() == col)
            {
                resetColors(gridLayout);
                isPieceSelected_ = false;
                selectedPiece_ = nullptr;
            }

            else if (selectedPiece_->validMove(pieces_, row, col))
            {
                capture(row, col);
                movePiece(row, col);
                resetColors(gridLayout);
                isPieceSelected_ = false;
                selectedPiece_ = nullptr;
            }
            else
            {
                selectedButton_->setStyleSheet("background-color: red");
            }
        }
    }
}