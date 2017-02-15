// Nick Valenti
// CS 470/570 AI
// Assignment 1 Part 2
// search.h

#ifndef SEARCH_H
#define SEARCH_H
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <list>
#include <windows.h>

#include "slideboard.h"

// Breadth first open list, populates path with the solution in reverse order
void solveBF(slideBoard &original, std::vector<int16_t> &path);

// Breadth first closed list, populates path with the solution in reverse order
void solveBFC(slideBoard &original, std::vector<int16_t> &path);

// Depth first search
void solveDFS(slideBoard &original, std::vector<int16_t> &path);

void DFSRecurse(slideBoard *curr, std::list<slideBoard*> DFStack, std::list<slideBoard*> Closed, int16_t *comparr);

#endif // SEARCH_H
