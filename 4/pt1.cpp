#include <iostream>
#include <stdlib.h>
#include <fstream>

#define GRIDSIZE 135

int main() {

    bool rolls[GRIDSIZE][GRIDSIZE];
    int adjecent[GRIDSIZE][GRIDSIZE] = {0};

    std::ifstream file("input.txt");
    
    // fill 2d array
    for (int i = 0; i < GRIDSIZE; i++, file.get()) 
        for (int j = 0; j < GRIDSIZE; j++) 
            rolls[i][j] = file.get() == '@';

    // fill adjecent grid with the values of the adjecent rolls
    for (int i = 0; i < GRIDSIZE; i++, file.get()) { 
        for (int j = 0; j < GRIDSIZE; j++) {
            // check left top, middle and bottom
            if (i > 0) {
                // top left
                if (j > 0 && rolls[i - 1][j - 1]) adjecent[i][j]++;
                // middle left
                if (rolls[i - 1][j]) adjecent[i][j]++;
                // bottom left
                if (j < GRIDSIZE - 1 && rolls[i - 1][j + 1]) adjecent[i][j]++;
            }
            
            // check right top, middle and bottom
            if (i < GRIDSIZE - 1) {
                // top right
                if (j > 0 && rolls[i + 1][j - 1]) adjecent[i][j]++;
                // middle right
                if (rolls[i + 1][j]) adjecent[i][j]++;
                // bottom right
                if (j < GRIDSIZE - 1 && rolls[i + 1][j + 1]) adjecent[i][j]++;
            }

            // check top
            if (j > 0 && rolls[i][j - 1]) adjecent[i][j]++;
            // check bottom
            if (j < GRIDSIZE - 1 && rolls[i][j + 1]) adjecent[i][j]++;
        }
    }

    // count rolls with fewer that 4 adjecent rolls
    int count = 0;
    for (int i = 0; i < GRIDSIZE; i++) for (int j = 0; j < GRIDSIZE; j++) if (rolls[i][j] && adjecent[i][j] < 4) count++;

    std::cout << std::endl << "Count: " << count << std::endl;

    return 0;
}