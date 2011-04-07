#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Query.h"
using namespace std;

Query::Query(string query)
{
    text = query;
    count = 0;
}

node* Query::open_list(map<string, int> &lexicon)
{
    int offset = 0, doc_id = 0, frequency = 0;
    string inverted_list;
    node* head = NULL;

    offset = get_offset( lexicon );
    inverted_list = get_inverted_list( offset );

    stringstream parseable_inverted_list( inverted_list );

    while( parseable_inverted_list >> doc_id >> frequency ) {
        node *temp, *temp2;

        count++;

        temp = new node;
        temp->doc_id = doc_id;
        temp->frequency = frequency;
        temp->next = NULL;

        if (head == NULL)
            head = temp;
        else {
            temp2 = head;

            while (temp2->next != NULL)
                temp2 = temp2->next;

            temp2->next = temp;
        }
    }

    return head;
}

int Query::get_offset(map<string, int> &lexicon)
{
    map<string, int>::iterator lexicon_cursor;
    lexicon_cursor = lexicon.find( text );
    return ( *lexicon_cursor ).second;
}

string Query::get_inverted_list(int offset)
{
    string inverted_list;
    ifstream inverted_index;

    inverted_index.open( "data/inverted_index" );
    inverted_index.seekg( offset, ios::beg );
    getline( inverted_index, inverted_list );
    inverted_index.close();

    return inverted_list;
}

int Query::get_frequency(int document_id, node* head)
{
    int doc_id = 0, frequency = 0;

    while( head->next != NULL ) {
        if( head->doc_id != document_id ) {
            head = head->next;
            continue;
        }
        else {
            return head->frequency;
        }
    }
    
    return frequency;
}

string Query::get_text()
{
    return text;
}

int Query::get_count()
{
    return count;
}

void Query::close_list(node* head)
{
    free( head );
}
