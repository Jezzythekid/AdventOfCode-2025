#include <iostream>
#include <stdlib.h>
#include <fstream>

#define LOCKSIZE 100
#define INIT_LOCK 50

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
            
        if (dir == 'R') position = (position + amount) % (LOCKSIZE);
        else position = ((position - amount) % (LOCKSIZE) + (LOCKSIZE)) % (LOCKSIZE);

        if (position == 0) zero_count += 1;

        dir = file.get();
        file.getline(str_amount, 5);
    }

    std::cout << "end zerocount: " << zero_count << std::endl;
    return 0;
}