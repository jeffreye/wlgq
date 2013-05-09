#include "parallel_quester.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>

using namespace std;
using namespace boost;

parallel_quester::parallel_quester(query_operator o)
    :quester(o)
{

}

void parallel_quester::read_documents(vector<path> files)
{
    counter=files.size();
    thread task(bind(&parallel_quester::process_task,this));
    for (size_t i=0; i<files.size() ; ++i )
        read_single_document(files[i]);
    task.join();
}

void parallel_quester::read_single_document(path filename)
{
    const string &doc=m_indexer.get_document_id(filename.generic_string());
    reader<boost::filesystem::ifstream> reader(doc);
    reader.base_stream.open(filename);

    token t;
    while (!reader.eof())
    {
        reader>>t;

        while(string_queue.push(t));

    }
    reader.base_stream.close();

    --counter;
}

void parallel_quester::process_task()
{
    token item;
    while (!readDone())
    {
        while (string_queue.pop(item))
        {
            process(item);
            m_indexer.add_word(item);
        }
    }

    while (string_queue.pop(item))
    {
        process(item);
        m_indexer.add_word(item);
    }
}
