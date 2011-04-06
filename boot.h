#ifndef BOOT_H
#define BOOT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "page_stats.h"
using namespace std;

namespace boot
{
    void load_lexicon(map<string, int> &lexicon)
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

    void  load_url_table(map<int, page_stats> &url_table)
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

    void init(map<string, int> &lexicon, map<int, page_stats> &url_table)
    {
        cout << "Booting Query Processor" << endl;
        load_lexicon( lexicon );
        load_url_table( url_table );
    }
}

#endif
