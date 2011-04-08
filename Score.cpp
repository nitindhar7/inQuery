#include "config.h"
#include "Score.h"
using namespace std;

Score::Score()
{
    url = "";
    score = 0;
}

Score::Score(string new_url, double new_score)
{
    url = new_url;
    score = new_score;
}

string Score::get_url() const { 
    return url;
}

double Score::get_score() const { 
    return score;
}
