#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include "Score.h"
#include "QueryProcessor.h"
#include "Query.h"
using namespace std;

string search_or_quit();
bool operator<(const Score &, const Score &);

int main()
{
    QueryProcessor query_processor;

    while( true ) {
        int do_restart = 0;
        priority_queue<Score> results;
        vector<node*> inverted_lists;
        string user_input = search_or_quit();
        query_processor.collect_queries( user_input );

        // GET LIST POINTERS
        for( int i = 0; i < query_processor.get_num_queries(); i++ ) {
            node* head = query_processor.get_queries()[i].open_list( QueryProcessor::get_lexicon() );
            
            if( head == NULL ) {
                do_restart = 1;
                break;
            }
            
            inverted_lists.push_back( head );
        }
        
        if( do_restart == 1) {
            query_processor.reset();
            inverted_lists.clear();
            continue;
        }
        
        query_processor.set_max_doc_id( inverted_lists );

        // CALC SCORES USING BM25, nextGEQ, freq, add to heap etc, etc
        int doc_id = 0;
        int new_doc_id = 0;
        int frequency = 0;
        int max_doc_id = query_processor.get_max_doc_id();
        double bm25_score = 0;
        
        if( query_processor.get_num_queries() == 1 ) {
        
            while( doc_id <= max_doc_id ) {
                doc_id = query_processor.next_geq( inverted_lists[0], doc_id );
                bm25_score = query_processor.calculate_rank( doc_id, inverted_lists );
                
                if( results.size() < 10 ) {
                    results.push( Score( query_processor.get_url( doc_id ), bm25_score ) );
                }
                else {
                    if( results.top().get_score() < bm25_score ) {
                        results.pop();
                        results.push( Score( query_processor.get_url( doc_id ), bm25_score ) );
                    }
                }
                
                doc_id++;
            }
            
        }
        else {
            while( doc_id <= max_doc_id ) {
                doc_id = query_processor.next_geq( inverted_lists[0], doc_id );
                
                if( doc_id == -1 )
                    break;

                for( int i = 1; i < query_processor.get_num_queries() && ( new_doc_id = query_processor.next_geq( inverted_lists[i], doc_id ) ) == doc_id; i++ );

                if( new_doc_id == -1 )
                    break;

                else if( new_doc_id > doc_id )
                    doc_id = new_doc_id;

                else {

                    bm25_score = query_processor.calculate_rank( new_doc_id, inverted_lists );
                    
                    if( results.size() < 10 ) {
                        results.push( Score( query_processor.get_url( new_doc_id ), bm25_score ) );
                    }
                    else {
                        if( results.top().get_score() < bm25_score ) {
                            results.pop();
                            results.push( Score( query_processor.get_url( new_doc_id ), bm25_score ) );
                        }
                    }

                    doc_id++;
                }
            }
        }

        while ( !results.empty() ) {
            cout << results.top().get_score() << " => " << results.top().get_url() << endl;
            results.pop();
        }

        query_processor.close_query_lists( inverted_lists );
        query_processor.reset();
        inverted_lists.clear();
    }

    cout << endl;
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

bool operator<(const Score &a, const Score &b)
{
    return a.get_score() < b.get_score();
}
