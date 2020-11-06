#pragma once

#include "AbstractChessCtrl.h"

namespace Chess
{
    class ChessCtrl : public AbstractChessCtrl
    {
        //types
    public:
        struct Piece
        {
            ChessBoard::PieceMark   pieceMark;
            ChessBoard::Position    position;

            explicit Piece(const ChessBoard::PieceMark m,
                  const ChessBoard::Position p):
                pieceMark(m),
                position(p)
            {}
            ~Piece()
            {}
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

    protected:
        bool pieceCanMove() const;
        bool emptyByOffset(int x, int y) const;

    private:
        Piece   _piece;
    };
}
