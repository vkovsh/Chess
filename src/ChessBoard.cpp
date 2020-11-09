#include "ChessBoard.h"

#include <QDebug>

using namespace Chess;

ChessBoard::ChessBoard(QObject* ctrl):
    ChessBoard::ChessBoard(RANKS_TOTAL, COLUMNS_TOTAL, ctrl)
{

}

ChessBoard::ChessBoard(Rank ranks, Column columns, QObject* ctrl):
    _ranks(ranks),
    _columns(columns),
    _ctrl(ctrl)
{
    initBoard();
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::setFen(const QByteArray& fen)
{
    int index = 0;
    int skip = 0;
    PieceMark ch;
    for (int rank = RANK_EIGHT; rank >= RANK_ONE; --rank)
    {
        for (int column = COLUMN_A; column <= COLUMN_H; ++column)
        {
            if (skip > 0)
            {
                ch = EMPTY_FIELD_MARK;
                skip--;
            }
            else
            {
                ch = static_cast<PieceMark>(fen.data()[index++]);
                if (ch >= '0' && ch <= '9')
                {
                    skip = ch - '0';
                    ch = EMPTY_FIELD_MARK;
                    skip--;
                }
            }
            setDataInternal(Position(static_cast<Rank>(rank), static_cast<Column>(column)),
                            ch);
        }
        char next = fen.at(index++);
        if(next != '/' && next != ' ')
        {
            initBoard();
            return; // fail on error
        }
    }
    emit boardReset();
}

void ChessBoard::movePiece(Position fromPos, Position toPos)
{
    PieceMark piece  = getData(fromPos);
    setData(toPos, piece);
    setData(fromPos, EMPTY_FIELD_MARK);
}

ChessBoard::PieceMark   ChessBoard::getData(Position pos)
{
    int position = pos.rank * COLUMNS_TOTAL + pos.column;
    return _boardData.at(position);
}

bool ChessBoard::setDataInternal(ChessBoard::Position position, ChessBoard::PieceMark value)
{
    int index = position.rank * COLUMNS_TOTAL + position.column;
    if(_boardData.at(index) == value)
    {
        return false;
    }
    _boardData[index] = value;
    return true;
}

void    ChessBoard::setData(Position position, ChessBoard::PieceMark value)
{
    if (true == setDataInternal(position, value))
    {
        emit dataChanged(position);
    }
}

void ChessBoard::initBoard()
{
    _boardData.fill(EMPTY_FIELD_MARK, ranksCount() * columnsCount());
    emit boardReset();
}

ChessBoard::Rank ChessBoard::ranksCount() const
{
    return _ranks;
}

ChessBoard::Column ChessBoard::columnsCount() const
{
    return _columns;
}

void ChessBoard::setRanks(ChessBoard::Rank newRanks)
{
    if (ranksCount() == newRanks)
    {
        return;
    }

    _ranks = newRanks;
    initBoard();
    emit ranksChanged(_ranks);
}

void ChessBoard::setColumns(ChessBoard::Column newColumns)
{
    if (columnsCount() == newColumns)
    {
        return;
    }

    _columns = newColumns;
    initBoard();
    emit columnsChanged(_columns);
}
