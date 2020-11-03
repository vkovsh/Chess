#include "ChessBoard.h"

using namespace Chess;

ChessBoard::ChessBoard(int rows, int columns, QObject* ctrl):
    _rows(rows),
    _columns(columns),
    _ctrl(ctrl)
{
    initBoard();
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::setFen(const QByteArray &fen)
{
    int index = 0;
    int skip = 0;
    const int columnCount = getColumns();
    PieceMark ch;
    for(int row = getRows(); row > 0; --row)
    {
        for (int column = 1; column <= columnCount; ++column)
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
            setDataInternal(row, column, ch);
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

void ChessBoard::movePiece(int fromRow,
               int fromColumn,
               int toRow,
               int toColumn)
{
    setData(toRow, toColumn, getData(fromRow, fromColumn));
    setData(fromRow, fromColumn, EMPTY_FIELD_MARK);
}

ChessBoard::PieceMark   ChessBoard::getData(int row, int column)
{
    int position = (row - 1) * getColumns() + (column - 1);
    return _boardData.at(position);
}

bool ChessBoard::setDataInternal(int row, int column, ChessBoard::PieceMark value)
{
    int index = (row - 1) * getColumns() + (column - 1);
    if(_boardData .at(index) == value)
    {
        return false;
    }
    _boardData[index] = value;
    return true;
}

void    ChessBoard::setData(int row, int column, ChessBoard::PieceMark value)
{
    if (true == setDataInternal(row, column, value))
    {
        emit dataChanged(row, column);
    }
}

void ChessBoard::initBoard()
{
    _boardData.fill(EMPTY_FIELD_MARK, getRows() * getColumns());
    emit boardReset();
}

int ChessBoard::getRows() const
{
    return _rows;
}

int ChessBoard::getColumns() const
{
    return _columns;
}

void ChessBoard::setRows(int newRows)
{
    if(getRows() == newRows)
    {
        return;
    }
    _rows = newRows;
    initBoard();
    emit rowsChanged(_rows);
}

void ChessBoard::setColumns(int newColumns)
{
    if(getColumns() == newColumns)
    {
        return;
    }
    _columns = newColumns;
    initBoard();
    emit columnsChanged(_columns);
}


