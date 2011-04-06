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

map<string, int> QueryProcessor::lexicon;
map<int, page_stats> QueryProcessor::url_table;

QueryProcessor::QueryProcessor()
{
    boot();
}

QueryProcessor::~QueryProcessor()
{
    clear_structures();
}

void QueryProcessor::init(int query_count, vector<Query> user_queries)
{
    num_queries = query_count;
    queries = user_queries;
    max_doc_id = 0;
}

vector<Query> QueryProcessor::get_queries()
{
    return queries;
}

int QueryProcessor::get_num_queries()
{
    return num_queries;
}

int QueryProcessor::get_max_doc_id()
{
    return max_doc_id;
}

int QueryProcessor::get_max_doc_id(vector<node*> inverted_lists)
{
    int maximum_doc_id = 0;
    
    for( int i = 0; i < num_queries; i++ ) {
        node* temp = inverted_lists[i];

        while( temp->next != NULL )
            temp = temp->next;
        
        if( maximum_doc_id < temp->doc_id )
            maximum_doc_id = temp->doc_id;
    }
    
    return maximum_doc_id;
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

void QueryProcessor::clear_structures()
{
    lexicon.clear();
    url_table.clear();
}

void QueryProcessor::quit_if_requested(string user_input)
{
    if( !user_input.compare( "quit" ) ) {
        clear_structures();
        exit( 0 );
    }
}

string QueryProcessor::search_or_quit()
{
    string user_input;

    cout << "Search or 'QUIT' to quit: ";
    getline( cin, user_input );

    transform( user_input.begin(), user_input.end(), user_input.begin(), ::tolower );

    quit_if_requested( user_input );

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

void QueryProcessor::load_lexicon()
{
    string line, word;
    int offset;
    ifstream lexicon_file;

    lexicon_file.open( "data/lexicon" );
    cout << "* Loading Lexicon... ";

    while( !lexicon_file.eof() ) {
        getline( lexicon_file, line );
        stringstream parseable_line( line );
        parseable_line >> word >> offset;
        lexicon[word] = offset;
    }

    cout << "[DONE]" << endl;
    lexicon_file.close();
}

void QueryProcessor::load_url_table()
{
    page_stats stats;
    string url, line;
    int doc_id, page_size;
    ifstream url_table_file;

    url_table_file.open( "data/url_table" );
    cout << "* Loading URL Table... ";

    while( !url_table_file.eof() ) {
        getline( url_table_file, line );
        stringstream parseable_line( line );
    
        parseable_line >> doc_id >> page_size >> url;
        stats.page_size = page_size;
        stats.url = url;
        url_table[doc_id] = stats;
    }

    cout << "[DONE]" << endl << endl;
    url_table_file.close();
}

void QueryProcessor::boot()
{
    cout << "Booting Query Processor" << endl;
    load_lexicon();
    load_url_table();
}

map<string, int> & QueryProcessor::get_lexicon()
{
    return QueryProcessor::lexicon;
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
