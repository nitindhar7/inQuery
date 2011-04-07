#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include "QueryProcessor.h"

#define CONSTANT_K 1.2
#define CONSTANT_B 0.75
using namespace std;

map<string, int> QueryProcessor::lexicon;
map<int, page_stats> QueryProcessor::url_table;
int QueryProcessor::avg_doc_length;

QueryProcessor::QueryProcessor()
{
    num_queries = 0;
    max_doc_id = 0;
    avg_doc_length = 0;
    boot();
    set_avg_doc_length();
}

QueryProcessor::~QueryProcessor()
{
    clear_structures();
}

vector<Query> & QueryProcessor::get_queries()
{
    return queries;
}

void QueryProcessor::reset()
{
    queries.clear();
    num_queries = 0;
    max_doc_id = 0;
}

int QueryProcessor::get_num_queries()
{
    return num_queries;
}

int QueryProcessor::get_max_doc_id()
{
    return max_doc_id;
}

int QueryProcessor::get_avg_doc_length()
{
    return avg_doc_length;
}

void QueryProcessor::set_max_doc_id(vector<node*> inverted_lists)
{
    for( int i = 0; i < num_queries; i++ ) {
        node* temp = inverted_lists[i];

        while( temp->next != NULL )
            temp = temp->next;
        
        if( max_doc_id < temp->doc_id )
            max_doc_id = temp->doc_id;
    }
}

void QueryProcessor::set_avg_doc_length()
{
    int total_length = 0;
    map<int, page_stats>::iterator url_table_cursor;
    
    cout << "* Calculating Average Document Length... ";
    
    for( url_table_cursor = url_table.begin(); url_table_cursor != url_table.end(); url_table_cursor++ )
        total_length += ( *url_table_cursor ).second.page_size;
        
    avg_doc_length = total_length / url_table.size();

    cout << "[" << avg_doc_length << "]" << endl << endl;    
}

int QueryProcessor::next_geq(node* head, int doc_id)
{
    while( head != NULL ) {
        if( head->doc_id >= doc_id )
            return head->doc_id;
        head = head->next;
    }
    
    return -1;
}

void QueryProcessor::clear_structures()
{
    lexicon.clear();
    url_table.clear();
}

void QueryProcessor::close_query_lists(vector<node*> &inverted_lists)
{
    for( int i = 0; i < num_queries; i++ )
        queries[i].close_list( inverted_lists[i] );
}

void QueryProcessor::collect_queries(string user_input)
{
    string tmp_query;
    stringstream user_input_stream( user_input );

    while( user_input_stream >> tmp_query ) {
        Query query( tmp_query );
        queries.push_back( query );
        num_queries++;
    }
}

void QueryProcessor::show_queries()
{
    for( int i = 0; i < num_queries; i++ )
        cout << i << ". " << queries[i].get_text() << endl;
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

    cout << "[DONE]" << endl;
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

string QueryProcessor::get_url(int doc_id)
{
    map<int, page_stats>::iterator url_table_cursor;
    url_table_cursor = url_table.find( doc_id );
    return ( *url_table_cursor ).second.url;
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

void QueryProcessor::add_to_heap(string url, int doc_id)
{
    //add url and doc_id
}
*/
