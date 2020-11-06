#include "ChessCtrl.h"

using namespace Chess;

ChessCtrl::ChessCtrl(QObject *parent):
    AbstractChessCtrl(parent),
    _piece(ChessBoard::EMPTY_FIELD_MARK,
           ChessBoard::Position(ChessBoard::RANK_UNDEFINED,
                                ChessBoard::COLUMN_UNDEFINED))
{
}

ChessCtrl::~ChessCtrl()
{
}

void ChessCtrl::newGame()
{
    setupBoard();
    getBoard()->setFen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    setResult(NoResult);
    setCurrentPlayer(Player1);
}

bool ChessCtrl::move(const ChessBoard::Position& from,
                  const ChessBoard::Position& to)
{
//    if (getCurrentPlayer() == NoPlayer)
//    {
//        return false;
//    }

//    // is there a piece of the right color?
//    ChessBoard
//        char source = board()->data(colFrom, rankFrom);
//        if(currentPlayer() == Player1 && source != 'P') return false;
//        if(currentPlayer() == Player2 && source != 'p') return false;

//        // both can only move one column right or left
//        if(colTo != colFrom + 1 && colTo != colFrom - 1) return false;

//        // do we move within the board?
//        if(colTo < 1  || colTo  > board()->columns()) return false;
//        if(rankTo < 1 || rankTo > board()->ranks())   return false;

//        // is the destination field black?
//        if((colTo + rankTo) % 2) return false;

//        // is the destination field empty?
//        char destination = board()->data(colTo, rankTo);
//        if(destination != ' ') return false;

//        // is white advancing?
//        if(currentPlayer() == Player1 && rankTo <= rankFrom) return false;

//        board()->movePiece(colFrom, rankFrom, colTo, rankTo);
//        // make the move
//        if(currentPlayer() == Player2) {
//          m_fox = QPoint(colTo, rankTo); // cache fox position
//        }
//        // check win condition
//        if(currentPlayer() == Player2 && rankTo == 1) {
//            setResult(Player2Wins); // fox has escaped
//        } else if(currentPlayer() == Player1 && !foxCanMove()) {
//            setResult(Player1Wins); // fox can't move
//        } else {
//            // the other player makes the move now
//            setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
//        }
//        return true;
////    Q_UNUSED(from)
////    Q_UNUSED(to)
//    return false;
}

bool ChessCtrl::pieceCanMove() const
{
    if  (emptyByOffset(-1, -1) ||
         emptyByOffset(-1, 1) ||
         emptyByOffset(1, -1) ||
         emptyByOffset(1, 1))
    {
        return true;
    }
    return false;
}

bool ChessCtrl::emptyByOffset(int x, int y) const
{
//    const int destCol = m_fox.x() + x;
//    const int destRank = m_fox.y() + y;
//    if(destCol < 1 || destRank < 1 || destCol > board()->columns() || destRank > board()->ranks()) return false;
//    return (board()->data(destCol, destRank) == ' ');
}





