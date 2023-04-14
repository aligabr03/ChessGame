class Piece
{
public:
    enum Color
    {
        White,
        Black
    };
    enum Type
    {
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn
    };

    Piece(Color color, Type type, int row, int col) : m_color(color), m_type(type), m_row(row), m_col(col) {}

    Color color() const { return m_color; }
    Type type() const { return m_type; }
    int row() const { return m_row; }
    int col() const { return m_col; }
    void setRow(int row) { m_row = row; }
    void setCol(int col) { m_col = col; }

    // void deplacement() {}

private:
    Color m_color;
    Type m_type;
    int m_row;
    int m_col;
};