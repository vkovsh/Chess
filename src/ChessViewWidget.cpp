#include <QPainter>

#include "ChessViewWidget.h"

#include <QRgb>
#include <QMouseEvent>
#include <QDebug>

using namespace Chess;

QSize ChessViewWidget::sizeHint() const
{
    if (_chessBoard == NULL)
    {
        return QSize(50, 50);
    }

    QSize boardSize(getFieldSize().height() * _chessBoard->ranksCount() + 1,
                    getFieldSize().width() * _chessBoard->columnsCount() + 1);

    // 'M' is the widest letter
    int rankSize = fontMetrics().horizontalAdvance('M') + 4;
    int columnSize = fontMetrics().height() + 4;
    return boardSize + QSize(rankSize, columnSize);
}

void ChessViewWidget::setChessBoard(ChessBoard* chessBoard)
{
    if (_chessBoard == chessBoard)
    {
        return;
    }

    if (_chessBoard)
    {
        // disconnect all signal-slot connections between m_board and this
        _chessBoard->disconnect(this);
    }

    _chessBoard = chessBoard;

    // connect signals
    if (chessBoard)
    {
        connect(chessBoard, SIGNAL(dataChanged(Position)), this,  SLOT(update()));
        connect(chessBoard, SIGNAL(boardReset()), this, SLOT(update()));
    }
    updateGeometry();
}

ChessBoard* ChessViewWidget::getChessBoard() const
{
    return _chessBoard;
}

QRect ChessViewWidget::getFieldRect(int rank, int column) const
{
    if (_chessBoard == NULL)
    {
        return QRect();
    }

    const QSize fs = getFieldSize();
    QPoint topLeft(column * fs.width(), (ChessBoard::RANK_EIGHT - rank) * fs.height());
    QRect fRect = QRect(topLeft, fs);

    // offset rect by rank symbols
    int offset = fontMetrics().horizontalAdvance('M');
    return fRect.translated(offset + 4, 0);
}

void ChessViewWidget::drawRow(QPainter *painter, int row)
{
    QRect r = getFieldRect(row, 0);
    QRect rankRect = QRect(0, r.top(), r.left(), r.height()).adjusted(2, 0, -2, 0);
    QString rankText = QString::number(row + 1);
    QFont f;
    f.setBold(true);
    painter->setFont(f);
    painter->drawText(rankRect, Qt::AlignVCenter | Qt::AlignRight, rankText);
}

void ChessViewWidget::drawColumn(QPainter *painter, int column)
{
    QRect r = getFieldRect(0, column - 1);
    QRect columnRect = QRect(r.left(), r.bottom(), r.width(), height() - r.bottom()).adjusted(0, 2, 0, -2);
    QFont f;
    f.setBold(true);
    painter->setFont(f);
    painter->drawText(columnRect, Qt::AlignHCenter | Qt::AlignTop, QChar('a' + column - 1));
}

void ChessViewWidget::drawField(QPainter *painter, int row, int column)
{
    QRect rect = getFieldRect(row, column);
    QColor fillColor = (column + row) % 2 ?
                QColor(QRgb(LIGHT_FIELD_COLOR)) : QColor(QRgb(DARK_FIELD_COLOR));
    painter->setPen(palette().color(QPalette::Dark));
    painter->setBrush(fillColor);
    painter->drawRect(rect);
}

void ChessViewWidget::paintEvent(QPaintEvent *)
{
    if (_chessBoard == NULL)
    {
        return;
    }

    QPainter painter(this);
    int rowCount = _chessBoard->ranksCount();
    for (int r = 0; r < rowCount; ++r)
    {
        painter.save();
        drawRow(&painter, r);
        painter.restore();
    }

    int columnCount = _chessBoard->columnsCount();
    for (int c = 0; c <= columnCount; ++c)
    {
        painter.save();
        drawColumn(&painter, c);
        painter.restore();
    }

    for (int r = 0; r < rowCount; ++r)
    {
        for(int c = 0; c < columnCount; ++c)
        {
            painter.save();
            drawField(&painter, r, c);
            painter.restore();
        }
    }

    drawHighlights(&painter);

    for(int r = 0; r < rowCount; ++r)
    {
        for(int c = 0; c < columnCount; ++c)
        {
            drawPiece(&painter, r, c);
        }
    }
}

void ChessViewWidget::drawPiece(QPainter *painter, int rank, int column)
{
    QRect rect = getFieldRect(rank, column);
    ChessBoard::PieceMark value =
            _chessBoard->getData(ChessBoard::Position((ChessBoard::Rank)rank, (ChessBoard::Column)column));
    if (value != ChessBoard::EMPTY_FIELD_MARK)
    {
        QIcon icon = getPiece(value);
        if (false == icon.isNull())
        {
            icon.paint(painter, rect, Qt::AlignCenter);
        }
    }
}

void ChessViewWidget::setPiece(ChessBoard::PieceMark type, const QIcon &icon)
{
    _pieces.insert(type, icon);
    update();
}

QIcon ChessViewWidget::getPiece(ChessBoard::PieceMark type) const
{
    return _pieces.value(type, QIcon());
}

QPoint ChessViewWidget::fieldAt(const QPoint &pt) const
{
    if (_chessBoard == NULL)
    {
        return QPoint();
    }

    const QSize fs = getFieldSize();
    // 'M' is the widest letter
    int offset = fontMetrics().horizontalAdvance('M') + 4;
    if(pt.x() < offset)
    {
        return QPoint();
    }
    int c = (pt.x() - offset) / fs.width();
    int r = pt.y() / fs.height();
    if(c < 0 || c >= _chessBoard->columnsCount() ||
       r < 0 || r >= _chessBoard->ranksCount())
    {
        return QPoint();
    }
    // max rank - r
    return QPoint(c + 1, _chessBoard->ranksCount() - r);
}

void ChessViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = fieldAt(event->pos());
    pt.setX(pt.x() - 1);
    pt.setY(pt.y() - 1);
    if(pt == QPoint(-1, -1))
    {
        return;
    }
    qDebug() << "mouseReleaseEvent";
    emit clicked(pt);
}

void ChessViewWidget::addHighlight(ChessViewWidget::Highlight *hl)
{
    _highlights.append(hl);
    update();
}

void ChessViewWidget::removeHighlight(ChessViewWidget::Highlight *hl)
{
    _highlights.removeOne(hl);
    update();
}

void ChessViewWidget::drawHighlights(QPainter *painter)
{
    for(int idx = 0; idx < highlightCount(); ++idx) {
        Highlight *hl = highlight(idx);
        if(hl->type() == FieldHighlight::Type) {
            FieldHighlight *fhl = static_cast<FieldHighlight*>(hl);
            QRect rect = getFieldRect(fhl->rank(), fhl->column());
            painter->fillRect(rect, fhl->color());
        }
    }
}
