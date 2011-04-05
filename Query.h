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
	    node* open_list(Lexicon &, LexiconCursor &);
    private:
        int get_offset(Lexicon &, LexiconCursor &);
        string get_inverted_list(int);
};

#endif

//void close_list(node*);
        //int get_frequency(int);
