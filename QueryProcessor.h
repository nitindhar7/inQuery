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
        // per object
        QueryProcessor();
        ~QueryProcessor();
        vector<Query> & get_queries();
        int get_num_queries();
        int get_max_doc_id();
        void set_max_doc_id(vector<node*>);
        int next_geq(node*, int);
        void collect_queries(string);
        void show_queries();
        string get_url(int);
        void close_query_lists(vector<node*> &);
        void reset();
        void set_avg_doc_length();
        double calculate_rank(int, vector<node*> &);
        int get_doc_length(int);
        //void add_to_heap(string, int);
        
        // for all query processors
        static void clear_structures();
        static int get_avg_doc_length();
        static map<string, int> & get_lexicon();

    private:
        // per object
        void boot();
        void load_lexicon();
        void load_url_table();
        vector<Query> queries;
        int num_queries;
        int max_doc_id;
        
        // for all query processors
        static map<string, int> lexicon;
        static map<int, page_stats> url_table;
        static int avg_doc_length;
};

#endif
