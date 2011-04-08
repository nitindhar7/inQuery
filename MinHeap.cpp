#include <iostream>
#include "MinHeap.h"
using namespace std;

MinHeap::MinHeap(int size)
{
    max_size = size;
}

void MinHeap::push(Score score)
{
    if( heap.size() < max_size )
        heap.push( score );
    else {
        if( heap.top().get_score() < score.get_score() ) {
            heap.pop();
            heap.push( score );
        }
    }
}

void MinHeap::display()
{
    while ( !heap.empty() ) {
        cout << heap.top().get_score() << " => " << heap.top().get_url() << endl;
        heap.pop();
    }
}

bool operator<(const Score &a, const Score &b)
{
    return a.get_score() < b.get_score();
}
