#pragma once

#include "AbstractChessCtrl.h"

namespace Chess
{
    class ChessCtrl : public AbstractChessCtrl
    {
        //types
    public:
        struct PieceMove
        {
            ChessBoard::PieceMark   pieceMark;
            ChessBoard::Position    positionFrom;
            ChessBoard::Position    positionTo;

            explicit PieceMove(const ChessBoard::PieceMark m,
                  const ChessBoard::Position& from,
                  const ChessBoard::Position& to):
                pieceMark(m),
                positionFrom(from),
                positionTo(to)
            {}
            ~PieceMove()
            {}
        };

        struct PlayerData
        {

        };

        //constructors and destructors
    public:
        ChessCtrl(QObject *parent = 0);
        ~ChessCtrl();

        //methods
    public:
        void newGame() override;
        bool move(const ChessBoard::Position& from,
                  const ChessBoard::Position& to) override;

    signals:
        void    promotePawn();

    protected:
        //can  move
        bool pieceCanMove() const;
        bool kingCanMove() const;
        bool queenCanMove() const;
        bool rookCanMove() const;
        bool bishopCanMove() const;
        bool knightCanMove() const;
        bool pawnCanMove() const;

        bool canCastling() const;
        void castling();

        bool isCheck(ChessBoard::Position position) const;
        bool isCheckmate() const;
        bool isStalemate() const;
        bool emptyByOffset(int x, int y) const;

    private:
        PieceMove   _pieceMove;

        bool    _whiteKingMoved;
        bool    _whiteLeftRookMoved;
        bool    _whiteRightRookMoved;

        bool    _blackKingMoved;
        bool    _blackLeftRookMoved;
        bool    _blackRightRookMoved;
    };
}
