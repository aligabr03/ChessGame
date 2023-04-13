#include <qmainwindow>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtwidgets>
#include <qlabel.h>
#include <qobject.h>
#include <qgraphicseffect.h>

#include "Controller.h"

class ChessWindow : public QMainWindow {
public:
    ChessWindow();
    void initializeWhitePieces();
    void initializeBlackPieces();
    void initializeBoard();

    void addPiece(QPixmap icon, Piece::Color color, Piece::Type type, int row, int col);
    void movePiece(int row, int col);
    void selectPiece(int row, int col);
    void capture(int row, int col);

    void highlightValid(Piece* piece, QGridLayout* gridLayout);
    void highlightValidByTurn(Piece* piece, QGridLayout* gridLayout);
    void resetColors(QGridLayout* gridLayout);

private slots:
    void pieceClick();

private:
    QPushButton* buttons[8][8];
    std::list<Piece> pieces;

    QPushButton* selectedButton = nullptr;
    QPushButton* lastValidButton = nullptr;
    Piece* selectedPiece = nullptr;

    bool isPieceSelected = false;
    bool whiteTurn = true;
};
