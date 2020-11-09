#pragma once

#include <QObject>
#include <QPointer>

#include "ChessBoard.h"

namespace Chess
{
    class AbstractChessCtrl : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Result result READ getResult)
        Q_PROPERTY(PlayerID currentPlayerID
                   READ getCurrentPlayerID
                   NOTIFY currentPlayerChanged)

        //types
    public:
        enum Result
        {
            NoResult = -1,
            Player1Wins = 0,
            Draw = 1,
            Player2Wins = 2
        };
        Q_ENUM(Result)

        enum PlayerID
        {
            NoPlayer = -1,
            Player1 = 0,
            Player2 = 2
        };
        Q_ENUM(PlayerID)

        //constructors and destructors
    public:
        AbstractChessCtrl(QObject* parent = NULL);
        virtual ~AbstractChessCtrl() = 0;

        //getters and setters
    public:
        ChessBoard* getBoard() const;
        inline Result getResult() const { return _result; }
        inline PlayerID getCurrentPlayerID() const { return _currentPlayerID; }

    public slots:
        virtual void newGame();
        virtual bool move(const ChessBoard::Position& from,
                          const ChessBoard::Position& to);

    signals:
        void boardChanged(ChessBoard*);
        void gameOver(Result);
        void currentPlayerChanged(PlayerID);
        void promotePawn();
        void checkmated();
        void stalemate();

    protected:
        virtual void setupBoard();
        void setBoard(ChessBoard *board);
        void setResult(Result);
        void setCurrentPlayer(PlayerID);

    private:
        Result  _result;
        PlayerID  _currentPlayerID;
        ChessBoard* _chessBoard;
    };
}
