#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include "QueryProcessor.h"
#include "Query.h"
using namespace std;

string search_or_quit();

int main()
{
    QueryProcessor query_processor;

    // get average page length somehow.

    while( true ) {
        vector<node*> inverted_lists;
        string user_input = search_or_quit();
        query_processor.collect_queries( user_input );

        // GET LIST POINTERS
        for( int i = 0; i < query_processor.get_num_queries(); i++ ) {
            node* head = query_processor.get_queries()[i].open_list( QueryProcessor::get_lexicon() );
            inverted_lists.push_back( head );
        }
        
        query_processor.set_max_doc_id( inverted_lists );

        // CALC SCORES USING BM25, nextGEQ, freq, add to heap etc, etc
        int doc_id = 0;
        int new_doc_id = 0;
        int frequency = 0;
        int max_doc_id = query_processor.get_max_doc_id();
        while( doc_id <= max_doc_id ) {
            doc_id = query_processor.next_geq( inverted_lists[0], doc_id );

            for( int i = 1; i < query_processor.get_num_queries() && ( new_doc_id = query_processor.next_geq( inverted_lists[i], doc_id ) ) == doc_id; i++ );
            // doc_id = 9638
            // new_doc_id = 19022
            if( new_doc_id > doc_id )
                doc_id = new_doc_id;
            else {
                /*for( int i = 0; i < query_processor.get_num_queries(); i++ ) {
                    frequency = query_processor.get_queries()[i].get_frequency( doc_id, inverted_lists[i] );
                    cout << frequency << endl;
                }*/
                
                // BM25
                
                doc_id++;
            }
            // doc_id = 19022
            // new_doc_id = 19022
        }

        // loop num_queries: queryies[i].close_list()

        // display results
        
        // clear the containers in query_processor
    }

    return 0;
}

string search_or_quit()
{
    string user_input;

    cout << "Search or 'QUIT' to quit: ";
    getline( cin, user_input );

    transform( user_input.begin(), user_input.end(), user_input.begin(), ::tolower );

    if( !user_input.compare( "quit" ) )
        exit( 0 );

    return user_input;
}
