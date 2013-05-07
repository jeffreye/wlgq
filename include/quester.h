#ifndef QUESTER_H
#define QUESTER_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "indexer.h"
#include "printer.h"
#include "query.h"

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
        void read_single_document(path filename);
        indexer m_indexer;
    private:
        printer m_printer;
        query_operator m_operator;
};

#endif // QUESTER_H
