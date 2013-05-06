#include "indexer.h"

indexer::indexer()
{

}

indexer::~indexer()
{
    for (map<string,vector<word_position>*>::iterator it=m_words.begin(); it!=m_words.end(); ++it)
    {
         delete it->second;
    }
}

void indexer::add_word(string str,word_position index)
{
    if (m_words[str])
    {
        m_words[str]->push_back(index);
    }
    else
    {
        m_words[str] = new vector<word_position>(1,index);
    }
}

vector<word_position> *indexer::find_word(string str)
{
    return m_words[str];
}
