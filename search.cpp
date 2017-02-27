// Nick Valenti
// CS 470/570 AI
// Assignment 1 Part 2
// search.cpp

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <windows.h>
#include "slideboard.h"
#include "search.h"

void solveBF(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting Breadth-First Search\n";

    std::list<slideBoard*> BFQueue;
    slideBoard *curr = new slideBoard(original);

    BFQueue.emplace_front(curr);
    auto it = BFQueue.begin();
    curr = *it;

    int32_t j = 0; // Tracks nodes touched

    while (!curr->equals()){
        j++;
            // Places all valid moves in the queue
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
                 " steps after analyzing " << j << " nodes. Moves to found solution: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}

void solveBFC(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting Breadth-First Search With a Closed List\n";
    std::list<slideBoard*> BFQueue;
    std::list<slideBoard*> Closed;

    slideBoard *curr = new slideBoard(original);
    slideBoard *temp;
    bool exists = false;

    // This array is used for quick boolean board comparisons
    int16_t *comparr = new int16_t[original.getsize()];

    BFQueue.emplace_front(curr);
    auto it = BFQueue.begin();
    curr = *it;

    int32_t j = 0;

        // While not in a solution state continue dequeuing and checking nodes
    while (!curr->equals()){
        j++;
        for (int i = 0; i < 4; i++){
            if (curr->moves[i] >= 0){
                exists = false;
                curr->fauxmove(comparr, curr->moves[i]+1);
                    // Compares the proposed move to the closed list
                for (auto cit = Closed.begin(); cit != Closed.end(); ++cit){
                    if ((*cit)->compare(comparr)){
                        exists = true;
                        break;
                    }
                }
                    // If this is a new node add to both lists
                if (!exists){
                    temp = curr->spawn(curr->moves[i]+1);
                    BFQueue.emplace_back(temp);
                    Closed.emplace_front(temp);
                }
            }
        }
        // auto it keeps track of current place in the list without deallocating memory
        it++;
        curr = *it;
    }
    while (curr->parent != NULL){
        path.emplace_back(curr->path);
        curr = curr->parent;
    }
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes. Moves to found solution: ";

    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nThe closed list contained " << Closed.size() <<
                 " entries.\n" << std::endl;
}

void solveDFS(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting Depth-First Search\n";
    std::list<slideBoard*> DFStack;
    std::list<slideBoard*> Closed;

    slideBoard *curr = new slideBoard(original);
    slideBoard *temp;
    int32_t j = 0;
    int16_t *comparr = new int16_t[original.getsize()];

    DFStack.emplace_front(curr);

    auto it = DFStack.begin();

    while (!curr->equals()){
        j++;
        (*it) = curr;
        for (int i = 0; i < 4; i++){
            if (curr->moves[i] >= 0){
                bool exists = false;
                curr->fauxmove(comparr, curr->moves[i]+1);
                for (auto cit = Closed.begin(); cit != Closed.end(); ++cit){
                    if ((*cit)->compare(comparr)){
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                        // If not on the closed list here is where children are added to stack
                    temp = curr->spawn(curr->moves[i]+1);
                    DFStack.emplace_front(temp);
                    //Closed.emplace_front(temp);
                }
            }
        }
            // pop the element that was just processed off the stack...in a roundabout way
        DFStack.remove(*it);
        curr = DFStack.front();
    }

    while (curr->parent != NULL) {
        path.emplace_back(curr->path);
        curr = curr->parent;
    }
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes. Press any key for solution.\n";

    std::cout << "\nThe closed list contained " << Closed.size() <<
                 " entries.\n" << std::endl;

}

void solveIDA(slideBoard &original, std::vector<int16_t> &path)
{
    std::cout << "Starting IDA* Search\n";
    std::list<slideBoard> DFStack;
    std::list<slideBoard> Closed;

    slideBoard *temp;
    int16_t *comparr = new int16_t[original.getsize()];

    original.setFitness3();
    int32_t maxfitness = original.getFitness();
    int32_t j = 0;
    int32_t minexcess = original.getFitness();
    bool changes, solved = false, exists = false;

    DFStack.emplace_front(original);

    while (!DFStack.front().equals()){
        changes = false;
        j++;
        auto it = DFStack.begin();

        for (int i = 0; i < 4; i++){
            if ((*it).moves[i] >= 0){
                exists = false;
                (*it).fauxmove(comparr, (*it).moves[i]+1);
                    // Compares the proposed move to the closed list

                for (auto cit = Closed.begin(); cit != Closed.end(); ++cit){
                    if ((*cit).compare(comparr)){
                        exists = true;
                        break;
                    }
                }

                    // If this is a new node add to both lists
                if (!exists){
                    changes = true;
                    temp = (*it).spawn((*it).moves[i]+1);
                    temp->setFitness2();
                    if (temp->getFitness() < maxfitness){
                        DFStack.emplace_front(*temp);
                        Closed.emplace_front(*temp);
                        if (DFStack.front().equals()){
                            // Don't bother continuing if we've just pushed the solution
                            solved = true;
                            break;
                        }
                    } else if (temp->getFitness() != maxfitness){
                        if (minexcess == -1){
                            minexcess = temp->getFitness() - maxfitness;
                        } else if (temp->getFitness() - maxfitness < minexcess){
                            minexcess = temp->getFitness() - maxfitness;
                        }
                    }
                    delete temp;
                }
            }
        }
        if (!solved) {

            DFStack.erase(it);

            // Here we increase fitness if we have exhaused our current stack
            if (DFStack.size() == 0) {
                if (minexcess == -1)
                    minexcess = 1;
                maxfitness += minexcess;
                minexcess = -1;
                std::cout << "Fitness: " << maxfitness << std::endl;
                DFStack.clear();
                Closed.clear();
                DFStack.emplace_front(original);
            }
        }
    }


    temp = &DFStack.front();
    std::cout << "\nSolution found in " << temp->step <<
                 " steps after analyzing " << j << " nodes.\n";

    std::cout << "\nThe closed list contained " << Closed.size() <<
                 " entries.\n" << std::endl;
}

void solveID(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting Iterative Deepening Search\n";
    std::list<slideBoard> DFStack;

    slideBoard *temp;
    // This vector contains the number of nodes at [index] level to assist depth tracking
    // with an inconsistant branching factor
    std::vector<int16_t> currnodes;

    int16_t currdepth = 0;
    int16_t maxdepth = 1;
    currnodes.assign(maxdepth+1,0);
    currnodes[0] = 1;
    int32_t j = 0;
    bool changes, solved = false;

    DFStack.emplace_front(original);

    while (!DFStack.front().equals()){
        currnodes[currdepth]--;
        changes = false;
        j++;
        auto it = DFStack.begin();

        if (currdepth < maxdepth){
            for (int i = 0; i < 4; i++){
                if ((*it).moves[i] >= 0){
                    bool exists = false;
                    if (!exists) {
                        changes = true;
                        currnodes[currdepth+1]++;
                        temp = (*it).spawn((*it).moves[i]+1);
                        DFStack.emplace_front(*temp);
                        if (DFStack.front().equals()){
                            // Don't bother continuing if we've just pushed the solution
                            solved = true;
                            break;
                        }
                        delete temp;
                    }
                }
            }
        }
        if (!solved) {
            if (changes) {
                currdepth++;
            } else {
                    // Ensures current depth is correctly adjusted
                while (currdepth > 0 && currnodes[currdepth] == 0){
                    currdepth--;
                    if (DFStack.size() != 0){
                    }
                }
            }

            DFStack.erase(it);

            // Here we increase depth if we have exhaused our current depth
            if (DFStack.size() == 0) {
                currdepth = 0;
                maxdepth++;
                std::cout << "Depth: " << maxdepth << std::endl;
                DFStack.clear();
                currnodes.clear();
                currnodes.assign(maxdepth+1, 0);
                currnodes[0] = 1;
                DFStack.emplace_front(original);
            }
        }
    }


    temp = &DFStack.front();
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes.\n";
    std::cout << "Moves to found solution: ";
}


// Both A* functions are similar
void solveAStarOne(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting A* Search (1)\n";

    std::list<slideBoard*> BFQueue;
    std::list<slideBoard*> Closed;

    slideBoard *curr = new slideBoard(original);
    slideBoard *temp;
    bool exists = false;

    int16_t *comparr = new int16_t[original.getsize()];

    curr->setFitness1();
    BFQueue.emplace_front(curr);
    auto it = BFQueue.begin();
    curr = *it;

    int32_t j = 0;

        // While not in a solution state continue dequeuing and checking nodes
    while (!curr->equals()){
        j++;
        for (int i = 0; i < 4; i++){
            if (curr->moves[i] >= 0){
                exists = false;
                curr->fauxmove(comparr, curr->moves[i]+1);
                    // Compares the proposed move to the closed list
                for (auto cit = Closed.begin(); cit != Closed.end(); ++cit){
                    if ((*cit)->compare(comparr)){
                        exists = true;
                        break;
                    }
                }
                    // If this is a new node add to both lists
                if (!exists){
                    // Computes the fitness of the current node and sorts it accordingly
                    temp = curr->spawn(curr->moves[i]+1);
                    temp->setFitness1();
                    auto ait = BFQueue.begin();

                    for (ait = it; ait != BFQueue.end(); ++ait){
                        if (temp->getFitness() < (*ait)->getFitness()){
                            break;
                        }
                    }
                    BFQueue.insert(ait, temp);

                    if (ait == it){
                        it--;
                        it--;
                    }

                    Closed.emplace_front(temp);
                }
            }
        }
        // auto it keeps track of current place in the list without deallocating memory
        it++;
        curr = *it;
    }
    while (curr->parent != NULL){
        path.emplace_back(curr->path);
        curr = curr->parent;
    }
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes. Moves to found solution: ";

    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nThe closed list contained " << Closed.size() <<
                 " entries.\n" << std::endl;
}

void solveAStarTwo(slideBoard &original, std::vector<int16_t> &path){
    std::cout << "Starting A* Search (2)\n";

    std::list<slideBoard*> BFQueue;
    std::list<slideBoard*> Closed;

    slideBoard *curr = new slideBoard(original);
    slideBoard *temp;
    bool exists = false;

    int16_t *comparr = new int16_t[original.getsize()];

    curr->setFitness2();
    BFQueue.emplace_front(curr);
    auto it = BFQueue.begin();
    curr = *it;

    int32_t j = 0;

        // While not in a solution state continue dequeuing and checking nodes
    while (!curr->equals()){
        j++;
        for (int i = 0; i < 4; i++){
            if (curr->moves[i] >= 0){
                exists = false;
                curr->fauxmove(comparr, curr->moves[i]+1);
                    // Compares the proposed move to the closed list
                for (auto cit = Closed.begin(); cit != Closed.end(); ++cit){
                    if ((*cit)->compare(comparr)){
                        exists = true;
                        break;
                    }
                }
                    // If this is a new node add to both lists
                if (!exists){
                    temp = curr->spawn(curr->moves[i]+1);
                    temp->setFitness2();

                    auto ait = BFQueue.begin();
                    std::cout << "Fit: " << temp->getFitness() << ", " << curr->moves[i]+1 << std::endl;
                    for (ait = it; ait != BFQueue.end(); ++ait){
                        if (temp->getFitness() < (*ait)->getFitness()){
                            break;
                        }
                    }
                    BFQueue.insert(ait, temp);

                    if (ait == it){
                        it--;
                        it--;
                    }

                    std::cin.ignore();

                    Closed.emplace_front(temp);
                }
            }
        }
        for (auto tit = it; tit != BFQueue.end(); ++tit){
            std::cout << (*tit)->getFitness() << " ";
        }
        std::cout << "break\n";
        it++;
        curr = *it;
    }
    while (curr->parent != NULL){
        path.emplace_back(curr->path);
        curr = curr->parent;
    }
    std::cout << "\nSolution found in " << path.size() <<
                 " steps after analyzing " << j << " nodes. Moves to found solution: ";

    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nThe closed list contained " << Closed.size() <<
                 " entries.\n" << std::endl;
}
