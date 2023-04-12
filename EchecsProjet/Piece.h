#include <qmainwindow>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtwidgets>
#include <qlabel.h>

class Piece {
public:
    enum Color { White, Black };
    enum Type { King, Queen, Bishop };

    Piece(){}

    Piece(QPixmap icon, Color color, Type type, int row, int col) :
        m_icon(icon), m_color(color), m_type(type), m_row(row), m_col(col) {}

    Color color() const { return m_color; }
    Type type() const { return m_type; }
    int row() const { return m_row; }
    int col() const { return m_col; }
    QPixmap icon() const { return m_icon; }
    void setRow(int row) { m_row = row; }
    void setCol(int col) { m_col = col; }

private:
    Color m_color = Color::White;
    Type m_type = Type::King;
    int m_row = 99;
    int m_col = 99;
    QPixmap m_icon;
};
