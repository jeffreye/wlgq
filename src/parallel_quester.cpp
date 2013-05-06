#include "parallel_quester.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>

using namespace boost;


parallel_quester::parallel_quester(query_operator* o)
        :quester(o)
{

}

void parallel_quester::read_documents(vector<path> files)
{
    thread **works=new thread*[files.size()];
    for (size_t i=0;i<files.size() ;++i )
    {
        Callable c;
        c.quester=this;
        c.name=files[i];
        works[i]=new thread(c);
    }

    for (size_t i=0;i<files.size() ;++i )
    {
        works[i]->join();
        delete works[i];
    }
    delete [] works;
}

void parallel_quester::read(path name)
{
    this->read_single_document(name);
}
