#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

typedef struct {
    size_t min;
    size_t max;
} range_t;

bool compare(range_t a, range_t b) { return a.min > b.min; }

int main() {

    std::vector<range_t> ranges;

    std::ifstream file("input.txt");

    std::string buf;

    // read ranges
    while (std::getline(file, buf)) {
        if (buf.empty()) break;

        auto dash = buf.find('-');

        if (dash == std::string::npos) continue;

        std::string a = buf.substr(0, dash);
        std::string b = buf.substr(dash + 1);

        range_t range = {std::stoull(a), std::stoull(b)};
        ranges.push_back(range);
    }

    std::vector<size_t> ingredients;

    // read ingredients
    while (std::getline(file, buf)) {
        if (buf.empty()) continue;
        ingredients.push_back(std::stoull(buf));
    }

    size_t count = 0;

    // count expired ingredients
    while (ingredients.size() > 0) {
        bool expired = 1;
        for (range_t r : ranges)
            if (ingredients.back() >= r.min && ingredients.back() <= r.max) {
                expired = 0;
                break;
            }
        
        if (!expired) count++;
        ingredients.pop_back();
    }

    std::cout << "amount of expired ingredients: " << count << std::endl;

    // part 2

    size_t IDs = 0;

    // sort ranges vector
    std::sort(ranges.begin(), ranges.end(), compare);
    
    IDs = (ranges.back().max - ranges.back().min) + 1;
    range_t prev_range = ranges.back();
    ranges.pop_back();
    
    while (ranges.size() > 0) {
        if (ranges.back().min > prev_range.max) {
            IDs += (ranges.back().max - ranges.back().min) + 1;
            prev_range = ranges.back();
            ranges.pop_back();
            continue;
        }

        if (ranges.back().max > prev_range.max) {
            IDs += (ranges.back().max - (prev_range.max + 1)) + 1;
            prev_range = ranges.back();
            ranges.pop_back();
            continue;
        }
        
        ranges.pop_back();
    }

    // return awnser
    std::cout << "amount of fresh ingredients: " << IDs << std::endl;

    return 0;
}