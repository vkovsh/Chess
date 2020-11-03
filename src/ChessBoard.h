#pragma once

#include <QObject>
#include <QPointer>
#include <QVector>

namespace Chess
{
    class ChessBoard : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(int rows READ getRows NOTIFY rowsChanged)
        Q_PROPERTY(int columns READ getColumns NOTIFY columnsChanged)

    public:
        enum PieceMark
        {
            EMPTY_FIELD_MARK = 0x20,
        };

        using BoardData = QVector<PieceMark>;

    public:
        ChessBoard(int rows, int columns, QObject* ctrl);
        ~ChessBoard();

        PieceMark   getData(int row, int column);
        void    setData(int row, int column, PieceMark value);

        void initBoard();
        void setFen(const QByteArray &fen);
        void movePiece(int fromRow,
                       int fromColumn,
                       int toRow,
                       int toColumn);

        int getRows() const;
        int getColumns() const;

    signals:
        void rowsChanged(int);
        void columnsChanged(int);
        void boardReset();
        void dataChanged(int, int);

    protected:
        bool setDataInternal(int row, int column, PieceMark value);
        void setRows(int newRanks);
        void setColumns(int newColumns);

    private:
        int _rows;
        int _columns;
        QPointer<QObject>   _ctrl;
        BoardData   _boardData;

    private:
        //space in ascii for empty field
//        static const PieceMark EMPTY_FIELD_MARK = 0x20;
    };
}
