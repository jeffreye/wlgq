#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <indexer.h>
#include "printer.h"

using namespace std;

class printer;

class query
{
public:
    friend class query_operator;
    friend class printer;

    query();
    query(vector<word_position*> &res,string w);

    string get_query_words();
    virtual ~query();
protected:
    vector<word_position*> results;
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
