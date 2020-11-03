#pragma once

#include <QWidget>
#include <QPointer>

#include "ChessBoard.h"

namespace Chess
{
    class ChessViewWidget : public QWidget
    {
        Q_OBJECT

    public:
        void setChessBoard(ChessBoard *chessBoard);
        ChessBoard* getChessBoard() const;

    private:
        QPointer<ChessBoard>    _chessBoard;
    };
}
