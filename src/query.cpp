#include "query.h"
#include <algorithm>

query::query()
    :words("NONE")
{

}

query::query(vector<word_position> &res,string w)
    :results(res),words(w)
{

}

string query::get_query_words()
{
    return words;
}

query::~query()
{
    cout<<"query:"<<words<<" destructed"<<endl;
//    delete results;
}

query &query_operator::operator_and(query &l, query r)
{
    vector<word_position> results;
    for (vector<word_position>::iterator lit=l.results.begin(); lit!=l.results.end(); ++lit )
    {
        for (vector<word_position>::iterator rit=r.results.begin(); rit!=r.results.end(); ++rit )
        {
            if (lit->document_name == rit->document_name)
            {
                results.push_back(*lit);
                results.push_back(*rit);
                //do this temporarily....
            }
        }
    }

    l.words=l.words+" AND "+r.words;
    l.results=results;
    return l;
}

query &query_operator::operator_or(query &l, query r)
{
    copy(r.results.begin(),r.results.end(),back_inserter(l.results));
    return l;
}

query_operator::~query_operator()
{

}
