/*
Nom: Piece.h
Description: Definit la classe Piece
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 14 Avril 2023
*/

#include <qpixmap.h>

class Piece {
public:
    enum Color { White, Black };

    Piece() = default;

    Piece(QPixmap icon, Color color, int row, int col) : m_icon(icon), m_color(color), m_row(row), m_col(col) {}
    virtual ~Piece() {};

    Color color() const { return m_color; }
    int row() const { return m_row; }
    int col() const { return m_col; }
    QPixmap icon() const { return m_icon; }
    void setRow(int row) { m_row = row; }
    void setCol(int col) { m_col = col; }

    virtual bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) = 0;
    int isPieceAt(int row, int col, std::list<std::shared_ptr<Piece>> pieces);

protected:
    Color m_color = Color::White;
    int m_row = 99;
    int m_col = 99;
    QPixmap m_icon;
};

class King : public Piece
{
public:
    King(QPixmap icon, Color color, int row, int col) : Piece(icon, color, row, col) {}
    bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) override;
};

class Bishop : public Piece
{
public:
    Bishop(QPixmap icon, Color color, int row, int col) : Piece(icon, color, row, col) {}
    bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) override;
};

class Queen : public Piece
{
public:
    Queen(QPixmap icon, Color color, int row, int col) : Piece(icon, color, row, col) {}
    bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) override;
};



