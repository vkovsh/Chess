#pragma once

#include <QObject>
#include <QPointer>

#include "ChessBoard.h"

namespace Chess
{
    class ChessCtrl : public QObject
    {
        Q_OBJECT

    public:
        ChessCtrl();
        ~ChessCtrl();

    public:
        ChessBoard* getBoard() const;

    public slots:
        virtual void newGame();

    signals:
        void boardChanged(ChessBoard*);

    protected:
        virtual void setupBoard();
        void setBoard(ChessBoard *board);

    private:
        ChessBoard* _chessBoard;
    };
}
