#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef struct
{
    string document_name;
    int position;
}word_position;



typedef void (*action)(string str,vector<word_position>* indexes);

class indexer
{
public:
    indexer();
    virtual ~indexer();

    void add_word(string str,word_position index);
    vector<word_position> *find_word(string str);

    void foreach(action f);
protected:
private:
    map<string,vector<word_position>*> m_words;
};

#endif // DOCUMENT_INDEXER_H
