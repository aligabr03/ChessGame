#include <QtWidgets>
#include <QApplication>

class ChessBoard : public QWidget
{
public:
    ChessBoard(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(400, 400);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        int size = 50; // taille d'une case en pixels
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                if ((row + col) % 2 == 0)
                {
                    painter.fillRect(col * size, row * size, size, size, Qt::lightGray);
                }
                else
                {
                    painter.fillRect(col * size, row * size, size, size, Qt::darkGray);
                }
            }
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChessBoard board;
    board.show();

    return app.exec();
}
