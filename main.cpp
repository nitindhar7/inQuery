#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "boot.h"
#include "QueryProcessor.h"
#include "Query.h"
using namespace std;

map<string, int> lexicon;
map<string, int>::iterator lexicon_cursor;
map<int, page_stats> url_table;
map<int, page_stats>::iterator url_table_cursor;

vector<Query> queries;

int main()
{
    boot::init( lexicon, url_table );
    // get average page length somehow.

    while( true ) {
        int max_doc_id = 0;
        vector<node*> inverted_lists;
        string user_input = QueryProcessor::search_or_quit( lexicon, url_table );
        int num_queries = QueryProcessor::collect_queries( user_input, queries );
        QueryProcessor query_processor( num_queries, queries );

        // GET LIST POINTERS
        for( int i = 0; i < query_processor.num_queries; i++ ) {
            node* head = query_processor.queries[i].open_list( lexicon, lexicon_cursor );
            inverted_lists.push_back( head );
        }
        
        max_doc_id = query_processor.get_max_doc_id( inverted_lists );

        // CALC SCORES USING BM25, nextGEQ, freq, add to heap etc, etc
        int doc_id = 0;
        int new_doc_id = 0;
        int frequency = 0;
        while( doc_id <= max_doc_id ) {
            doc_id = query_processor.nextGEQ( inverted_lists[0], doc_id );
            
            for( int i = 1; i < query_processor.num_queries && ( new_doc_id = query_processor.nextGEQ( inverted_lists[1], doc_id ) ) == doc_id; i++ );
            
            if( new_doc_id > doc_id )
                doc_id = new_doc_id;
            else {
                for( int i = 0; i < query_processor.num_queries; i++ ) {
                    frequency = query_processor.queries[i].get_frequency( doc_id, inverted_lists[i] );
                    cout << frequency << endl;
                }
                doc_id++;
            }
        }

        // loop num_queries: queryies[i].close_list()

        // display results
    }
    
    QueryProcessor::clear_structures( lexicon, url_table );

    return 0;
}
