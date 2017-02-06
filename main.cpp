#include <QCoreApplication>
#include <iostream>

#include "slideboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    slideBoard test;

    std::cout << "This is a sliding puzzle game.\n";
    std::cout << "Move the tiles so recreate this pattern: \n";

    test.print();

    std::cout << "Good luck!\n\n" << std::flush;

    test.play();
    return a.exec();
}
