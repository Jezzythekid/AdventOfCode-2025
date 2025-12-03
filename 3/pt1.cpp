#include <iostream>
#include <stdlib.h>
#include <fstream>

#define LINE_LEN 100

int func(char* buf, int* numbers) {
        int max = numbers[0];
        int i_max = 0;

        // find max, ignore last idx
        for (int i = 0; i < LINE_LEN - 1; i++) {
            if (numbers[i] > max) {
                max = numbers[i];
                i_max = i;
            } 
        }

        int second_max = numbers[i_max + 1];
        int i_second_max = i_max + 1;

        // find max from range i_max - end
        for (int i = i_max + 1; i < LINE_LEN; i++) {
            if (numbers[i] > second_max) {
                second_max = numbers[i];
                i_second_max = i;
            }    
        }

        return (max * 10) + second_max;
}

int main() {
    std::ifstream file("input.txt");
    int numbers[LINE_LEN + 1];
    char buf[LINE_LEN + 1];
    int sum = 0;

    while (file.getline(buf, LINE_LEN + 1)) {
        for (int i = 0; i < LINE_LEN; i++) numbers[i] = buf[i] - '0';
        sum += func(buf, numbers);
    }
    
    std::cout << sum << std::endl;

    return 0;
}