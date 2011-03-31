#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "lib/Query.h"
using namespace std;

Query::Query(string query)
{
    text = query;
    count = 0;
}

node* Query::open_list(Lexicon &lexicon, LexiconCursor &lexicon_cursor)
{
    int offset = 0, doc_id = 0, frequency = 0;
    string inverted_list;
    stringstream parseable_inverted_list;
    node* head = NULL;

    offset = get_offset( lexicon, lexicon_cursor );
    inverted_list = get_inverted_list( offset ); // remember to seek to beg after done

    parseable_inverted_list << inverted_list;

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

int Query::get_offset(Lexicon &lexicon, LexiconCursor &lexicon_cursor)
{
    lexicon_cursor = lexicon.find( text );
    return ( *lexicon_cursor ).second;
}

string Query::get_inverted_list(int offset)
{
    string inverted_list;
    ifstream inverted_index;

    inverted_index.open( "structures/inverted_index" );
    inverted_index.seekg( offset, ios::beg );
    getline( inverted_index, inverted_list );
    inverted_index.close();

    return inverted_list;
}

/*
void Query::close_list(node* head)
{
    free( head );
}

int Query::get_frequency(int document_id)
{
    int doc_id = 0, frequency = 0;
    string inverted_list;
    stringstream parseable_inverted_list;

    while( parseable_inverted_list >> doc_id >> frequency ) {
        if( doc_id == document_id )
            return frequency;
    }

    return 0;
}

*/
