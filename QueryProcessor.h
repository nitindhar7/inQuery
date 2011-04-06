#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Query.h"
#include "page_stats.h"
using namespace std;

class QueryProcessor
{
    public:
        QueryProcessor();
        ~QueryProcessor();
        vector<Query> & get_queries();
        int get_num_queries();
        int get_max_doc_id();
        int get_max_doc_id(vector<node*>);
        int next_geq(node*, int);
        void collect_queries(string);
        void show_queries();
        /*double calculate_rank(int);
        string get_url(int);
        void add_to_heap(string, int);*/
        
        static void clear_structures();
        static map<string, int> & get_lexicon();
    private:
        void boot();
        void load_lexicon();
        void load_url_table();

        vector<Query> queries;
        int num_queries;
        int max_doc_id;
        static map<string, int> lexicon;
        static map<int, page_stats> url_table;
};

#endif
