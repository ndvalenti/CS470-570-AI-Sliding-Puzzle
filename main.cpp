#include <QCoreApplication>
#include <iostream>
#include <queue>

#include "slideboard.h"

void solveBF(slideBoard start);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    slideBoard test;

    std::cout << "This is a sliding puzzle game.\n";
    std::cout << "Move the tiles so recreate this pattern: \n";

    test.print();

    test.randomize();

    test.play();
    std::cout << "Good luck!\n\n" << std::flush;
    solveBF(test);
    //test.play();
    return a.exec();
}

void solveBF(slideBoard original){
    std::queue<slideBoard*> BFQueue;
    slideBoard *temp;
    slideBoard *start = new slideBoard(original);
    BFQueue.push(start);
    while (!temp->equals()){
        temp = BFQueue.front();
        BFQueue.pop();
        for (int i = 0; i < 4; i++){
            if (temp->moves[i] >= 0){

            }
        }
    }
}
