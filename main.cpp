#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget window;
    window.resize(750,450);
    window.show();
    return app.exec();
}
