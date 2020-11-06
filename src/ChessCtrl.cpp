#include "ChessCtrl.h"

using namespace Chess;

ChessCtrl::ChessCtrl(QObject *parent):
    AbstractChessCtrl(parent),
    _pieceMove(ChessBoard::EMPTY_FIELD_MARK,
           ChessBoard::Position(ChessBoard::RANK_UNDEFINED,
                                ChessBoard::COLUMN_UNDEFINED),
           ChessBoard::Position(ChessBoard::RANK_UNDEFINED,
                                ChessBoard::COLUMN_UNDEFINED)),
    _whiteKingMoved(false),
    _whiteLeftRookMoved(false),
    _whiteRightRookMoved(false),
    _blackKingMoved(false),
    _blackLeftRookMoved(false),
    _blackRightRookMoved(false)
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

    _pieceMove = PieceMove(source, from, to);
    if (pieceCanMove() == false)
    {
        return false;
    }
    //move piece
    getBoard()->movePiece(from, to);

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

bool ChessCtrl::isCheck(ChessBoard::Position position) const
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
    switch (_pieceMove.pieceMark)
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
    //check is move legal
    {
        //normal king move
        int diff = _pieceMove.positionFrom.rank -
                _pieceMove.positionTo.rank +
                _pieceMove.positionFrom.column -
                _pieceMove.positionTo.column;
        if (false == (diff == 0 || diff == 1 || diff == -1))
        {
            if (canCastling() == true)
            {

            }
            return false;
        }
    }
    //check on friendly fire
    ChessBoard::PieceMark dest =
            getBoard()->getData(_pieceMove.positionTo);
    if (_pieceMove.pieceMark == ChessBoard::WHITE_KING_MARK)
    {
        if (dest == ChessBoard::WHITE_QUEEN_MARK ||
            dest == ChessBoard::WHITE_ROOK_MARK ||
            dest == ChessBoard::WHITE_BISHOP_MARK ||
            dest == ChessBoard::WHITE_KNIGHT_MARK ||
            dest == ChessBoard::WHITE_PAWN_MARK)
        {
            return false;
        }
    }
    else
    {
        if (dest == ChessBoard::BLACK_QUEEN_MARK ||
            dest == ChessBoard::BLACK_ROOK_MARK ||
            dest == ChessBoard::BLACK_BISHOP_MARK ||
            dest == ChessBoard::BLACK_KNIGHT_MARK ||
            dest == ChessBoard::BLACK_PAWN_MARK)
        {
            return false;
        }
    }
    return true;
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
    //king is checked in current position and on potential castling path
    if (false == isCheck(_pieceMove.positionFrom))
    {
        ChessBoard::Position checkPos = _pieceMove.positionFrom;
        if (_pieceMove.positionTo.column < _pieceMove.positionFrom.column)
        {
            checkPos.decColumn();
            if (isCheck(checkPos) == true)
            {
                return false;
            }
            checkPos.decColumn();
            if (isCheck(checkPos) == true)
            {
                return false;
            }
        }
        else
        {
            checkPos.incColumn();
            if (isCheck(checkPos) == true)
            {
                return false;
            }
            checkPos.incColumn();
            if (isCheck(checkPos) == true)
            {
                return false;
            }
        }
    }

    if (getCurrentPlayerID() == Player1)
    {
        if (_whiteKingMoved == true)
        {
            return false;
        }
        else
        {
            const ChessBoard::Position
                    LEFT_ROOK_START_POS(ChessBoard::RANK_ONE, ChessBoard::COLUMN_A);
            const ChessBoard::Position
                    RIGHT_ROOK_START_POS(ChessBoard::RANK_ONE, ChessBoard::COLUMN_H);
            const ChessBoard::Position
                    LEFT_CASTLING_KING_POS(ChessBoard::RANK_ONE, ChessBoard::COLUMN_C);
            const ChessBoard::Position
                    RIGHT_CASTLING_KING_POS(ChessBoard::RANK_ONE, ChessBoard::COLUMN_G);
            if (LEFT_CASTLING_KING_POS == _pieceMove.positionTo && _whiteLeftRookMoved == false)
            {
                //check space between king and rook
                for (int c = _pieceMove.positionFrom.column - 1; c != ChessBoard::COLUMN_A; --c)
                {
                    ChessBoard::Position
                            pos(ChessBoard::RANK_ONE, static_cast<ChessBoard::Column>(c));
                    if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
                    {
                        return false;
                    }
                }
                return true;
            }
            if (RIGHT_CASTLING_KING_POS == _pieceMove.positionTo && _whiteRightRookMoved == false)
            {
                //check space between king and rook
                for (int c = _pieceMove.positionFrom.column + 1; c != ChessBoard::COLUMN_H; ++c)
                {
                    ChessBoard::Position
                            pos(ChessBoard::RANK_ONE, static_cast<ChessBoard::Column>(c));
                    if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    else if (getCurrentPlayerID() == Player2)
    {
        if (_blackKingMoved == true)
        {
            return false;
        }
        else
        {
            const ChessBoard::Position
                    LEFT_ROOK_START_POS(ChessBoard::RANK_EIGHT, ChessBoard::COLUMN_A);
            const ChessBoard::Position
                    RIGHT_ROOK_START_POS(ChessBoard::RANK_EIGHT, ChessBoard::COLUMN_H);
            const ChessBoard::Position
                    LEFT_CASTLING_KING_POS(ChessBoard::RANK_EIGHT, ChessBoard::COLUMN_C);
            const ChessBoard::Position
                    RIGHT_CASTLING_KING_POS(ChessBoard::RANK_EIGHT, ChessBoard::COLUMN_G);
            if (LEFT_CASTLING_KING_POS == _pieceMove.positionTo && _blackLeftRookMoved == false)
            {
                //check space between king and rook
                for (int c = _pieceMove.positionFrom.column - 1; c != ChessBoard::COLUMN_A; --c)
                {
                    ChessBoard::Position
                            pos(ChessBoard::RANK_EIGHT, static_cast<ChessBoard::Column>(c));
                    if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
                    {
                        return false;
                    }
                }
                return true;
            }
            if (RIGHT_CASTLING_KING_POS == _pieceMove.positionTo && _blackRightRookMoved == false)
            {
                //check space between king and rook
                for (int c = _pieceMove.positionFrom.column + 1; c != ChessBoard::COLUMN_H; ++c)
                {
                    ChessBoard::Position
                            pos(ChessBoard::RANK_EIGHT, static_cast<ChessBoard::Column>(c));
                    if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

void ChessCtrl::castling()
{
    ChessBoard::PieceMark rook = getBoard()->getData(_pieceMove.positionTo);
//    getBoard()->setData(_pieceMove.positionFrom, rook);
//    getBoard()-setData(_pieceMove.positionTo)
}

bool ChessCtrl::emptyByOffset(int x, int y) const
{
//    const int destCol = m_fox.x() + x;
//    const int destRank = m_fox.y() + y;
//    if(destCol < 1 || destRank < 1 || destCol > board()->columns() || destRank > board()->ranks()) return false;
//    return (board()->data(destCol, destRank) == ' ');
}





