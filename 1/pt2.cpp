#include <iostream>
#include <stdlib.h>
#include <fstream>

#define LOCKSIZE 100
#define INIT_LOCK 50

int step(bool dir, int cur_pos, int start, int end, int steps, int* zeros) {

    if (steps == 0) return cur_pos;
    if (cur_pos == 0) *zeros += 1;


    int new_pos = cur_pos + (dir ? 1 : -1);

    if (new_pos > end) return step(dir, start, start, end, steps - 1, zeros);
    if (new_pos < start) return step(dir, end, start, end, steps - 1, zeros);
    else return step(dir, new_pos, start, end, steps - 1, zeros);
}

int main() {
    int position = INIT_LOCK;
    char dir;
    char str_amount[10];
    int amount;

    std::ifstream file("input.txt");

    dir = file.get();
    file.getline(str_amount, 5);
    amount = std::stoi(str_amount);

    int zero_count = 0;
    while (file.gcount() > 0) {

        if (file.gcount() > 1) amount = std::stoi(str_amount);
        else break;

        position = step(dir == 'R', position, 0, 99, amount, &zero_count);

        dir = file.get();
        file.getline(str_amount, 5);
    }

    std::cout << "end zerocount: " << zero_count << std::endl;
    return 0;
}