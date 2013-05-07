#ifndef PARALLEL_QUESTER_H
#define PARALLEL_QUESTER_H
#include <quester.h>
#include <boost/filesystem.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

struct Callable;

class parallel_quester:public quester
{
    public:
        friend struct Callable;
        parallel_quester(query_operator o);
        virtual void read_documents(vector<path> files);
    protected:
    private:
        void read(path name);

};

struct Callable
{
    parallel_quester *quester;
    path name;
    void operator()()
    {
        quester->read(name);
    }
};

#endif // PARALLEL_QUESTER_H
