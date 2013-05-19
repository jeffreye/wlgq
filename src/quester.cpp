#include "quester.h"
#include "stopwatch.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

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

/**< select best result of each files and sort all of them by ranker */
void reduce_and_sort(query &result,unordered_map<string,int> &ranker)
{
    vector<word_position*> vals;

    result.for_each([&vals](word_position* p) mutable
    {
        if(none_of(vals.begin(),vals.end(),[p](word_position* pos){return pos->document==p->document;}))
         vals.push_back(p);
    });

    sort(vals.begin(),vals.end(),[&ranker](word_position *i,word_position *j){return ranker[i->document]>ranker[j->document];});

    result=query(vals,result.get_query_words());
}

void quester::execute(string queryString)
{
    //parse the query and
    //process operator of AND,OR,etc...

    //simple implement
    //some useful resource:boost::Xpressive ,Lucene(org.apache.lucene.queryparser.classic.QueryParser?),Lemur

    stopwatch watch;
    watch.start();

    stringstream s;
    s.str(queryString);

    string temp;
    s>>temp;

    query result=create_query(temp);
    vector<string> keywords;
    keywords.push_back(temp);
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
            keywords.push_back(temp);
        }
    }

    //rank the files
    unordered_map<string,int> file_rank;
    BOOST_FOREACH(string f,m_indexer.get_documents())
    {
        int ranking=0;
        BOOST_FOREACH(string w,keywords)
            ranking+=word_statistics[f][w];

        file_rank[f]=ranking;
    }
    reduce_and_sort(result,file_rank);

    watch.stop();
    m_printer.printAll(result);
    cout<<"("<<watch.get_elapse_milliseconds()<<"ms)"<<endl;
}

query quester::create_query(string keyword)
{
    if (is_excluded(keyword))
        return query();
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
    word_statistics[t.pos->document][t.word]++;
    //process plural forms ,etc....
}


