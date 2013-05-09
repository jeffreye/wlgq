#ifndef PARALLEL_QUESTER_H
#define PARALLEL_QUESTER_H
#include "quester.h"
#include "reader.h"
#include <boost/filesystem.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <string>
#include <unordered_set>

/** WARNING: Here are some bugs and uncompleted code.
 */

class parallel_quester:public quester
{
    public:
        parallel_quester(query_operator o);
        virtual void read_documents(vector<path> files);
    protected:
        virtual void read_single_document(path path);
    private:
        void process_task();
        boost::lockfree::spsc_queue<token,boost::lockfree::capacity<65535> > string_queue;

        boost::atomic<int> counter;
        inline bool readDone(){ return counter==0;};

};

#endif // PARALLEL_QUESTER_H
