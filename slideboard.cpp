// Nick Valenti
// CS 470/570 AI
// Assignment 1 Part 2
// slideboard.cpp

#include "slideboard.h"
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iterator>

slideBoard::slideBoard() : WIDTH(3)
{
    initializeBoard();
}

slideBoard::slideBoard(int32_t x) : WIDTH(x)
{
    initializeBoard();
}

slideBoard::slideBoard(slideBoard &temp) : WIDTH(temp.WIDTH)
{
    initializeBoard(temp);
}

void slideBoard::initializeBoard()
{
    size = WIDTH * WIDTH;
    srand(time(NULL));
    int16_t count = 0;
    emptyPos = 0;
    parent = NULL;
    step = 0;

    gameboard = new board();

    gameboard->tile = new int16_t[size];

    for (int i = 0; i < size; i++) {
        gameboard->tile[i] = count;
        count++;
    }
    setMoves();
}

void slideBoard::initializeBoard(slideBoard &temp)
{
    size = WIDTH * WIDTH;
    srand(time(NULL));
    emptyPos = temp.emptyPos;
    parent = temp.parent;
    path = temp.path;
    fitness = temp.fitness;
    gameboard = new board();
    step = temp.step;

    gameboard->tile = new int16_t[size];

    for (int i = 0; i < size; i++) {
        gameboard->tile[i] = temp.gameboard->tile[i];
    }
    setMoves();
}

void slideBoard::print() {
    for (int i = 0; i < size; i++){
        if (i % WIDTH == 0){
            std::cout << "\n";
        }
        if (gameboard->tile[i] != 0) {
            std::cout << std::left << std::setw(3) << gameboard->tile[i];
        } else {
            std::cout << "   ";
        }
    }
    std::cout << "\n\n";
}

void slideBoard::setMoves()
{
    if (emptyPos - WIDTH >= 0){
        moves[0] = emptyPos - WIDTH;
    } else {
        moves[0] = -1;
    }
    if ((emptyPos + 1) % WIDTH != 0) {
        moves[1] = emptyPos + 1;
    } else {
        moves[1] = -1;
    }
    if ((emptyPos + WIDTH) < (size)) {
        moves[2] = emptyPos + WIDTH;
    } else {
        moves[2] = -1;
    }
    if (emptyPos % WIDTH != 0) {
        moves[3] = emptyPos - 1;
    } else {
        moves[3] = -1;
    }
}

void slideBoard::getMoves()
{
    std::cout << "\nValid moves: ";
    for (int i = 0; i < 4; i++){
        if (moves[i] >= 0){
            std::cout << moves[i] + 1 << " ";
        }
    }
    std::cout << std::endl;
}

void slideBoard::play()
{
    int16_t x;
    while (!equals()) {
        std::cout << "Current Gameboard:\n";
        print();
        getMoves();
        std::cin >> x;
        move(x);
    }
    print();
    std::cout << "\nCongratulations!" << std::endl;
}

void slideBoard::play(std::vector<int16_t> path)
{
    for (int i = path.size() - 1; i >= 0; i--){
        std::cout << "Current Gameboard:\n";
        print();
    std::cout << "\nPress any key to execute the next move (" << path[i] << ")\n";
        std::cin.ignore();
        move(path[i]);
    }
    print();
    std::cout << "\nThe puzzle is solved." << std::endl;
}

void slideBoard::randomize()
{
    int16_t i = 0;
    int16_t attempt;

    while (i < WIDTH * 100){
            // attempts to move n,e,s,w based on moves[] array
        attempt = rand() % 4;
        if (move(moves[attempt]+1)){
            i++;
        }
    }
}

void slideBoard::randomize1()
{
    gameboard->tile[0] = 6;
    gameboard->tile[1] = 4;
    gameboard->tile[2] = 1;
    gameboard->tile[3] = 3;
    gameboard->tile[4] = 7;
    gameboard->tile[5] = 2;
    gameboard->tile[6] = 8;
    gameboard->tile[7] = 5;
    gameboard->tile[8] = 0;
    emptyPos = 8;
    setMoves();
}

int16_t slideBoard::getFitness()
{
    return fitness;
}

void slideBoard::setFitness1()
{
    fitness = 1;
    for (int i = 0; i < size; i++)
    {
        if (gameboard->tile[i] != i)
        {
            fitness++;
        }
    }
    fitness += step;
}

void slideBoard::setFitness2()
{
    fitness = 1;
    for (int i = 0; i < size; i++)
    {
        fitness += abs(gameboard->tile[i]/WIDTH - i/WIDTH) + abs(gameboard->tile[i]%WIDTH - i%WIDTH);
    }
    fitness += step;
}

void slideBoard::setFitness3()
{
    fitness = 1;
    for (int i = 0; i < size; i++)
    {
        fitness += abs(gameboard->tile[i]/WIDTH - i/WIDTH) + abs(gameboard->tile[i]%WIDTH - i%WIDTH);
    }
    fitness += step;
}

bool slideBoard::compare(slideBoard *s)
{
    if (memcmp(s->gameboard->tile, gameboard->tile, sizeof(int16_t) * size) != 0){
        return false;
    }
    return true;
}

bool slideBoard::compare(int16_t *s)
{
    if (memcmp(s, gameboard->tile, sizeof(int16_t) * size) != 0){
        return false;
    }
    return true;
}

void slideBoard::fauxmove(int16_t *s, int16_t x)
{
    memcpy(s, gameboard->tile, sizeof(int16_t) * size);

    x--;
    int16_t temp = s[x];
    s[x] = s[emptyPos];
    s[emptyPos] = temp;
}

int16_t slideBoard::getsize()
{
    return size;
}

bool slideBoard::equals()
{
    for (int i = 0; i < size; i++)
    {
        if (i != gameboard->tile[i]){
            return false;
        }
    }
    return true;
}

bool slideBoard::equals(std::vector<int16_t> s)
{
    if (s.size() != size){
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (s[i] != gameboard->tile[i]){
            return false;
        }
    }
    return true;
}

bool slideBoard::move(int16_t x)
{
    for (int i = 0; i < 4; i++){
        if (x == moves[i] + 1 && moves[i] >= 0){
            int16_t temp = gameboard->tile[moves[i]];
            gameboard->tile[moves[i]] = gameboard->tile[emptyPos];
            gameboard->tile[emptyPos] = temp;
            emptyPos = moves[i];
            setMoves();
            return true;
        }
    }
    return false;
}

void slideBoard::movef(int16_t x)
{
    x--;
    int16_t temp = gameboard->tile[x];
    gameboard->tile[x] = gameboard->tile[emptyPos];
    gameboard->tile[emptyPos] = temp;
    emptyPos = x;
    setMoves();
}

slideBoard *slideBoard::spawn(int16_t x)
{
    slideBoard *sbnew = new slideBoard(WIDTH);

    for (int i = 0; i < size; i++) {
        sbnew->gameboard->tile[i] = gameboard->tile[i];
    }
    sbnew->emptyPos = emptyPos;
    sbnew->setMoves();

    sbnew->parent = this;
    sbnew->path = x;
    sbnew->step = step + 1;
    sbnew->movef(x);

    return sbnew;
}
