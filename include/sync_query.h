#ifndef SYNC_QUERY_H
#define SYNC_QUERY_H

#include <query.h>


class sync_query : public query
{
    public:
        sync_query();
        virtual ~sync_query();
    protected:
    private:
};

class sync_query_operator:public query_operator
{
    public:
        virtual query operator_or(query l,query r);
        virtual query operator_and(query l,query r);
    private:

};


#endif // SYNC_QUERY_H
