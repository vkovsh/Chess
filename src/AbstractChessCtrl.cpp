#include "AbstractChessCtrl.h"

using namespace Chess;

AbstractChessCtrl::AbstractChessCtrl(QObject *parent):
    QObject(parent),
    _result(NoResult),
    _currentPlayer(NoPlayer),
    _chessBoard(NULL)
{

}

AbstractChessCtrl::~AbstractChessCtrl()
{

}

ChessBoard* AbstractChessCtrl::getBoard() const
{
    return _chessBoard;
}

void AbstractChessCtrl::newGame()
{
    setupBoard();
    getBoard()->setFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void AbstractChessCtrl::setupBoard()
{
    setBoard(new ChessBoard(this));
}

void AbstractChessCtrl::setBoard(ChessBoard *chessBoard)
{
    if(chessBoard == _chessBoard)
    {
        return;
    }
    delete _chessBoard;
    _chessBoard = chessBoard;
    emit boardChanged(_chessBoard);
}

void AbstractChessCtrl::setCurrentPlayer(Player value)
{
    if (getCurrentPlayer() == value)
    {
        return;
    }

    _currentPlayer = value;
    emit currentPlayerChanged(_currentPlayer);
}

bool AbstractChessCtrl::move(const ChessBoard::Position& from,
                  const ChessBoard::Position& to)
{
    Q_UNUSED(from)
    Q_UNUSED(to)
    return false;
}
