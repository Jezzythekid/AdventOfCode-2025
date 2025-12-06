#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

bool eq_spaces(char a, char b) { return (a == b && a == ' '); }

int main() {

    std::ifstream file("input.txt");

    std::string buf_str;
    std::string::iterator buf_str_it;
    std::vector<size_t> buf_numbers;

    bool initialized = false;
    std::vector<std::vector<size_t>> numbers;
    std::vector<char> operations;


    while (std::getline(file, buf_str)) {

        // remove unessecary spaces
        buf_str_it = std::unique(buf_str.begin(), buf_str.end(), eq_spaces);
        buf_str.resize(std::distance(buf_str.begin(), buf_str_it));

        // remove leading zero on first number
        if (buf_str[0] == ' ') buf_str.erase(buf_str.begin());

        // break when operations line
        if (buf_str[0] == '*' || buf_str[0] == '+') break;

        // split string
        size_t start = 0;
        size_t end = buf_str.find_first_of(' ');
        while (end != std::string::npos) {
            buf_numbers.push_back(std::stoi(buf_str.substr(start, end-start)));
            start = end + 1;
            end = buf_str.find_first_of(' ', start);
        }
        
        // push last number if it does not end with an space
        if (start < buf_str.length()) {
            buf_numbers.push_back(std::stoi(buf_str.substr(start)));
        }

        // initialize 2d numbers vector, if not already
        if (!initialized) numbers.resize(buf_numbers.size());

        // fill 2d numbers vector
        for (size_t i = 0; buf_numbers.size() > 0; i++, buf_numbers.pop_back()) {
            numbers[i].push_back(buf_numbers.back());
        }
    }

    // split operations string
    size_t delim = buf_str.find_first_of(' ');
    while (delim != std::string::npos) {
        buf_str.erase(buf_str.begin() + delim);
        delim = buf_str.find_first_of(' ');
    }

    // fill operations vector
    for (char c : buf_str)
        operations.push_back(c);

    // calculate total sum
    size_t total_sum = 0;
    for (char op : operations) {
        if (op == '*') {
            size_t product = 1;
            for (size_t number : numbers.back()) product *= number;
            total_sum += product;
            numbers.pop_back();
        } else {
            size_t sum = 0;
            for (size_t number : numbers.back()) sum += number;
            total_sum += sum;
            numbers.pop_back();
        }
    }

    std::cout << "sum of the results of the operations: " << total_sum << std::endl;
        
    return 0;
}