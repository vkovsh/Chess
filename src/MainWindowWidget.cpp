#include "MainWindowWidget.h"

#include <QHBoxLayout>

using namespace Chess;

MainWindowWidget::MainWindowWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _clickPoint(QPoint(-1, -1)),
    _selectedField(NULL)
{
    ui->setupUi(this);
    _view = new ChessViewWidget;
    {
        _view->setPiece(ChessBoard::PieceMark('P'), QIcon(":/icons/white_pawn.png")); // pawn
        _view->setPiece(ChessBoard::PieceMark('K'), QIcon(":/icons/white_king.png")); // king
        _view->setPiece(ChessBoard::PieceMark('Q'), QIcon(":/icons/white_queen.png")); // queen
        _view->setPiece(ChessBoard::PieceMark('R'), QIcon(":/icons/white_rook.png")); // rook
        _view->setPiece(ChessBoard::PieceMark('N'), QIcon(":/icons/white_knight.png")); // knight
        _view->setPiece(ChessBoard::PieceMark('B'), QIcon(":/icons/white_bishop.png")); // bishop
    }

    {
        _view->setPiece(ChessBoard::PieceMark('p'), QIcon(":/icons/black_pawn.png")); // pawn
        _view->setPiece(ChessBoard::PieceMark('k'), QIcon(":/icons/black_king.png")); // king
        _view->setPiece(ChessBoard::PieceMark('q'), QIcon(":/icons/black_queen.png")); // queen
        _view->setPiece(ChessBoard::PieceMark('r'), QIcon(":/icons/black_rook.png")); // rook
        _view->setPiece(ChessBoard::PieceMark('n'), QIcon(":/icons/black_knight.png")); // knight
        _view->setPiece(ChessBoard::PieceMark('b'), QIcon(":/icons/black_bishop.png")); // bishop
    }

    _ctrl = new ChessCtrl(this);
    _ctrl->newGame();
    _view->setChessBoard(_ctrl->getBoard());
    setCentralWidget(_view);
    _view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _view->setFieldSize(QSize(100, 100));
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(_view, &ChessViewWidget::clicked, this, &MainWindowWidget::viewClicked);
}

void MainWindowWidget::viewClicked(const QPoint &field)
{
    if (_clickPoint == QPoint(-1, -1))
    {
        ChessBoard::Position clickPos(static_cast<ChessBoard::Rank>(field.y()),
                                     static_cast<ChessBoard::Column>(field.x()));
        if(_view->getChessBoard()->getData(clickPos) != ChessBoard::EMPTY_FIELD_MARK)
        {
            _clickPoint = field;
            _selectedField = new ChessViewWidget::FieldHighlight(
                        field.y(), field.x(), QColor(0xc9, 0xa0, 0xdc, 150));
            _view->addHighlight(_selectedField);
        }
    }
    else
    {
        if (field != _clickPoint)
        {
            ChessBoard::Position fromPos(static_cast<ChessBoard::Rank>(_clickPoint.y()),
                                         static_cast<ChessBoard::Column>(_clickPoint.x()));
            ChessBoard::Position toPos(static_cast<ChessBoard::Rank>(field.y()),
                                         static_cast<ChessBoard::Column>(field.x()));

            _view->getChessBoard()->movePiece(fromPos, toPos);
        }
        _clickPoint = QPoint(-1, -1);
        _view->removeHighlight(_selectedField);
        delete _selectedField;
        _selectedField = nullptr;
    }
}
