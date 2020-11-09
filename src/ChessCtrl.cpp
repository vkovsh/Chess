#include <tuple>

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
        if (_pieceMove.pieceMark == ChessBoard::BLACK_KING_MARK ||
                _pieceMove.pieceMark == ChessBoard::WHITE_KING_MARK)
        {
            if (canCastling() == true)
            {
                castling();
                return true;
            }
        }
        return false;
    }
    //move piece
    getBoard()->movePiece(from, to);

    {
        if ((_pieceMove.pieceMark == ChessBoard::BLACK_PAWN_MARK &&
             _pieceMove.positionTo.rank == ChessBoard::RANK_ONE) ||
                (_pieceMove.pieceMark == ChessBoard::WHITE_PAWN_MARK &&
                 _pieceMove.positionTo.rank == ChessBoard::RANK_EIGHT))
        {
            emit promotePawn();
        }
    }

    // check win condition
    {
        if (isStalemate() == true)
        {
            setResult(Draw);
            emit stalemate();
        }
        else if (getCurrentPlayerID() == Player2 && isCheckmate() == true)
        {
            // checkmate to white king
            setResult(Player2Wins);
            emit checkmated();
        }
        else if (getCurrentPlayerID() == Player1 && isCheckmate() == true)
        {
            // checkmate to black king
            setResult(Player1Wins);
            emit checkmated();
        }
        else
        {
            // the other player makes the move now
            setCurrentPlayer(getCurrentPlayerID() == Player1 ? Player2 : Player1);
        }
    }
    return true;
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
        bool canMove = (abs(_pieceMove.positionFrom.rank -
                           _pieceMove.positionTo.rank) <= 1) &&
                (abs(_pieceMove.positionFrom.column -
                     _pieceMove.positionTo.column) <= 1);
        if (canMove == false)
        {
            return false;
        }
    }

    //check on friendly fire
    return friendlyFire(_pieceMove.positionTo) == false;
}

bool ChessCtrl::queenCanMove() const
{
    //check is move legal
    {
        int rankOffset = _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank;
        int columnOffset = _pieceMove.positionTo.column - _pieceMove.positionFrom.column;

        if (((rankOffset != 0 && columnOffset == 0) ||
                (rankOffset == 0 && columnOffset != 0)) == false &&
                abs(rankOffset) != abs(columnOffset))
        {
            // bad position
            return false;
        }
    }

    // check on path is clear
    if (pathIsClear(_pieceMove.positionFrom, _pieceMove.positionTo) == false)
    {
        return false;
    }

    //check on friendly fire
    return friendlyFire(_pieceMove.positionTo) == false;
}

bool ChessCtrl::rookCanMove() const
{
    // check regular condition
    {
        int rankOffset = _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank;
        int columnOffset = _pieceMove.positionTo.column - _pieceMove.positionFrom.column;

        if (((rankOffset != 0 && columnOffset == 0) ||
                (rankOffset == 0 && columnOffset != 0)) == false)
        {
            // bad position
            return false;
        }

        // check on path is clear
        if (pathIsClear(_pieceMove.positionFrom, _pieceMove.positionTo) == false)
        {
            return false;
        }

        //check on friendly fire
        return friendlyFire(_pieceMove.positionTo) == false;
    }
    return false;
}

bool ChessCtrl::bishopCanMove() const
{
    // check regular condition
    {
        int rankOffset = _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank;
        int columnOffset = _pieceMove.positionTo.column - _pieceMove.positionFrom.column;

        if (abs(rankOffset) != abs(columnOffset))
        {
            // bad position
            return false;
        }

        // check on path is clear
        if (pathIsClear(_pieceMove.positionFrom, _pieceMove.positionTo) == false)
        {
            return false;
        }

        //check on friendly fire
        return friendlyFire(_pieceMove.positionTo) == false;
    }
}

bool ChessCtrl::knightCanMove() const
{
    // check regular condition
    {
        int rankOffset = _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank;
        int columnOffset = _pieceMove.positionTo.column - _pieceMove.positionFrom.column;
        if (((rankOffset == -1 && columnOffset == -2) ||
                (rankOffset == -2 && columnOffset == -1) ||
                (rankOffset == -1 && columnOffset == 2) ||
                (rankOffset == -2 && columnOffset == 1) ||
                (rankOffset == 1 && columnOffset == -2) ||
                (rankOffset == 2 && columnOffset == -1) ||
                (rankOffset == 1 && columnOffset == 2) ||
                (rankOffset == 2 && columnOffset == 1)) == false)
        {
            //bad moveTo position
            return false;
        }
        //check on friendly fire
        return friendlyFire(_pieceMove.positionTo) == false;
    }
}

bool ChessCtrl::pawnCanMove() const
{
    // check first move condition
    {
        if ((getCurrentPlayerID() == Player1 &&
             _pieceMove.positionFrom.rank == ChessBoard::RANK_TWO &&
             _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank == 2) ||
                (getCurrentPlayerID() == Player2 &&
                 _pieceMove.positionFrom.rank == ChessBoard::RANK_SEVEN &&
                 _pieceMove.positionFrom.rank - _pieceMove.positionTo.rank == 2))
        {
            // check if obstacle
            if (pathIsClear(_pieceMove.positionFrom, _pieceMove.positionTo) == false)
            {
                return false;
            }
            if (getBoard()->getData(_pieceMove.positionTo) !=
                    ChessBoard::EMPTY_FIELD_MARK)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }

    //check regular move condition
    {
        if (((getCurrentPlayerID() == Player1 &&
             _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank == 1 &&
             _pieceMove.positionTo.column - _pieceMove.positionFrom.column == 0) ||
                (getCurrentPlayerID() == Player2 &&
                 _pieceMove.positionFrom.rank - _pieceMove.positionTo.rank == 1 &&
                 _pieceMove.positionTo.column - _pieceMove.positionFrom.column == 0)) &&
                getBoard()->getData(_pieceMove.positionTo) == ChessBoard::EMPTY_FIELD_MARK)
        {
            return true;
        }
    }

    //combat move condition
    {
        if ((getCurrentPlayerID() == Player1 &&
             _pieceMove.positionTo.rank - _pieceMove.positionFrom.rank == 1 &&
             abs(_pieceMove.positionTo.column - _pieceMove.positionFrom.column) == 1) ||
                (getCurrentPlayerID() == Player2 &&
                 _pieceMove.positionFrom.rank - _pieceMove.positionTo.rank == 1 &&
                 abs(_pieceMove.positionTo.column - _pieceMove.positionFrom.column) == 1))
        {
            if (getBoard()->getData(_pieceMove.positionTo) == ChessBoard::EMPTY_FIELD_MARK)
            {
                return false;
            }

            //check on friendly fire
            return friendlyFire(_pieceMove.positionTo) == false;
        }
    }
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
    ChessBoard::Position rookStartPosition;
    ChessBoard::Position rookFinalPosition;
    //left castling
    if (_pieceMove.positionTo.column < _pieceMove.positionFrom.column)
    {
        rookStartPosition = ChessBoard::Position(_pieceMove.positionTo.rank,
                                                 ChessBoard::COLUMN_A);
        rookFinalPosition = ChessBoard::Position(_pieceMove.positionTo.rank,
                                                 ChessBoard::COLUMN_D);
    }
    //right castling
    else
    {
        rookStartPosition = ChessBoard::Position(_pieceMove.positionTo.rank,
                                                 ChessBoard::COLUMN_H);
        rookFinalPosition = ChessBoard::Position(_pieceMove.positionTo.rank,
                                                 ChessBoard::COLUMN_F);

    }
    getBoard()->movePiece(rookStartPosition, rookFinalPosition);
    getBoard()->movePiece(_pieceMove.positionFrom, _pieceMove.positionTo);
    if (getCurrentPlayerID() == Player1)
    {
        _whiteKingMoved = true;
        _whiteLeftRookMoved = true;
        _whiteRightRookMoved = true;
    }
    else
    {
        _blackKingMoved = true;
        _blackLeftRookMoved = true;
        _blackRightRookMoved = true;
    }
}

bool ChessCtrl::pathIsClear(const ChessBoard::Position &from,
                            const ChessBoard::Position &to) const
{
    if (from.column == to.column)
    {
        int delta = (to.rank - from.rank < 0) ? -1 : 1;
        for (int rank = from.rank + delta; rank != to.rank; rank+=delta)
        {
            ChessBoard::Position pos(static_cast<ChessBoard::Rank>(rank), to.column);
            if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
            {
                // find obstacle
                return false;
            }
        }
    }
    else if (from.rank == to.rank)
    {
        int delta = (to.column - from.column < 0) ? -1 : 1;
        for (int column = from.column + delta; column != to.column; column+=delta)
        {
            ChessBoard::Position pos(to.rank, static_cast<ChessBoard::Column>(column));
            if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
            {
                // find obstacle
                return false;
            }
        }
    }
    else if (abs(from.rank - to.rank) == abs(from.column - to.column))
    {
        int deltaRank = (to.rank - from.rank < 0) ? -1 : 1;
        int deltaCol = (to.column - from.column < 0) ? -1 : 1;
        for (auto [rank, column] = std::make_tuple(from.rank + deltaRank, from.column + deltaCol);
             rank != to.rank;
             rank += deltaRank, column += deltaCol)
        {
            ChessBoard::Position pos(static_cast<ChessBoard::Rank>(rank),
                                     static_cast<ChessBoard::Column>(column));
            if (getBoard()->getData(pos) != ChessBoard::EMPTY_FIELD_MARK)
            {
                // find obstacle
                return false;
            }
        }
    }
    return true;
}

bool ChessCtrl::friendlyFire(const ChessBoard::Position &to) const
{
    //check on friendly fire
    ChessBoard::PieceMark dest = getBoard()->getData(to);
    if (getCurrentPlayerID() == Player1)
    {
        if (dest == ChessBoard::WHITE_KING_MARK ||
                dest == ChessBoard::WHITE_QUEEN_MARK ||
                dest == ChessBoard::WHITE_ROOK_MARK ||
                dest == ChessBoard::WHITE_BISHOP_MARK ||
                dest == ChessBoard::WHITE_PAWN_MARK ||
                dest == ChessBoard::WHITE_KNIGHT_MARK)
        {
            return true;
        }
    }
    else if (getCurrentPlayerID() == Player2)
    {
        if (dest == ChessBoard::BLACK_KING_MARK ||
                dest == ChessBoard::BLACK_QUEEN_MARK ||
                dest == ChessBoard::BLACK_ROOK_MARK ||
                dest == ChessBoard::BLACK_BISHOP_MARK ||
                dest == ChessBoard::BLACK_PAWN_MARK ||
                dest == ChessBoard::BLACK_KNIGHT_MARK)
        {
            return true;
        }
    }
    return false;
}
