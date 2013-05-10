#include "quester.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>

using namespace boost::algorithm;

quester::quester(query_operator o)
    :m_operator(o)
{

}

quester::~quester()
{

}

bool quester::is_excluded(string word)
{
    return stopwords.count(word);
}

void quester::execute(string queryString)
{
    //parse the query and
    //process operator of AND,OR,etc...

    //simple implement
    stringstream s;
    s.str(queryString);

    string temp;
    s>>temp;

    query result=create_query(temp);
    while (s>>temp)
    {
        if (temp=="AND")
        {
            s>>temp;
            result=m_operator.operator_and(result,create_query(temp));
        }
        else if (temp=="OR")
        {
            s>>temp;
            result=m_operator.operator_or(result,create_query(temp));
        }
        else
        {
            result=m_operator.operator_and(result,create_query(temp));
        }
    }

    m_printer.printAll(result);
}

query quester::create_query(string keyword)
{
    return query(m_indexer.find_word(keyword),keyword);
}

void quester::read_documents(vector<path> files)
{
    for_each(files.begin(),files.end(),
             boost::bind(&quester::read_single_document,this,_1));
}

void quester::read_stopwords(path filename)
{
    boost::filesystem::ifstream fin;
    fin.open(filename);

    string t;
    while (!fin.eof())
    {
        fin>>t;
        split(stopwords,t,is_any_of(","));//another way:boost tokenizer
    }
    fin.close();
}

void quester::read_single_document(path filename)
{
    const string &doc=m_indexer.get_document_id(filename.generic_string());
    reader<boost::filesystem::ifstream> reader(doc);
    reader.base_stream.open(filename);

    token t;
    while (!reader.eof())
    {
        reader>>t;
        if (is_excluded(t.word))
            continue;
        process(t);
        m_indexer.add_word(t.word,t.pos);
    }
    reader.base_stream.close();
}

void quester::process(token &t)
{
    //process plural forms ,etc....
}


