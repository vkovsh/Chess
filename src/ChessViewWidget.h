#pragma once

#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>

#include "ChessBoard.h"

class QPainter;

namespace Chess
{
    class ChessViewWidget : public QWidget
    {
        Q_OBJECT

        Q_PROPERTY(QSize fieldSize
                   READ getFieldSize WRITE setFieldSize
                   NOTIFY fieldSizeChanged)

    public:
        class Highlight
        {
        public:
            Highlight() {}
            virtual ~Highlight() {}
            virtual int type() const { return 0; }
        };

        class FieldHighlight : public Highlight
        {
        public:
            enum { Type = 1 };
            FieldHighlight(int rank, int column, QColor color)
              : _field(column, rank), _color(color) {}
            inline int column() const { return _field.x(); }
            inline int rank() const { return _field.y(); }
            inline QColor color() const { return _color; }
            int type() const { return Type; }

        private:
            QPoint _field;
            QColor _color;
        };
    public:
        void setChessBoard(ChessBoard *chessBoard);
        ChessBoard* getChessBoard() const;

        QPoint fieldAt(const QPoint &pt) const;

        QSize sizeHint() const override;

        QSize getFieldSize() const
        {
            return _fieldSize;
        }

        QRect getFieldRect(int row, int column) const;
        void paintEvent(QPaintEvent *) override;

        void drawColumn(QPainter *painter, int column);
        void drawRow(QPainter *painter, int row);

        void setPiece(ChessBoard::PieceMark type, const QIcon& icon);
        QIcon getPiece(ChessBoard::PieceMark type) const;

        void addHighlight(Highlight *hl);
        void removeHighlight(Highlight *hl);
        inline Highlight *highlight(int index) const
        {
                return _highlights.at(index);
        }
        inline int highlightCount() const
        {
            return _highlights.size();
        }

    public slots:
        void setFieldSize(QSize fieldSize)
        {
            if (_fieldSize == fieldSize)
            {
                return ;
            }
            _fieldSize = fieldSize;
            emit fieldSizeChanged(fieldSize);
            updateGeometry();
        }

    signals:
        void fieldSizeChanged(QSize);
        void clicked(const QPoint &);

    protected:
        virtual void drawField(QPainter *painter, int row, int column);
        virtual void drawPiece(QPainter *painter, int row, int column);
        void mouseReleaseEvent(QMouseEvent *event) override;
        virtual void drawHighlights(QPainter *painter);

    private:
        QPointer<ChessBoard> _chessBoard;
        QSize _fieldSize;
        QMap<ChessBoard::PieceMark, QIcon> _pieces;
        QList<Highlight*> _highlights;

    private:
        static const uint32_t LIGHT_FIELD_COLOR = 0xf7cfa4;
        static const uint32_t DARK_FIELD_COLOR = 0xc88d52;
    };
}
