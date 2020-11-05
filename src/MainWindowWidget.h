#pragma once

#include <QWidget>

#include "ChessViewWidget.h"
#include "ChessCtrl.h"

namespace Chess
{
    class MainWindowWidget : public QWidget
    {
        Q_OBJECT

    public:
        MainWindowWidget(QWidget* parent = NULL);

    private slots:
        void viewClicked(const QPoint &field);

    private:
        QWidget*    _parent;
        ChessViewWidget*  _view;
        ChessCtrl* _ctrl;
        QPoint  _clickPoint;
        ChessViewWidget::FieldHighlight* _selectedField;
    };
}
