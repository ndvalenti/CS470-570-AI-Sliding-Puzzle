// Nick Valenti
// CS 470/570 AI
// Assignment 1 Part 2
// search.cpp

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <list>
#include <windows.h>
#include "slideboard.h"
#include "search.h"

void solveBF(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting Breadth-First Open List Search\n";

    std::list<slideBoard*> BFQueue;
    slideBoard *curr = new slideBoard(original);

    BFQueue.emplace_front(curr);
    auto it = BFQueue.begin();
    curr = *it;

    int32_t j = 0;

    while (!curr->equals()){
        j++;
        for (int i = 0; i < 4; i++){
            if (curr->moves[i] >= 0){
                BFQueue.emplace_back(curr->spawn(curr->moves[i]+1));
            }
        }
        it++;
        curr = *it;
    }
    while (curr->parent != NULL){
        path.emplace_back(curr->path);
        curr = curr->parent;
    }
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}

void solveBFC(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting Breadth-First Closed List Search\n";
    std::list<slideBoard*> BFQueue;
    std::list<slideBoard*> Closed;

    slideBoard *curr = new slideBoard(original);
    slideBoard *temp;
    bool exists = false;

    int16_t *comparr = new int16_t[original.getsize()];

    BFQueue.emplace_front(curr);
    auto it = BFQueue.begin();
    curr = *it;

    int32_t j = 0;

    while (!curr->equals()){
        for (int i = 0; i < 4; i++){
            if (curr->moves[i] >= 0){
                exists = false;
                curr->fauxmove(comparr, curr->moves[i]+1);
                for (auto cit = Closed.begin(); cit != Closed.end(); ++cit){
                    if ((*cit)->compare(comparr)){
                        exists = true;
                        break;
                    }
                }
                if (!exists){
                    temp = curr->spawn(curr->moves[i]+1);
                    BFQueue.emplace_back(temp);
                    Closed.emplace_front(temp);
                }
            }
        }
        j++;
        it++;
        curr = *it;
    }
    while (curr->parent != NULL){
        path.emplace_back(curr->path);
        curr = curr->parent;
    }
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes: ";

    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nThe closed list contained " << Closed.size() <<
                 " entries.\n" << std::endl;
}
