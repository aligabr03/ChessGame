#include <qmainwindow>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtwidgets>
#include <qlabel.h>

#include "Controller.h"

class ChessWindow : public QMainWindow {
public:
    ChessWindow();
    void initializeWhitePieces();
    void initializeBlackPieces();
    void initializeBoard();
    void addPiece(QPixmap icon, Piece::Color color, Piece::Type type, int row, int col);

private:
    QPushButton* buttons[8][8];
    std::vector<Piece> pieces;
};
