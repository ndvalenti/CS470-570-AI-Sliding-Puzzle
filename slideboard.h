// Nick Valenti
// CS 470/570 AI
// Assignment 1 Part 2
// slideboard.h

#ifndef SLIDEBOARD_H
#define SLIDEBOARD_H
#include <iostream>
#include <vector>

class slideBoard
{
private:
    const int32_t WIDTH;
    int16_t size;

    slideBoard(int32_t x, bool fill);

    struct board
    {
        int16_t *tile;

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

    // Updates int16_t moves[] for current position
    void getMoves();

    // Initializes to "solved" position
    void initializeBoard();
    void initializeBoard(slideBoard &temp);
    void initializeBoardf();

    void setMoves();

    bool move(int16_t x);

    // WARNING: forces an attempted move without checking if it's valid
    void movef(int16_t x);


public:
    // Constructs a board with width and height x, defaults to 3
    slideBoard();
    slideBoard(int32_t x);
    slideBoard(slideBoard &temp);

    ~slideBoard()
    {
        // ONGOING: Keep track of dynamically allocated memory
        // individual boards currently responsible for deallocating their own memory
        delete gameboard;
    }

    void play();
    void play(std::vector<int16_t> path);

    // Makes 1000 * WIDTH random valid moves
    void randomize();
    void print();

    // Compares the contents of two gameboards
    bool compare(slideBoard *s);
    bool compare(int16_t *s);

    int16_t getsize();


    // Makes a fake "fast" move for comparison purposes
    void fauxmove(int16_t *s, int16_t x);

    // Checks if the current board is the same as s or is the default
    // solution state if no argument supplied
    // Uses std::vector to safely check bounds of s
    bool equals();
    bool equals(std::vector<int16_t> s);

    // Spawns a child copy and returns a pointer to it
    slideBoard *spawn(int16_t x);

    // Indicies track whether N,E,S,W are valid moves respectively
    // Will be -1 if invalid, index of available move if valid
    int16_t moves[4];
    int16_t path;
    slideBoard *parent;
    //std::vector<int16_t> path;
};

#endif // SLIDEBOARD_H
