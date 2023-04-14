// #include "ChessWindow.hpp"

// ChessWindow::ChessWindow()
// {
//     initializeBoard();
//     initializeWhitePieces();
//     initializeBlackPieces();
// }

// void ChessWindow::initializeBoard()
// {
//     QWidget *central_widget = new QWidget();
//     setCentralWidget(central_widget);

//     QGridLayout *grid_layout = new QGridLayout(central_widget);

//     for (int row = 0; row < 8; row++)
//     {
//         for (int col = 0; col < 8; col++)
//         {
//             QPushButton *button = new QPushButton();
//             buttons[row][col] = button;
//             button->setFixedSize(50, 50);
//             if ((row + col) % 2 == 0)
//             {
//                 button->setStyleSheet("background-color: rgb(220,220,220)");
//             }
//             else
//             {
//                 button->setStyleSheet("background-color: green");
//             }
//             grid_layout->addWidget(button, row, col);
//         }
//     }
//     setFixedSize(400, 400);
// }

// void ChessWindow::initializeWhitePieces()
// {
//     QPixmap rookw("rook.png");
//     QPixmap knightw("knight.png");
//     QPixmap bishopw("bishop.png");
//     QPixmap queenw("queen.png");
//     QPixmap kingw("king.png");
//     QPixmap pawnw("pawn.png");
//     for (int row = 0; row < 2; row++)
//     {
//         for (int col = 0; col < 8; col++)
//         {
//             if (row == 0)
//             {
//                 switch (col)
//                 {
//                 case 0:
//                 case 7:
//                     addPiece(rookw, Piece::Color::White, Piece::Type::Rook, row, col);
//                     break;
//                 case 1:
//                 case 6:
//                     addPiece(knightw, Piece::Color::White, Piece::Type::Knight, row, col);
//                     break;
//                 case 2:
//                 case 5:
//                     addPiece(bishopw, Piece::Color::White, Piece::Type::Bishop, row, col);
//                     break;
//                 case 3:
//                     addPiece(queenw, Piece::Color::White, Piece::Type::Queen, row, col);
//                     break;
//                 case 4:
//                     addPiece(kingw, Piece::Color::White, Piece::Type::King, row, col);
//                     break;
//                 }
//             }
//             else
//             {
//                 addPiece(pawnw, Piece::Color::White, Piece::Type::Pawn, row, col);
//             }
//         }
//     }
// }

// void ChessWindow::initializeBlackPieces()
// {
//     QPixmap rookb("rook1.png");
//     QPixmap knightb("knight1.png");
//     QPixmap bishopb("bishop1.png");
//     QPixmap queenb("queen1.png");
//     QPixmap kingb("king1.png");
//     QPixmap pawnb("pawn1.png");
//     for (int row = 6; row < 8; row++)
//     {
//         for (int col = 0; col < 8; col++)
//         {
//             if (row == 7)
//             {
//                 switch (col)
//                 {
//                 case 0:
//                 case 7:
//                     addPiece(rookb, Piece::Color::Black, Piece::Type::Rook, row, col);
//                     break;
//                 case 1:
//                 case 6:
//                     addPiece(knightb, Piece::Color::Black, Piece::Type::Knight, row, col);
//                     break;
//                 case 2:
//                 case 5:
//                     addPiece(bishopb, Piece::Color::Black, Piece::Type::Bishop, row, col);
//                     break;
//                 case 3:
//                     addPiece(queenb, Piece::Color::Black, Piece::Type::Queen, row, col);
//                     break;
//                 case 4:
//                     addPiece(kingb, Piece::Color::Black, Piece::Type::King, row, col);
//                     break;
//                 }
//             }
//             else
//             {
//                 addPiece(pawnb, Piece::Color::Black, Piece::Type::Pawn, row, col);
//             }
//         }
//     }
// }

// void ChessWindow::addPiece(QPixmap icon, Piece::Color color, Piece::Type type, int row, int col)
// {
//     Piece piece(color, type, row, col);
//     buttons[row][col]->setIcon(icon);
//     pieces.push_back(piece);
// }

#include <QHBoxLayout>
#include <QLabel>
#include "ChessWindow.hpp"
#include "Piece.hpp"

ChessWindow::ChessWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // Initialisation de l'échiquier
    init_board();

    // Création d'une pièce blanche de type roi
    Piece piece(Piece::White, Piece::King, 0, 4);

    // Création d'un QLabel pour représenter la pièce
    QLabel* piece_label = new QLabel(this);
    piece_label->setPixmap(piece_pixmap(piece));

    // Ajout du QLabel sur l'échiquier
    buttons[0][4]->addWidget(piece_label);
}

void ChessWindow::init_board()
{
    // Création des cases de l'échiquier
    for(int row = 0; row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            // Création d'une QVBoxLayout pour chaque case
            QVBoxLayout* square_layout = new QVBoxLayout();
            square_layout->setSpacing(0);
            // square_layout->setMargin(0);

            // Ajout d'une QLabel noire ou blanche sur la case
            QLabel* square_label = new QLabel(this);
            square_label->setFixedSize(50, 50);
            if((row + col) % 2 == 0) {
                square_label->setStyleSheet("background-color: white;");
            } else {
                square_label->setStyleSheet("background-color: gray;");
            }
            square_layout->addWidget(square_label);

            // Ajout de la QVBoxLayout sur l'échiquier
            buttons[row][col] = square_layout;
            m_chessboard->addLayout(square_layout, row, col);
        }
    }

    // Mise à jour de la taille minimale de la fenêtre
    setMinimumSize(50 * 8, 50 * 8);
}

QPixmap ChessWindow::piece_pixmap(const Piece& piece) const
{
    // Détermination du chemin d'accès à l'image de la pièce
    QString filename;
    switch(piece.type()) {
        case Piece::King:
            filename = (piece.color() == Piece::White) ? "king.png" : "king1.png";
            break;
        case Piece::Queen:
            filename = (piece.color() == Piece::White) ? "queen.png" : "queen1.png";
            break;
        case Piece::Rook:
            filename = (piece.color() == Piece::White) ? "rook.png" : "rook1.png";
            break;
        case Piece::Bishop:
            filename = (piece.color() == Piece::White) ? "bishop.png" : "bishop1.png";
            break;
        case Piece::Knight:
            filename = (piece.color() == Piece::White) ? "knight.png" : "knight1.png";
            break;
        case Piece::Pawn:
            filename = (piece.color() == Piece::White) ? "pawn.png" : "pawn1.png";
            break;
    }

    // Chargement de l'image de la pièce
    QPixmap pixmap(filename);
    return pixmap;
}
