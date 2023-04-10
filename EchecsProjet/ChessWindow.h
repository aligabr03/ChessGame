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
    void initializeWhitePieces(Controller& controller);
    void initializeBlackPieces(Controller& controller);
    void initializeBoard(Controller& controller);
    void addPiece(Controller& controller, QPixmap icon, Piece::Color color, Piece::Type type, int row, int col);

private slots:
    void pieceClick();
private:
    QPushButton* buttons[8][8];
    std::vector<Piece> pieces;
    QPushButton* selectedButton = nullptr;
    bool pieceSelected = false;
    bool whiteTurn = true;
    Piece selectedPiece;
};
