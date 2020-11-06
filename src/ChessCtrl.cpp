#include "ChessCtrl.h"

using namespace Chess;

ChessCtrl::ChessCtrl(QObject *parent):
    AbstractChessCtrl(parent),
    _pieceMove(ChessBoard::EMPTY_FIELD_MARK,
           ChessBoard::Position(ChessBoard::RANK_UNDEFINED,
                                ChessBoard::COLUMN_UNDEFINED),
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
    if (getCurrentPlayerID() == NoPlayer)
    {
        return false;
    }

    // do we move within the board?
    if (to.column == ChessBoard::COLUMN_UNDEFINED ||
            to.column == ChessBoard::COLUMNS_TOTAL ||
            to.rank == ChessBoard::RANKS_TOTAL ||
            to.rank == ChessBoard::RANK_UNDEFINED)
    {
        return false;
    }

    // is there a piece of the right color?
    ChessBoard::PieceMark source = getBoard()->getData(from);
    if (getCurrentPlayerID() == Player1)
    {
        if (source != ChessBoard::WHITE_KING_MARK &&
                source != ChessBoard::WHITE_QUEEN_MARK &&
                source != ChessBoard::WHITE_ROOK_MARK &&
                source != ChessBoard::WHITE_BISHOP_MARK &&
                source != ChessBoard::WHITE_KNIGHT_MARK &&
                source != ChessBoard::WHITE_PAWN_MARK)
        {
            return false;
        }
    }

    if (getCurrentPlayerID() == Player2)
    {
        if (source != ChessBoard::BLACK_KING_MARK &&
                source != ChessBoard::BLACK_QUEEN_MARK &&
                source != ChessBoard::BLACK_ROOK_MARK &&
                source != ChessBoard::BLACK_BISHOP_MARK &&
                source != ChessBoard::BLACK_KNIGHT_MARK &&
                source != ChessBoard::BLACK_PAWN_MARK)
        {
            return false;
        }
    }

    _piece.pieceMark = source;
    _piece.positionFrom = from;
    _piece.positionTo = to;
    if (pieceCanMove() == false)
    {
        return false;
    }

    //        // both can only move one column right or left
//        if(colTo != colFrom + 1 && colTo != colFrom - 1) return false;

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

bool ChessCtrl::isCheck() const
{
    return false;
}

bool ChessCtrl::isCheckmate() const
{
    return false;
}

bool ChessCtrl::isStalemate() const
{
    return false;
}

bool ChessCtrl::pieceCanMove() const
{
    switch (_piece.pieceMark)
    {
    case ChessBoard::WHITE_KING_MARK:
        return kingCanMove();
    case ChessBoard::WHITE_QUEEN_MARK:
        return queenCanMove();
    case ChessBoard::WHITE_ROOK_MARK :
        return rookCanMove();
    case ChessBoard::WHITE_BISHOP_MARK:
        return bishopCanMove();
    case ChessBoard::WHITE_KNIGHT_MARK:
        return knightCanMove();
    case ChessBoard::WHITE_PAWN_MARK:
        return pawnCanMove();
    case ChessBoard::BLACK_KING_MARK:
        return kingCanMove();
    case ChessBoard::BLACK_QUEEN_MARK:
        return queenCanMove();
    case ChessBoard::BLACK_ROOK_MARK :
        return rookCanMove();
    case ChessBoard::BLACK_BISHOP_MARK:
        return bishopCanMove();
    case ChessBoard::BLACK_KNIGHT_MARK:
        return knightCanMove();
    case ChessBoard::BLACK_PAWN_MARK:
        return pawnCanMove();
    default:
        return false;
    }
}

bool ChessCtrl::kingCanMove() const
{
    return false;
}

bool ChessCtrl::queenCanMove() const
{
    return false;
}

bool ChessCtrl::rookCanMove() const
{
    return false;
}

bool ChessCtrl::bishopCanMove() const
{
    return false;
}

bool ChessCtrl::knightCanMove() const
{
    return false;
}

bool ChessCtrl::pawnCanMove() const
{
    return false;
}

bool ChessCtrl::canCastling() const
{
    return false;
}

bool ChessCtrl::emptyByOffset(int x, int y) const
{
//    const int destCol = m_fox.x() + x;
//    const int destRank = m_fox.y() + y;
//    if(destCol < 1 || destRank < 1 || destCol > board()->columns() || destRank > board()->ranks()) return false;
//    return (board()->data(destCol, destRank) == ' ');
}





