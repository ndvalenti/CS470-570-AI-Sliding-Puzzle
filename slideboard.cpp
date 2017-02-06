#include "slideboard.h"
#include <iomanip>
#include <time.h>
#include <stdlib.h>

slideBoard::slideBoard() : WIDTH(3)
{
    initializeBoard();
}

slideBoard::slideBoard(int32_t x) : WIDTH(x)
{
    initializeBoard();
}

void slideBoard::initializeBoard()
{
    size = WIDTH * WIDTH;
    srand(time(NULL));
    int16_t count = 0;
    emptyPos = 0;

    gameboard = new board();

    gameboard->parent = NULL;
    gameboard->tile = new int16_t[size];

    for (int i = 0; i < size; i++) {
        gameboard->tile[i] = count;
        count++;
    }
    setMoves();
}

void slideBoard::print() {
    std::cout << "Current Gameboard:\n";
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
    std::cout << std::endl;
}

void slideBoard::setMoves()
{
    for (int i = 0; i < 4; i++){
        moves[i] = -1;
    }
    if (emptyPos - WIDTH >= 0){
        moves[0] = emptyPos - WIDTH;
    }
    if ((emptyPos + 1) % WIDTH != 0) {
        moves[1] = emptyPos + 1;
    }
    if ((emptyPos + WIDTH) < (size)) {
        moves[2] = emptyPos + WIDTH;
    }
    if (emptyPos % WIDTH != 0) {
        moves[3] = emptyPos - 1;
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
    randomize();
    while (!equals()) {
        print();
        getMoves();
        std::cin >> x;
        move(x);
    }
    print();
    std::cout << "Congratulations!" << std::endl;
}

void slideBoard::randomize()
{
    int16_t i = 0;
    int16_t attempt;

    while (i < WIDTH * 1000){
            // attempts to move n,e,s,w based on moves[] array
        attempt = rand() % 4;
        if (move(moves[attempt]+1)){
            i++;
        }
    }
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
