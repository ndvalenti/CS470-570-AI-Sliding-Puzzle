#ifndef SLIDEBOARD_H
#define SLIDEBOARD_H
#include <iostream>

class slideBoard
{
private:
    struct tile
    {
        int16_t value;
    };
    const int32_t WIDTH;
    tile **tileList;
    int16_t emptyPos;
    int16_t moves[4];

    void initializeBoard();
    void setMoves();


public:
    slideBoard();
    slideBoard(int32_t x);
    ~slideBoard()
    {

    }

    void randomize();
    void getMoves();
    bool move(int16_t x);
    void solve();
    void solveFor(int32_t s);
    bool equals(int32_t s);

    void print();
};

#endif // SLIDEBOARD_H
