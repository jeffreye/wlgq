#include "query.h"
#include <algorithm>
#include <boost/bind.hpp>

query::query()
    :words("NONE")
{
//    results = new vector<word_position>;
}

query::query(vector<word_position> &res,string w)
    :words(w)
{
//    results = new vector<word_position>(res);
    results=res;
}

string query::get_query_words()
{
    return words;
}

query::~query()
{
//    cout<<"query:"<<words<<" destructed"<<endl;
//    delete results;
}

query query_operator::operator_and(query l, query r)
{

    query ret;
    for (vector<word_position>::iterator lit=l.results.begin(); lit!=l.results.end(); ++lit )
    {
        for (vector<word_position>::iterator rit=r.results.begin(); rit!=r.results.end(); ++rit )
        {
            if (lit->document_name == rit->document_name)
            {
                ret.results.push_back(*lit);
                ret.results.push_back(*rit);
                //do this temporarily....
            }
        }
    }

    ret.words=l.words+" AND "+r.words;
    return ret;
}

query query_operator::operator_or(query l, query r)
{
    query ret=l;
    copy(r.results.begin(),r.results.end(),back_inserter(ret.results));
    return ret;
}

query_operator::~query_operator()
{

}
