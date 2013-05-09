#include "indexer.h"
#include <algorithm>

indexer::indexer()
{

}

void delete_pos(word_position *p)
{
    delete p;
}

void vec_enumerator(pair<string,vector<word_position*> > p)
{
    for_each(p.second.begin(),p.second.end(),delete_pos);
}

indexer::~indexer()
{
    for_each(m_words.begin(),m_words.end(),vec_enumerator);
}

const string &indexer::get_document_id(string filename)
{

    pair<unordered_set<string>::iterator,bool> it=docs.insert(filename);

    return *(it.first);
}

void indexer::add_word(string str, string filename, int pos)
{
    add_word(str,new word_position{get_document_id(filename),pos});
}

    void indexer::add_word(token t)
    {
    m_words[t.word].push_back(t.pos);
    }

void indexer::add_word(string str, word_position* pos)
{
    m_words[str].push_back(pos);
}

vector<word_position*> &indexer::find_word(string str)
{
    return m_words[str];
}
