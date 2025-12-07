#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>

int main() {

    std::ifstream file("input.txt");

    std::string buf;
    std::deque<size_t> beams;
    std::deque<size_t> next_beams;

    size_t splits = 0;

    // find start
    std::getline(file, buf);
    beams.push_back(buf.find_first_of('S'));

    // parse splitters
    while (std::getline(file, buf)) {
        size_t i = 0;
        for (char c : buf) {
            // if no beams left, break loop
            if (beams.empty()) break;

            // split beam
            if (c == '^' && i == beams.front()) {
                splits++;
                next_beams.push_back(i - 1);
                next_beams.push_back(i + 1);
                beams.pop_front();
            }

            // copy beam downwards
            if (c == '.' && i == beams.front()) {
                next_beams.push_back(i);
                beams.pop_front();
            }

            i++;
        }

        std::swap(beams, next_beams);

        // remove duplicate beams
        auto it = std::unique(beams.begin(), beams.end());
        beams.resize(std::distance(beams.begin(), it));
    }
    
    std::cout << "amount of beam splits: " << splits << std::endl;
        
    return 0;
}