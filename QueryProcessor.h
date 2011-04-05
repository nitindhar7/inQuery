#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <iostream>
#include <map>
#include <vector>
#include "Query.h"
using namespace std;

class QueryProcessor
{
    public:
        QueryProcessor(int, vector<Query>);
        /*int nextGEQ(node*, int);
        double calculate_rank(int);
        string get_url(int);
        void add_to_heap(string, int);*/
        vector<Query> queries;
        int num_queries;
};

#endif
