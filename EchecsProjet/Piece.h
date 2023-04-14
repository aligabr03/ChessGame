#include <qmainwindow>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtwidgets>
#include <qlabel.h>

class Piece
{
public:
    enum Color
    {
        White,
        Black
    };
    // enum Type
    // {
    //     King,
    //     Queen,
    //     Bishop
    // };

    Piece() = default;
    virtual ~Piece() {}

    Piece(QPixmap icon, Color color, int row, int col) : m_icon(icon), m_color(color), m_row(row), m_col(col) {}

    Color color() const { return m_color; }
    // Type type() const { return m_type; }
    int row() const { return m_row; }
    int col() const { return m_col; }
    QPixmap icon() const { return m_icon; }
    void setRow(int row) { m_row = row; }
    void setCol(int col) { m_col = col; }
    virtual bool validMove(std::vector<Piece> pieces, int rowDest, int colDest) = 0;

protected:
    QPixmap m_icon;
    Color m_color;
    // Type m_type;
    int m_row ;
    int m_col ;
};

class King : public Piece
{
public:
    King(QPixmap icon, Color color, int row, int col) : m_color(color),m_icon(icon), m_row(row), m_col(col) {}
    bool validMove(std::vector<Piece> pieces, int rowDest, int colDest) override;

protected:
    Color m_color;
    // Type m_type = Piece::King;
    QPixmap m_icon;
    int m_row ;
    int m_col ;
};

class Bishop : public Piece
{
public:
    Bishop(QPixmap icon, Color color, int row, int col) :  m_color(color),m_icon(icon), m_row(row), m_col(col) {}
    bool validMove(std::vector<Piece> pieces, int rowDest, int colDest) override;

protected:
    Color m_color;
    // Type m_type = Piece::King
    QPixmap m_icon;
    int m_row ;
    int m_col ;
};

class Queen : public Piece
{
public:
    Queen(QPixmap icon, Color color, int row, int col) : m_color(color),m_icon(icon), m_row(row), m_col(col) {}
    bool validMove(std::vector<Piece> pieces, int rowDest, int colDest) override;

protected:
    Color m_color;
    // Type m_type = Piece::King
    QPixmap m_icon;
    int m_row ;
    int m_col ;
};