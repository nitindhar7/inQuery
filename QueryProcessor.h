#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include "Query.h"
#include "page_stats.h"
using namespace std;

class QueryProcessor
{
    public:
        QueryProcessor(int, vector<Query>);
        int get_max_doc_id(vector<node*>);
        int nextGEQ(node*, int);
        
        static void clear_structures(map<string, int> &, map<int, page_stats> &);
        static void quit_if_requested(string, map<string, int> &, map<int, page_stats> &);
        static string search_or_quit(map<string, int> &, map<int, page_stats> &);
        static int collect_queries(string, vector<Query> &);
        /*double calculate_rank(int);
        string get_url(int);
        void add_to_heap(string, int);*/
        
        vector<Query> queries;
        int num_queries;
        int max_doc_id;
};

#endif
