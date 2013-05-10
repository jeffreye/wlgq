#include "query.h"
#include <algorithm>

query::query()
    :words("NONE")
{

}

query::query(vector<word_position*> &res,string w)
    :results(res),words(w)
{

}

string query::get_query_words()
{
    return words;
}

query::~query()
{

}

query_operator::query_operator()
{

}

query &query_operator::operator_and(query &l, query r)
{
    vector<word_position*> &results=l.results;
    for (vector<word_position*>::iterator lit=l.results.begin(); lit!=l.results.end(); ++lit )
    {
        for (vector<word_position*>::iterator rit=r.results.begin(); rit!=r.results.end(); ++rit )
        {
            if ((*lit)->document == (*rit)->document)
            {
                results.push_back(*lit);
                results.push_back(*rit);
                //do this temporarily....
            }
        }
    }

    l.words=l.words+" AND "+r.words;
    return l;
}

query &query_operator::operator_or(query &l, query r)
{
    copy(r.results.begin(),r.results.end(),back_inserter(l.results));
    l.words=l.words+" OR "+r.words;
    return l;
}

query_operator::~query_operator()
{

}
