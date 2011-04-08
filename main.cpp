#include "config.h"
#include "Score.h"
#include "MinHeap.h"
#include "QueryProcessor.h"
#include "Query.h"
#define MAX_NUM_RESULTS 10
using namespace std;

string search_or_quit();

int main()
{
    QueryProcessor query_processor;
    MinHeap results_heap( MAX_NUM_RESULTS );

    while( true ) {
        int do_restart = 0;

        string user_input = search_or_quit();

        query_processor.collect_queries( user_input );

        do_restart = query_processor.collect_inverted_lists();
        if( do_restart == 1 ) {
            query_processor.reset();
            continue;
        }
        
        query_processor.set_max_doc_id();

        // CALC SCORES USING BM25, nextGEQ, freq, add to heap etc, etc
        int doc_id = 0;
        int new_doc_id = 0;
        int max_doc_id = query_processor.get_max_doc_id();
        double bm25_score = 0;
        
        while( doc_id <= max_doc_id ) {
            doc_id = query_processor.next_geq( 0, doc_id );

            if( query_processor.get_num_queries() == 1 ) {
                bm25_score = query_processor.calculate_rank( doc_id );
                results_heap.push( Score( query_processor.get_url( doc_id ), bm25_score ) );
                doc_id++;
            }
            else {
                if( doc_id == -1 )
                    break;

                for( int i = 1; i < query_processor.get_num_queries() && ( new_doc_id = query_processor.next_geq( i, doc_id ) ) == doc_id; i++ );

                if( new_doc_id == -1 )
                    break;
                else if( new_doc_id > doc_id )
                    doc_id = new_doc_id;
                else {
                    bm25_score = query_processor.calculate_rank( new_doc_id );                    
                    results_heap.push( Score( query_processor.get_url( new_doc_id ), bm25_score ) );
                    doc_id++;
                }
            }
        }

        results_heap.display();

        query_processor.close_query_lists();
        query_processor.reset();
        cout << endl << endl;
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
        
    cout << "-----------------------------------------------------------------------" << endl;

    return user_input;
}
