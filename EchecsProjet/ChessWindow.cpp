/*
Nom: ChessWindow.cpp
Description: Gere la vue du jeu et implemente les methodes definies dans la class ChessWindow.h
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 5 Mai 2023
*/

#include "ChessWindow.h"

namespace view
{
    ChessWindow::ChessWindow()
    {
        initializeBoard();
        startNormal();
    }

    void ChessWindow::clearBoard()
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

    void ChessWindow::startNormal()
    {
        clearBoard();
        initializeWhitePieces();
        initializeBlackPieces();
    }

    void ChessWindow::startKingOnly()
    {
        const int ICON_SIZE = 45;
        std::pair<int, int> wkingStartPosition = { 0, 4 };
        std::pair<int, int> bkingStartPosition = { 7, 4 };

        clearBoard();
        QPixmap kingb("king1.png");
        QPixmap king("king.png");

        buttons[wkingStartPosition.first][wkingStartPosition.second]->setIcon(kingb);
        buttons[wkingStartPosition.first][wkingStartPosition.second]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        pieces_.push_back(std::make_shared<model::King>(kingb, model::Piece::Black, wkingStartPosition.first, wkingStartPosition.second));

        buttons[bkingStartPosition.first][bkingStartPosition.second]->setIcon(king);
        buttons[bkingStartPosition.first][bkingStartPosition.second]->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        pieces_.push_back(std::make_shared<model::King>(king, model::Piece::White, bkingStartPosition.first, bkingStartPosition.second));
    }

    void ChessWindow::initializeBoard()
    {
        const int BUTTONS_SIZE = 75;
        const int BOARD_SIZE = 600;
        QPushButton* menuButton = new QPushButton("Menu", this);

        QAction* onlyKings = new QAction("Only kings", this);
        QAction* normal = new QAction("New Game", this);

        connect(onlyKings, &QAction::triggered, this, &ChessWindow::startKingOnly);
        connect(normal, &QAction::triggered, this, &ChessWindow::startNormal);

        QMenu* menu = new QMenu(this);
        menu->addAction(normal);
        menu->addAction(onlyKings);

        connect(menuButton, &QPushButton::clicked, menu, [=]()
            { menu->popup(menuButton->mapToGlobal(QPoint(0, menuButton->height()))); });

        QWidget* central_widget = new QWidget();
        setCentralWidget(central_widget);

        QGridLayout* grid_layout = new QGridLayout(central_widget);

        grid_layout->addWidget(menuButton, CHESSBOARD_SIZE_, 0);

        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                QPushButton* button = new QPushButton();
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

    void ChessWindow::initializeBlackPieces()
    {
        const int ICON_SIZE = 45;
        const int BPIECES_START_ROWS = 2;
        QPixmap bishopb("bishop1.png");
        QPixmap queenb("queen1.png");
        QPixmap kingb("king1.png");
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
                        catch (const std::runtime_error& error)
                        {
                            QMessageBox::critical(nullptr, "Error", error.what());
                        }
                    }
                    }
                }
            }
        }
    }

    void ChessWindow::initializeWhitePieces()
    {
        const int ICON_SIZE = 45;
        const int WPIECES_START_ROWS = 6;
        QPixmap bishop("bishop.png");
        QPixmap queen("queen.png");
        QPixmap king("king.png");
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
                        catch (const std::runtime_error& error)
                        {
                            QMessageBox::critical(nullptr, "Error", error.what());
                        }
                    }
                    }
                }
            }
        }
    }

    void ChessWindow::movePiece(int row, int col)
    {
        bool undo = false;
        bool* ptrUndo = &undo;
        model::MoveGuard guard(selectedButton_, lastValidButton_, pieces_, selectedPiece_, row, col, ptrUndo);
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

    void ChessWindow::selectPiece(int row, int col)
    {
        for (auto it = pieces_.begin(); it != pieces_.end(); it++)
        {
            if ((*it)->row() == row && (*it)->col() == col)
            {
                selectedPiece_ = *it;
                isPieceSelected_ = checkTurn();
                lastValidButton_ = selectedButton_;
                break;
            }
        }
    }

    bool ChessWindow::isChecked()
    {
        for (std::shared_ptr<model::Piece> king : pieces_)
        {
            if (king->type() == model::Piece::King)
            {
                for (std::shared_ptr<model::Piece> piece : pieces_)
                {
                    //if (piece->type() != model::Piece::King)
                    //{
                    if (piece->color() == model::Piece::Black && whiteTurn_ && king->color() == model::Piece::White)
                    {
                        if (piece->validMove(pieces_, king->row(), king->col()))
                        {
                            return true;
                        }
                    }
                    else if (piece->color() == model::Piece::White && !whiteTurn_ && king->color() == model::Piece::Black)
                    {
                        if (piece->validMove(pieces_, king->row(), king->col()))
                        {
                            return true;
                        }
                    }
                    //}
                }
            }
        }
        return false;
    }

    bool ChessWindow::checkTurn()
    {
        const int MAX_ROWS = 99;
        if (selectedPiece_->row() != MAX_ROWS && whiteTurn_ && selectedPiece_->color() == model::Piece::White)
        {
            selectedButton_->setStyleSheet("background-color: rgb(233,233,108)");
            return true;
        }
        else if (selectedPiece_->row() != MAX_ROWS && !whiteTurn_ && selectedPiece_->color() == model::Piece::Black)
        {
            selectedButton_->setStyleSheet("background-color: rgb(233,233,108)");
            return true;
        }
        return false;
    }

    void ChessWindow::highlightValidByTurn(std::shared_ptr<model::Piece> piece, QGridLayout* gridLayout)
    {
        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                bool undo = true;
                bool* ptrUndo = &undo;
                model::MoveGuard* guard = new model::MoveGuard(selectedButton_, lastValidButton_, pieces_, selectedPiece_, row, col, ptrUndo);

                bool tempCheck = isChecked();
                delete guard;


                if (piece->validMove(pieces_, row, col) && !tempCheck)
                {
                    QLayoutItem* item = gridLayout->itemAtPosition(row, col);
                    if (item != nullptr)
                    {
                        QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                        button->setStyleSheet("background-color: rgb(233,233,108)");
                    }
                }
            }
        }
    }

    void ChessWindow::highlightValid(std::shared_ptr<model::Piece> piece, QGridLayout* gridLayout)
    {
        const int MAX_ROWS = 99;
        if (selectedPiece_ != nullptr)
        {
            if (selectedPiece_->row() != MAX_ROWS && whiteTurn_ == true && selectedPiece_->color() == model::Piece::White)
            {
                highlightValidByTurn(piece, gridLayout);
            }
            else if (selectedPiece_->row() != MAX_ROWS && whiteTurn_ == false && selectedPiece_->color() == model::Piece::Black)
            {
                highlightValidByTurn(piece, gridLayout);
            }
        }
    }

    void ChessWindow::resetColors(QGridLayout* gridLayout)
    {
        for (int row = 0; row < CHESSBOARD_SIZE_; row++)
        {
            for (int col = 0; col < CHESSBOARD_SIZE_; col++)
            {
                QLayoutItem* item = gridLayout->itemAtPosition(row, col);
                if (item != nullptr)
                {
                    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
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

    void ChessWindow::capture(int row, int col)
    {
        if (selectedPiece_->isPieceAt(row, col, pieces_) != 0)
        {
            for (auto it = pieces_.begin(); it != pieces_.end(); it++)
            {
                if ((*it)->row() == row && (*it)->col() == col)
                {
                    pieces_.erase(it);
                    break;
                }
            }
        }
    }

    void ChessWindow::pieceClick()
    {
        int row, col;
        int rowSpan, colSpan;

        selectedButton_ = qobject_cast<QPushButton*>(sender());
        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(selectedButton_->parentWidget()->layout());
        gridLayout->getItemPosition(gridLayout->indexOf(selectedButton_), &row, &col, &rowSpan, &colSpan);

        if (isPieceSelected_ == false)
        {
            selectPiece(row, col);
            highlightValid(selectedPiece_, gridLayout);
        }
        else if (isPieceSelected_ == true)
        {
            if (selectedPiece_->row() == row && selectedPiece_->col() == col)
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