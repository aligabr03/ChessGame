/*
Nom: TestCalc.cpp
Description: Tests unitaires
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 5 Mai 2023
*/

#include "Piece.h"
#include <memory>
#include <list>

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

namespace model::tests
{
    TEST(PieceTest, getters)
    {
        QPixmap icon;
        Queen piece2(icon, Piece::Color::White, 2, 3);
        EXPECT_EQ(piece2.color(), Piece::Color::White);
        EXPECT_EQ(piece2.row(), 2);
        EXPECT_EQ(piece2.col(), 3);
        // EXPECT_EQ(piece2.icon(), icon);
        EXPECT_EQ(piece2.type(), Piece::Type::Queen);
    }

    TEST(PieceTest, Setters)
    {
        QPixmap icon;
        Queen piece(icon, Piece::Color::White, 2, 3);
        piece.setRow(4);
        piece.setCol(5);
        EXPECT_EQ(piece.row(), 4);
        EXPECT_EQ(piece.col(), 5);
    }

    TEST(PieceTest, IsPieceAt)
    {
        QPixmap icon;
        std::list<std::shared_ptr<Piece>> pieces;
        std::shared_ptr<Piece> piece1 = std::make_shared<Queen>(icon, Piece::Color::White, 2, 3);
        std::shared_ptr<Piece> piece2 = std::make_shared<Queen>(icon, Piece::Color::Black, 4, 5);
        pieces.push_back(piece1);
        pieces.push_back(piece2);
        Queen piece(icon, Piece::Color::White, 99, 99);
        EXPECT_EQ(piece.isPieceAt(2, 3, pieces), 1);
        EXPECT_EQ(piece.isPieceAt(4, 5, pieces), 2);
        EXPECT_EQ(piece.isPieceAt(1, 1, pieces), 0);
    }

    TEST(KingTest, Type)
    {
        QPixmap icon;
        King king(icon, Piece::Color::White, 2, 3);
        EXPECT_EQ(king.type(), Piece::King);
    }

    TEST(KingTest, ValidMove)
    {
        QPixmap icon;
        std::list<std::shared_ptr<Piece>> pieces;
        std::shared_ptr<Piece> piece1 = std::make_shared<Queen>(icon, Piece::Color::White, 2, 3);
        std::shared_ptr<Piece> piece2 = std::make_shared<Queen>(icon, Piece::Color::Black, 4, 5);
        pieces.push_back(piece1);
        pieces.push_back(piece2);
        King king(icon, Piece::Color::White, 3, 4);
        EXPECT_TRUE(king.validMove(pieces, 2, 4));
        EXPECT_TRUE(king.validMove(pieces, 4, 4));
        EXPECT_TRUE(king.validMove(pieces, 3, 3));
        EXPECT_TRUE(king.validMove(pieces, 3, 5));
        EXPECT_TRUE(king.validMove(pieces, 4, 5));
        EXPECT_TRUE(king.validMove(pieces, 2, 5));
        EXPECT_TRUE(king.validMove(pieces, 4, 3));
        EXPECT_FALSE(king.validMove(pieces, 1, 1));
        EXPECT_FALSE(king.validMove(pieces, 5, 5));
    }

    TEST(KingTest, KingCount)
    {
        QPixmap icon;
        EXPECT_NO_THROW(King king1(icon, Piece::Color::White, 2, 3));
        EXPECT_NO_THROW(King king1(icon, Piece::Color::White, 2, 3); King king2(icon, Piece::Color::Black, 4, 5));
        EXPECT_THROW(King king1(icon, Piece::Color::White, 2, 3); King king2(icon, Piece::Color::Black, 4, 5); King king3(icon, Piece::Color::White, 6, 7), std::runtime_error);
    }

    TEST(BishopTest, ConstructorTest)
    {
        QPixmap icon;
        Bishop bishop(icon, Piece::Color::Black, 1, 2);

        EXPECT_EQ(bishop.color(), Piece::Color::Black);
        EXPECT_EQ(bishop.row(), 1);
        EXPECT_EQ(bishop.col(), 2);
        EXPECT_EQ(bishop.type(), Piece::Type::Bishop);
    }

    TEST(BishopTest, ValidMoveTest)
    {
        QPixmap icon;
        Bishop bishop(icon, Piece::Color::Black, 3, 3);
        std::list<std::shared_ptr<Piece>> pieces = { std::make_shared<Bishop>(bishop) };

        EXPECT_TRUE(bishop.validMove(pieces, 2, 2));
        EXPECT_FALSE(bishop.validMove(pieces, 2, 3));
    }

    TEST(QueenTest, ConstructorTest)
    {
        QPixmap icon;
        Queen queen(icon, Piece::Color::White, 2, 5);

        EXPECT_EQ(queen.color(), Piece::Color::White);
        EXPECT_EQ(queen.row(), 2);
        EXPECT_EQ(queen.col(), 5);
        EXPECT_EQ(queen.type(), Piece::Type::Queen);
    }

    TEST(QueenTest, ValidMoveTest)
    {
        QPixmap icon;
        Queen queen(icon, Piece::Color::White, 3, 3);
        std::list<std::shared_ptr<Piece>> pieces = { std::make_shared<Queen>(queen) };

        EXPECT_TRUE(queen.validMove(pieces, 1, 1));
        EXPECT_TRUE(queen.validMove(pieces, 5, 5));
        EXPECT_FALSE(queen.validMove(pieces, 4, 5));
    }

}

#endif