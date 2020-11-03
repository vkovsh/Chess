#include "ChessViewWidget.h"

using namespace Chess;

void ChessViewWidget::setChessBoard(ChessBoard *chessBoard)
{
    if (_chessBoard == chessBoard)
    {
        return;
    }

    if (_chessBoard)
    {
        // disconnect all signal-slot connections between m_board and this
        _chessBoard->disconnect(this);
    }

    _chessBoard = chessBoard;

    // connect signals (to be done later)
    updateGeometry();
}

ChessBoard* ChessViewWidget::getChessBoard() const
{
    return _chessBoard;
}
