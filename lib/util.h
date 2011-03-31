#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <string>
#include "Query.h"
using namespace std;

namespace util
{
    void quit_if_requested(string user_input, Lexicon &lexicon, UrlTable &url_table)
    {
        if( !user_input.compare( "quit" ) ) {
            lexicon.clear();
            url_table.clear();
            exit( 0 );
        }
    }

    int collect_queries(string user_input, vector<Query> &queries)
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

    string search_or_quit(Lexicon &lexicon, UrlTable &url_table)
    {
        string user_input;

        cout << "Search or 'QUIT' to quit: ";
        getline( cin, user_input );

        transform( user_input.begin(), user_input.end(), user_input.begin(), ::tolower );

        quit_if_requested( user_input, lexicon, url_table );

        return user_input;
    }
}

#endif
