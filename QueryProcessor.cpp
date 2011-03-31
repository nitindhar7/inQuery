#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include "lib/QueryProcessor.h"

#define CONSTANT_K 1.2
#define CONSTANT_B 0.75
using namespace std;

QueryProcessor::QueryProcessor(int query_count, vector<Query> user_queries)
{
    num_queries = query_count;
    queries = user_queries;
}

/*int QueryProcessor::nextGEQ( node* list_head, int doc_id)
{
    node* head = NULL;

    head = list_head;

    if( head->doc_id >= doc_id )
        return doc_id;
    else
        head = head->next;

    return -1;
}

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
