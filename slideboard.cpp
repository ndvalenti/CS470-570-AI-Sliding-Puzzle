#include "slideboard.h"
#include <iomanip>

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
    int16_t count = 0;
    emptyPos = 0;

    tileList = new tile*[WIDTH];
    for (int i = 0; i < WIDTH; i++){
        tileList[i] = new tile[WIDTH];
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < WIDTH; j++){
            tileList[i][j].value = count;
            count++;
        }
    }
    setMoves();
}

void slideBoard::print() {
    std::cout << "\n";
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < WIDTH; j++){
            if (tileList[i][j].value != 0) {
                std::cout << std::left << std::setw(3) << tileList[i][j].value;
            } else {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
}

void slideBoard::setMoves()
{
    for (int i = 0; i < 4; i++){
        moves[i] = 0;
    }
    if (emptyPos - WIDTH + 1 > 0){
        moves[0] = emptyPos - WIDTH + 1;
    }
    if ((emptyPos + 1) % WIDTH != 0) {
        moves[1] = emptyPos + 2;
    }
    if ((emptyPos + WIDTH) < (WIDTH * WIDTH)) {
        moves[2] = emptyPos + WIDTH + 1;
    }
    if (emptyPos % WIDTH != 0) {
        moves[3] = emptyPos;
    }
    getMoves();
}

void slideBoard::getMoves()
{
    for (int i = 0; i < 4; i++)
        std::cout << moves[i] << " ";
    std::cout << std::endl;
}

bool slideBoard::move(int16_t x)
{
    return false;
}
