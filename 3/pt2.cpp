#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>

#define LINE_LEN 100

long long find_max(int* numbers, int i_start, int ignore_amount) {
    if (ignore_amount < 0) return 0;

    long long max = numbers[i_start];
    int i_max = i_start;

    for (int i = i_start; i < LINE_LEN - ignore_amount; i++) 
        if (numbers[i] > max) {
            max = numbers[i];
            i_max = i;
        } 
    
    ignore_amount--;
    return (max * pow(10, ignore_amount + 1)) + find_max(numbers, i_max + 1, ignore_amount);
}

int main() {
    std::ifstream file("input.txt");
    int numbers[LINE_LEN + 1];
    char buf[LINE_LEN + 1];
    unsigned long long sum = 0;

    while (file.getline(buf, LINE_LEN + 1)) {
        for (int i = 0; i < LINE_LEN; i++) numbers[i] = buf[i] - '0';
        sum += find_max(numbers, 0, 11);
    }

    std::cout << "sum: " << sum << std::endl;
    return 0;
}