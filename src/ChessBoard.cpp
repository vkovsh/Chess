#include "ChessBoard.h"

using namespace Chess;

ChessBoard::ChessBoard(int rows, int columns, QObject* ctrl)
{

}

ChessBoard::~ChessBoard()
{

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
    emit rowsChanged(_rows);
}

void ChessBoard::setColumns(int newColumns)
{
    if(getColumns() == newColumns)
    {
        return;
    }
    _columns = newColumns;
    emit columnsChanged(_columns);
}


