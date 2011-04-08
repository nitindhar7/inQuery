#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <iostream>
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
        int get_num_queries();
        int get_max_doc_id();
        int next_geq(int, int);
        int collect_inverted_lists();
        double calculate_rank(int);
        int get_doc_length(int);
        vector<Query> & get_queries();
        vector<node*> & get_inverted_lists();
        string get_url(int);
        void collect_queries(string);
        void set_max_doc_id();
        void close_query_lists();
        void reset();
        void set_avg_doc_length();
        void add_to_heap(string, int);
        static void clear_structures();
        static int get_avg_doc_length();
        static map<string, int> & get_lexicon();

    private:
        void boot();
        void load_lexicon();
        void load_url_table();
        int num_queries;
        int max_doc_id;
        vector<Query> queries;
        vector<node*> inverted_lists;
        static map<string, int> lexicon;
        static map<int, page_stats> url_table;
        static int avg_doc_length;
};

#endif
