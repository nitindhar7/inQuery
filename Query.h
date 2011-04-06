#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <map>
using namespace std;

struct node {
    int doc_id;
    int frequency;
    node *next;
};

class Query
{
    public:
        Query(string);
        node* open_list(map<string, int> &);
        int get_frequency(int, node*);
        string get_text();
        int get_count();
        //void close_list(node*);
    private:
        int get_offset(map<string, int> &);
        string get_inverted_list(int);
        string text;
        int count;
};

#endif
