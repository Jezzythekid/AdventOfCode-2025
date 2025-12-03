#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define BUFF_SIZE 20


// some code I stole from chatGPT, because i was done with it
bool allEqual(const std::vector<std::string>& v) {
    if (v.empty()) return true;
    const std::string& first = v[0];
    return std::all_of(v.begin(), v.end(),
                       [&](const std::string& s){ return s == first; });
}

bool is_valid(std::string* str_number) {

    int length = str_number->length();
    int c = 2;
    bool invalid = false;

    std::vector<std::string> vect;

    while (c <= length) {

        vect.clear();

        if (length % c != 0) {
            c++;
            continue;
        }

        int cur_partion = length / c;

        for (int i = 1; i - 1 < c; i++) 
            vect.push_back(str_number->substr((i - 1) * cur_partion, cur_partion));

        invalid = allEqual(vect);
        if (invalid) break;
        c++;
    }

    return !invalid;
}

void get_values_in_range(long long int begin, long long int end, std::vector<long long int>* out) {
    out->push_back(begin);

    long long int next = begin + 1;

    while (next < end) {
        out->push_back(next);
        next++;
    }

    out->push_back(end);
}

int main() {
    std::ifstream file("input.txt");

    char first[20];
    char last[20];
    std::vector<long long int> range;
    long long int sum = 0;
    

    while (file.get(first, 20, '-')) {
        file.get();
        file.get(last, 20, ',');
        file.get();

        get_values_in_range(std::stoll(first), std::stoll(last), &range);

        while (range.size() > 0) {
            std::string str = std::to_string(range.back());
            if (!is_valid(&str)) sum += range.back();
            range.pop_back();
        }
    }

    std::cout << "sum: " << sum << std::endl;
    return 0;
}