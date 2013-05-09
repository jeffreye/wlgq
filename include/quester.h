#ifndef QUESTER_H
#define QUESTER_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "indexer.h"
#include "printer.h"
#include "query.h"
#include "reader.h"
#include "types.h"

using namespace std;
using namespace boost::filesystem;

class quester
{
    public:
        quester(query_operator o);
        virtual ~quester();

        virtual void read_documents(vector<path> files);

        void execute(string query);

    protected:
        virtual query create_query(string keyword);
        virtual void read_single_document(path filename);
        void process(token &t);
        indexer m_indexer;
    private:
        printer m_printer;
        query_operator m_operator;
};

#endif // QUESTER_H
