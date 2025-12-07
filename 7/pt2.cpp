#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

size_t explore(std::vector<std::string> &grid, std::vector<std::vector<long long>> &memo, size_t line, size_t beam) {    
    if (line >= grid.size() - 1) 
        return 1;
    
    // check if the line and beam combination has already been calculated
    if (memo[line][beam] != -1)
        return memo[line][beam];
    
    long long count = 0; 

    if (grid[line].at(beam) == '^') {
        // explore left
        count += explore(grid, memo, line + 1, beam - 1);
        // explore right
        count += explore(grid, memo, line + 1, beam + 1);
    } else {
        // explore straight down
        count += explore(grid, memo, line + 1, beam);
    }
    
    memo[line][beam] = count;
    return count;
}

int main() {

    std::ifstream file("input.txt");

    std::string buf;
    std::vector<std::string> grid;
    size_t paths = 0;

    // fill vector
    while (std::getline(file, buf))
        grid.push_back(buf);

    // print grid
    for (std::string line : grid)
        std::cout << line << std::endl;

    // 2d memoziation vector to store already explored values 
    std::vector<std::vector<long long>> memo(grid.size(), std::vector<long long>(grid[0].size(), -1));

    size_t start_beam = grid[0].find_first_of('S');
    paths = explore(grid, memo, 1, start_beam);
    
    std::cout << "amount of unique paths: " << paths << std::endl;
        
    return 0;
}