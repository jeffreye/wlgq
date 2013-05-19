#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <indexer.h>
#include <algorithm>
#include <map>

using namespace std;

class query
{
public:
    friend class query_operator;

    query();
    query(vector<word_position*> &res,string w);

    string get_query_words();

    int size(){return results.size();}

    template<typename Function>
    void for_each(Function f)
    {
        std::for_each(results.begin(),results.end(),[f](pair<int,word_position*> p) mutable {f(p.second);});
    }
    virtual ~query();
protected:
//    vector<word_position*> results;
    multimap<int,word_position*> results;
    string words;
private:
};


class query_operator
{
public:
    query_operator();
    virtual ~query_operator();

    virtual query& operator_or(query &l,query r);
    virtual query& operator_and(query &l,query r);

};


#endif // QUERY_H
