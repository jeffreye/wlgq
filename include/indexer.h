#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>
#include "types.h"

using namespace std;

class indexer
{
public:
    indexer();
    virtual ~indexer();
    const string &get_document_id(string doc);
    const unordered_set<string> &get_documents(){return docs;}


    /** \brief  add word and its position(ATTENTION:this member function is not thread-safe)
     *
     * \param str string word
     * \param path string path of file
     * \param pos int position in file
     * \return void
     *
     */
    void add_word(string str,string path,int pos);
    void add_word(string str,word_position *pos);
    void add_word(token t);
    vector<word_position*> &find_word(string str);

protected:
private:
    unordered_set<string> docs;
    unordered_map<string,vector<word_position*> > m_words;
};

#endif // DOCUMENT_INDEXER_H
