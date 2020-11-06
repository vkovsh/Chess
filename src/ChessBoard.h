#pragma once

#include <QObject>
#include <QPointer>
#include <QVector>

namespace Chess
{
    class ChessBoard : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(int ranks READ ranksCount NOTIFY ranksChanged)
        Q_PROPERTY(int columns READ columnsCount NOTIFY columnsChanged)

    public:
        enum PieceMark
        {
            EMPTY_FIELD_MARK = 0x20,
            WHITE_KING_MARK = 'K',
            BLACK_KING_MARK = 'k',
            WHITE_QUEEN_MARK = 'Q',
            BLACK_QUEEN_MARK = 'q',
            WHITE_ROOK_MARK = 'R',
            BLACK_ROOK_MARK = 'r',
            WHITE_BISHOP_MARK = 'B',
            BLACK_BISHOP_MARK = 'b',
            WHITE_KNIGHT_MARK = 'N',
            BLACK_KNIGHT_MARK = 'n',
            WHITE_PAWN_MARK = 'P',
            BLACK_PAWN_MARK = 'p',
        };

        enum Rank
        {
            RANK_UNDEFINED = -1,
            RANK_ONE = 0,
            RANK_TWO = 1,
            RANK_THREE = 2,
            RANK_FOUR = 3,
            RANK_FIVE = 4,
            RANK_SIX = 5,
            RANK_SEVEN = 6,
            RANK_EIGHT = 7,
            RANKS_TOTAL = 8,
        };

        enum Column
        {
            COLUMN_UNDEFINED = -1,
            COLUMN_A = 0,
            COLUMN_B = 1,
            COLUMN_C = 2,
            COLUMN_D = 3,
            COLUMN_E = 4,
            COLUMN_F = 5,
            COLUMN_G = 6,
            COLUMN_H = 7,
            COLUMNS_TOTAL = 8,
        };

        struct Position
        {
        public:
            Position(Rank r, Column c): rank(r), column(c){}
            ~Position(){}

        public:
            Rank rank;
            Column column;
        };

        using BoardData = QVector<PieceMark>;

    public:
        //constructors and destructors
        ChessBoard(QObject* ctrl);
        ~ChessBoard();

        //methods
        void initBoard();
        void setFen(const QByteArray& fen);
        void movePiece(Position fromPosition, Position toPosition);

        //getters and setters
        PieceMark   getData(Position position);
        void    setData(Position position, PieceMark value);
        Rank ranksCount() const;
        Column columnsCount() const;

    signals:
        void ranksChanged(Rank);
        void columnsChanged(Column);
        void boardReset();
        void dataChanged(Position);

    protected:
        ChessBoard(Rank ranksCount, Column columnsCount, QObject* ctrl);
        bool setDataInternal(Position position, PieceMark value);
        void setRanks(Rank newRanks);
        void setColumns(Column newColumns);

    private:
        Rank _ranks;
        Column _columns;
        QPointer<QObject>   _ctrl;
        BoardData   _boardData;
    };
}
