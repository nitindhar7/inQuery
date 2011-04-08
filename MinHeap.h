#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include <queue>
#include "Score.h"
using namespace std;

bool operator<(const Score &, const Score &);

class MinHeap
{
    public:
        MinHeap(int);
        void push(Score);
        void display();
    private:
        int max_size;
        priority_queue<Score> heap;
};

#endif
