#include "ChessCtrl.h"

using namespace Chess;

ChessCtrl::ChessCtrl(QObject* parent):
    _parent(parent),
    _chessBoard(NULL)
{

}

ChessCtrl::~ChessCtrl()
{

}

ChessBoard* ChessCtrl::getBoard() const
{
    return _chessBoard;
}

void ChessCtrl::newGame()
{
    setupBoard();
    getBoard()->setFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void ChessCtrl::setupBoard()
{
    ChessBoard* newBoard = new ChessBoard(this);
    setBoard(newBoard);
}

void ChessCtrl::setBoard(ChessBoard *chessBoard)
{
    if(chessBoard == _chessBoard)
    {
        return;
    }
    delete _chessBoard;
    _chessBoard = chessBoard;
    emit boardChanged(_chessBoard);
}
