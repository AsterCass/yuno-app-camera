
#include "index_widget.h"

#include <QApplication>
#include <QDebug>
#include <QGraphicsView>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    IndexWidget  w;

    w.show();

    return app.exec();
}
