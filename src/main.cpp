#include <QApplication>

#include "MainWindowWidget.h"

using namespace Chess;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("CountriesWidget");
    QApplication::setOrganizationName("ozzylogik");

    MainWindowWidget mainWidget;
    mainWidget.show();
    return app.exec();
}
