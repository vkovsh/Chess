#pragma once

#include <QObject>
#include <QPointer>

namespace Chess
{
    class ChessBoard : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(int rows READ getRows NOTIFY rowsChanged)
        Q_PROPERTY(int columns READ getColumns NOTIFY columnsChanged)

    public:
        ChessBoard(int rows, int columns, QObject* ctrl);
        ~ChessBoard();
        int getRows() const;
        int getColumns() const;

    signals:
        void rowsChanged(int);
        void columnsChanged(int);

    protected:
        void setRows(int newRanks);
        void setColumns(int newColumns);

    private:
        int _rows;
        int _columns;
        QPointer<QObject>   _ctrl;
    };
}
