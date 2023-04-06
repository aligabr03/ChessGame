#include <iostream>
#include <vector>
#include <string>
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>

using namespace std;

// Enum pour les différentes types de pièces
enum PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

// Enum pour les deux couleurs
enum PieceColor {
    WHITE,
    BLACK
};

// Classe pour représenter une pièce
class Piece {
public:
    Piece(PieceType type, PieceColor color) : type(type), color(color) {}
    virtual ~Piece() {}

    virtual bool isValidMove(int fromX, int fromY, int toX, int toY) const = 0;

    PieceType getType() const { return type; }
    PieceColor getColor() const { return color; }

private:
    PieceType type;
    PieceColor color;
};

// Classe pour représenter le roi
class King : public Piece {
public:
    King(PieceColor color) : Piece(KING, color) {}

    bool isValidMove(int fromX, int fromY, int toX, int toY) const override {
        return (abs(toX - fromX) <= 1 && abs(toY - fromY) <= 1);
    }
};

// Classe pour représenter la tour
class Rook : public Piece {
public:
    Rook(PieceColor color) : Piece(ROOK, color) {}

    bool isValidMove(int fromX, int fromY, int toX, int toY) const override {
        return (fromX == toX || fromY == toY);
    }
};

// Classe pour représenter le cavalier
class Knight : public Piece {
public:
    Knight(PieceColor color) : Piece(KNIGHT, color) {}

    bool isValidMove(int fromX, int fromY, int toX, int toY) const override {
        int deltaX = abs(fromX - toX);
        int deltaY = abs(fromY - toY);
        return (deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1);
    }
};

// Classe pour représenter l'échiquier
class Board {
public:
    Board() {
        // Initialisation des pièces sur l'échiquier
        pieces.resize(8);
        for (int i = 0; i < 8; i++) {
            pieces[i].resize(8, nullptr);
        }
        // Initialisation du roi blanc
        pieces[0][4] = new King(WHITE);
        // Initialisation de la tour blanche
        pieces[0][0] = new Rook(WHITE);
        // Initialisation du cavalier blanc
        pieces[0][1] = new Knight(WHITE);
    }

    ~Board() {
        // Suppression des pièces de l'échiquier
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete pieces[i][j];
            }
        }
    }

    Piece* getPiece(int x, int y) const {
        return pieces[x][y];
    }

    void setPiece(int x, int y, Piece* piece) {
        pieces[x][y] = piece;
    }

    void movePiece(int fromX, int fromY, int toX, int toY) {
        Piece* piece = pieces[fromX][fromY];