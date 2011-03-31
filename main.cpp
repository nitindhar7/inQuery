#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "lib/boot.h"
#include "lib/util.h"
#include "lib/QueryProcessor.h"
#include "lib/Query.h"
using namespace std;

Lexicon lexicon;
LexiconCursor lexicon_cursor;
UrlTable url_table;
UrlTableCursor url_table_cursor;

vector<Query> queries;

int main()
{
    boot::init( lexicon, url_table );
    // get average page length somehow.

    while( true ) {
        vector<node*> inverted_lists;
        string user_input = util::search_or_quit( lexicon, url_table );
        int num_queries = util::collect_queries( user_input, queries );
        QueryProcessor query_processor( num_queries, queries );

        // GET LIST POINTERS
        for( int i = 0; i < query_processor.num_queries; i++ ) {
            inverted_lists.push_back( query_processor.queries[i].open_list( lexicon, lexicon_cursor ) );
            //get_max_page_num_by_travering_to_end_of_lists_and_comparing_values();
        }

        // CALC SCORES USING BM25, nextGEQ, freq, add to heap etc, etc
        //while() {

        //}

        // loop num_queries: queryies[i].close_list()

        // display results
    }

    return 0;
}
