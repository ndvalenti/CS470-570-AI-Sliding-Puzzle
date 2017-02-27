// Nick Valenti
// CS 470/570 AI
// Assignment 1 Part 2
// main.cpp

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <list>
#include <windows.h>

#include "search.h"
#include "slideboard.h"


int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    std::vector<int16_t> path;

    std::cout << "Solving 10 n-puzzles of size 3 after 300 random LEGAL moves:\n\n";
    //for (int i = 1; i <= 10; i++){
        //std::cout << "\nAttempt " << i << std::endl;
        slideBoard test(4);
        //test.randomize1();
        test.randomize();
        test.print();
        //solveBFC(test, path);
        //path.clear();
        //solveAStarTwo(test,path);
        solveIDA(test, path);
        path.clear();
        Sleep(1000);
    //}
    return a.exec();
}

