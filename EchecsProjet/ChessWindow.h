#include <qmainwindow>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtwidgets>
#include <qlabel.h>
#include <qobject.h>

#include "Controller.h"

class ChessWindow : public QMainWindow {
public:
    ChessWindow();
    void initializeWhitePieces();
    void initializeBlackPieces();
    void initializeBoard();
    void addPiece(QPixmap icon, Piece::Color color, int row, int col);

    void movePiece();

private slots:
    void pieceClick();
private:
    QPushButton* buttons[8][8];
    std::vector<Piece> pieces;
    QPushButton* selectedButton = nullptr;
    bool isPieceSelected = false;
    bool whiteTurn = true;
    Piece* selectedPiece;
    QString originalStyle;

};
