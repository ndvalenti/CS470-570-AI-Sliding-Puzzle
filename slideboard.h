#ifndef SLIDEBOARD_H
#define SLIDEBOARD_H
#include <iostream>
#include <vector>

class slideBoard
{
private:
    const int32_t WIDTH;
    int32_t size;

    struct board
    {
        int16_t *tile;
        board *parent;

        ~board(){
            // TODO: Determine how to handle tracking of parents
            // before starting searches
            delete [] tile;
            tile = NULL;
        }
    };
    board *gameboard;

    // Stores the index of the empty tile
    int16_t emptyPos;

    // Indicies track whether N,E,S,W are valid moves respectively
    // Will be -1 if invalid, index of available move if valid
    int16_t moves[4];

    // Updates int16_t moves[] for current position
    void getMoves();

    // Initializes to "solved" position
    void initializeBoard();

    void setMoves();

    bool move(int16_t x);

    // Checks if the current board is the same as s or is the default
    // solution state if no argument supplied
    // Uses std::vector to safely check bounds of s
    bool equals();
    bool equals(std::vector<int16_t> s);


public:
    // Constructs a board with width and height x, defaults to 3
    slideBoard();
    slideBoard(int32_t x);

    ~slideBoard()
    {
        // ONGOING: Keep track of dynamically allocated memory
        // individual boards currently responsible for deallocating their own memory
        delete gameboard;
    }

    void play();

    // Makes 1000 * WIDTH random valid moves
    void randomize();
    void print();

};

#endif // SLIDEBOARD_H
