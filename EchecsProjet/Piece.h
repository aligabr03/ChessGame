/*
Nom: Piece.h
Description: Definit la classe Piece
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 5 Mai 2023
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

        Piece(QPixmap icon, Color color, int row, int col) : icon_(icon), color_(color), row_(row), col_(col) {}

        virtual ~Piece() {};

        Color color() const { return color_; }
        int row() const { return row_; }
        int col() const { return col_; }
        virtual Type type() = 0;
        QPixmap icon() const { return icon_; }
        void setRow(int row) { row_ = row; }
        void setCol(int col) { col_ = col; }


        virtual bool validMove(std::list<std::shared_ptr<Piece>> pieces, int rowDest, int colDest) = 0;
        int isPieceAt(int row, int col, std::list<std::shared_ptr<Piece>> pieces);

    protected:
        Color color_ = Color::White;
        int row_ = 99;
        int col_ = 99;
        QPixmap icon_;

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
                throw std::runtime_error("Cannot create more than two kings.");
            }
        }

        ~King() {
            --s_kingCount;
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
