#include "parallel_quester.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost;


parallel_quester::parallel_quester(query_operator o)
        :quester(o)
{

}

void parallel_quester::read_documents(vector<path> files)
{
    thread_group works;
    for (size_t i=0;i<files.size() ;++i )
    {
        Callable c;
        c.quester=this;
        c.name=files[i];
        works.create_thread(c);
    }
    works.join_all();
}

void parallel_quester::read(path name)
{
    this->read_single_document(name);
}
