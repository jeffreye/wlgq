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

void indexer::add_word(string str, string filename, int pos)
{
    m_words[str].emplace_back(new word_position{filename,pos});
}

void indexer::add_word(string str, word_position* pos)
{
    m_words[str].emplace_back(pos);
}

vector<word_position*> &indexer::find_word(string str)
{
    return m_words[str];
}
