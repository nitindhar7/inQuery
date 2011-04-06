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
        string text;
        int count;
        Query(string);
        node* open_list(map<string, int> &, map<string, int>::iterator &);
        int get_frequency(int, node*);
        //void close_list(node*);
    private:
        int get_offset(map<string, int> &, map<string, int>::iterator &);
        string get_inverted_list(int);
};

#endif
