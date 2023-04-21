/*
Nom: Piece.h
Description: Definit la classe Piece
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 20 Avril 2023
*/

#ifndef PIECE_H
#define PIECE_H

#include <qpixmap.h>
#include <stdexcept>

namespace model
{
    class Piece {
    public:
        enum Type { King, Queen, Bishop };
        enum Color { White, Black };

        Piece() = default;

        Piece(QPixmap icon, Color color, int row, int col) : m_icon(icon), m_color(color), m_row(row), m_col(col) {}

        virtual ~Piece() {};

        Color color() const { return m_color; }
        int row() const { return m_row; }
        int col() const { return m_col; }
        virtual Type type() = 0;
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

        static int s_kingCount;
    };

    class King : public Piece
    {
    public:
        King(QPixmap icon, Color color, int row, int col) : Piece(icon, color, row, col)
        {
                ++s_kingCount;
                if (s_kingCount > 2)
                {
                    --s_kingCount;
                    throw std::runtime_error("cannot create more than two kings.");
                }
        }

        Type type() override { return Piece::King; }
        bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) override;
    };

    class Bishop : public Piece
    {
    public:
        Bishop(QPixmap icon, Color color, int row, int col) : Piece(icon, color, row, col) {}

        Type type() override { return Piece::Bishop; }
        bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) override;
    };

    class Queen : public Piece
    {
    public:
        Queen(QPixmap icon, Color color, int row, int col) : Piece(icon, color, row, col) {}

        Type type() override { return Piece::Queen; }
        bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) override;
    };
}

#endif
