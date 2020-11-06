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
        Q_PROPERTY(Player currentPlayer
                   READ getCurrentPlayer
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

        enum Player
        {
            NoPlayer = -1,
            Player1 = 0,
            Player2 = 2
        };
        Q_ENUM(Player)

        //constructors and destructors
    public:
        AbstractChessCtrl(QObject* parent = NULL);
        virtual ~AbstractChessCtrl() = 0;

        //getters and setters
    public:
        ChessBoard* getBoard() const;
        inline Result getResult() const { return _result; }
        inline Player getCurrentPlayer() const { return _currentPlayer; }

    public slots:
        virtual void newGame();
        virtual bool move(const ChessBoard::Position& from,
                          const ChessBoard::Position& to);

    signals:
        void boardChanged(ChessBoard*);
        void gameOver(Result);
        void currentPlayerChanged(Player);

    protected:
        virtual void setupBoard();
        void setBoard(ChessBoard *board);
        void setResult(Result);
        void setCurrentPlayer(Player);

    private:
        Result  _result;
        Player  _currentPlayer;
        ChessBoard* _chessBoard;
    };
}
