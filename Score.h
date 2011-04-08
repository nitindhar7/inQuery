#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Score
{
    public:
        Score();
        Score(string, double);
        string get_url() const;
        double get_score() const;
    
    private:
        string url;
        double score;
};

#endif
