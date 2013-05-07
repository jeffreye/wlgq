#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

typedef struct
{
    string document_name;
    int position;
}word_position;

class indexer
{
public:
    indexer();
    virtual ~indexer();

    void add_word(string str,string filename,int pos);
    void add_word(string str,word_position *pos);
    vector<word_position*> &find_word(string str);

protected:
private:
    unordered_map<string,vector<word_position*> > m_words;
};

#endif // DOCUMENT_INDEXER_H
