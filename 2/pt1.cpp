#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

bool is_valid(std::string* str_number) {
    int lenght = str_number->length();
    int middle = lenght / 2;

    // uneven number cannot be invalid
    if (lenght % 2 != 0) return true;

    std::string str1 = str_number->substr(0, middle);
    std::string str2 = str_number->substr(middle);

    return str1.compare(str2);
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