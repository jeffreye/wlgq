#include "query.h"
#include <algorithm>

query::query()
    :words("NONE")
{

}

query::query(vector<word_position*> &res,string w)
    :words(w)
{
    std::for_each(res.begin(),res.end(),[this](word_position *p) mutable {this->results.insert(make_pair(0,p));});
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
    if (l.words=="NONE")
        return l=r;
    else if(r.words=="NONE")
        return l;

    //todo:order the results and optimize performance
    multimap<int,word_position*> results;
    for (auto lit=l.results.begin(); lit!=l.results.end(); ++lit )
    {
        word_position *left=lit->second;
        for (auto rit=r.results.begin(); rit!=r.results.end(); ++rit )
        {
            word_position *right=rit->second;
            if (left->document==right->document)
            {
                //insert the former postion
                //results will be ordered by abs(delta)
                //(but it seems some bugs in here...)
                auto delta=left->position-right->position;
                if (delta<0)
                    results.insert(make_pair(-delta,left));
                else
                    results.insert(make_pair(delta,right));
            }
        }
    }
    l.results=results;
    l.words=l.words+" AND "+r.words;
    return l;
}

query &query_operator::operator_or(query &l, query r)
{
    for_each(r.results.begin(),r.results.end(),[l](pair<int,word_position*> p) mutable {l.results.insert(p);});
    l.words=l.words+" OR "+r.words;
    return l;
}

query_operator::~query_operator()
{

}
