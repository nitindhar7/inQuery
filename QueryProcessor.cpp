#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>
#include "QueryProcessor.h"

#define CONSTANT_K 1.2
#define CONSTANT_B 0.75
using namespace std;

QueryProcessor::QueryProcessor(int query_count, vector<Query> user_queries)
{
    num_queries = query_count;
    queries = user_queries;
    max_doc_id = 0;
}

int QueryProcessor::get_max_doc_id(vector<node*> inverted_lists)
{
    int max_doc_id = 0;
    
    for( int i = 0; i < num_queries; i++ ) {
        node* temp = inverted_lists[i];

        while( temp->next != NULL )
            temp = temp->next;
        
        if( max_doc_id < temp->doc_id )
            max_doc_id = temp->doc_id;
    }
    
    return max_doc_id;
}

int QueryProcessor::nextGEQ( node* list_head, int doc_id)
{
    node* head = NULL;

    head = list_head;

    if( head->doc_id >= doc_id )
        return head->doc_id;
    else
        head = head->next;

    return -1;
}

void QueryProcessor::clear_structures(map<string, int> &lexicon, map<int, page_stats> &url_table)
{
    lexicon.clear();
    url_table.clear();
}

void QueryProcessor::quit_if_requested(string user_input, map<string, int> &lexicon, map<int, page_stats> &url_table)
{
    if( !user_input.compare( "quit" ) ) {
        clear_structures( lexicon, url_table );
        exit( 0 );
    }
}

string QueryProcessor::search_or_quit(map<string, int> &lexicon, map<int, page_stats> &url_table)
{
    string user_input;

    cout << "Search or 'QUIT' to quit: ";
    getline( cin, user_input );

    transform( user_input.begin(), user_input.end(), user_input.begin(), ::tolower );

    quit_if_requested( user_input, lexicon, url_table );

    return user_input;
}

int QueryProcessor::collect_queries(string user_input, vector<Query> &queries)
{
    int num_queries = 0;
    string tmp_query;
    stringstream user_input_stream( user_input );

    while( user_input_stream >> tmp_query ) {
        Query query( tmp_query );
        queries.push_back( query );
        num_queries++;
    }

    return num_queries;
}
/*
double QueryProcessor::calculate_rank(int doc_id)
{
    int total_pages, total_pages_with_queryword, freq_of_query_in_doc, doc_length;
    double K, page_rank, log_result,freq_result,avg_doc_length;

    K = CONSTANT_K* ( (1-CONSTANT_B) + ( CONSTANT_B * (doc_length/avg_doc_length) ) );

    total_pages_with_queryword = Query.count();
    freq_of_query_in_doc = Query.get_frequency();

    log_result = log( (total_pages - freq_of_query_in_doc + 0.5) / ( freq_of_query_in_doc + 0.5) );
    freq_result = ( ((CONSTANT_K+1) * total_pages_with_queryword) / (K+total_pages_with_queryword) );

    page_rank = log_result * freq_result;

    return page_rank;
}

string QueryProcessor::get_url(int doc_id)
{
    url_table_iterator = kyon_url_table.find( doc_id );
    return ( *url_table_iterator ).second.url;
}

void QueryProcessor::add_to_heap(string url, int doc_id)
{
    //add url and doc_id
}
*/
