#include "sync_query.h"

sync_query::sync_query()
{
    //ctor
}

sync_query::~sync_query()
{
    //dtor
}

query sync_query_operator::operator_or(query l, query r)
{
    throw 0;
}

query sync_query_operator::operator_and(query l, query r)
{
    throw 0;
}
