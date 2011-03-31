#ifndef BOOT_H
#define BOOT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

struct page_stats {
    string url;
    int page_size;
};

typedef map<string, int> Lexicon;
typedef map<string, int>::iterator LexiconCursor;
typedef map<int, page_stats> UrlTable;
typedef map<int, page_stats>::iterator UrlTableCursor;

namespace boot
{
    void load_lexicon(Lexicon &lexicon)
    {
        string line, word;
        int offset;
        ifstream lexicon_file;

        lexicon_file.open( "data/lexicon" );
        cout << "* Loading Lexicon... ";

        while( !lexicon_file.eof() ) {
            lexicon_file >> word >> offset;
            lexicon[word] = offset;
        }

        cout << "[DONE]" << endl;
        lexicon_file.close();
    }

    void  load_url_table(UrlTable &url_table)
    {
        page_stats stats;
        string url;
        int doc_id, page_size;
        ifstream url_table_file;

        url_table_file.open( "data/url_table" );
        cout << "* Loading URL Table... ";

        while( !url_table_file.eof() ) {
            url_table_file >> doc_id >> page_size >> url;
            stats.page_size = page_size;
            stats.url = url;
            url_table[doc_id] = stats;
        }

        cout << "[DONE]" << endl << endl;
        url_table_file.close();
    }

    void init(Lexicon &lexicon, UrlTable &url_table)
    {
        cout << "Booting Query Processor" << endl;
        load_lexicon( lexicon );
        load_url_table( url_table );
    }
}

#endif
