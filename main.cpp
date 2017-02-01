#include <QCoreApplication>
#include <iostream>

#include "slideboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    slideBoard test;
    test.print();
    return a.exec();
}
