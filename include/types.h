#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#include <string>

using namespace std;

typedef struct
{
    const string &document;
    int position;
} word_position;

typedef struct
{
    string word;
    word_position *pos;
} token;

#endif // TYPES_H_INCLUDED
