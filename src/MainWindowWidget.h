#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

#include "ChessViewWidget.h"
#include "AbstractChessCtrl.h"

namespace Chess
{
    class MainWindowWidget : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindowWidget(QWidget* parent = NULL);

    protected:
        Ui::MainWindow* ui;

    private slots:
        void viewClicked(const QPoint &field);

    private:
        QWidget*    _parent;
        ChessViewWidget*  _view;
        AbstractChessCtrl* _ctrl;
        QPoint  _clickPoint;
        ChessViewWidget::FieldHighlight* _selectedField;
    };
}
