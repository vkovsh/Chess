#include "ChessCtrl.h"

using namespace Chess;

ChessCtrl::ChessCtrl()
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
}

//signal
//void ChessCtrl::boardChanged(ChessBoard*)
//{

//}

void ChessCtrl::setupBoard()
{
    ChessBoard* newBoard = new ChessBoard(8, 8, this);
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
