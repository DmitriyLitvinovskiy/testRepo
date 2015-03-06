#include "mainunit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainUnit w;
    w.show();

    return a.exec();
}
