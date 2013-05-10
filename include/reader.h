#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>
#include "indexer.h"
#include "types.h"

using namespace std;

/**< read a word from stream (the code is modified from operator>>(istream,string) of SGI STL http://www.sgi.com/tech/stl/string) */
template <class _CharT, class _Traits, class _Alloc>
inline basic_istream<_CharT, _Traits>&
read_word(basic_istream<_CharT, _Traits>& __is,
            basic_string<_CharT,_Traits,_Alloc>& __s)
{
    basic_streambuf<_CharT, _Traits>* __buf = __is.rdbuf();

    __s.clear();

    while (true)
    {
        typename _Traits::int_type __c1 = __buf->sbumpc();
        if (_Traits::eq_int_type(__c1, _Traits::eof()))
        {
            __is.setstate(ios_base::eofbit);
            break;
        }
        else
        {
            _CharT __c = _Traits::to_char_type(__c1);

            if (!isalnum(__c))
                break;
            else
                __s.push_back(tolower(__c));
        }
    }


    return __is;
}



template <typename StreamType >
class reader
{

public:
    StreamType base_stream;

    reader(const string &document)
        :doc(document)
    {
    }

    virtual ~reader()
    {

    }

    bool eof()
    {
        return base_stream.eof();
    }

    virtual void read_token(token &t)
    {
        t.pos=new word_position {doc};
        do
        {
            t.pos->position=base_stream.tellg();
            read_word(base_stream,t.word);

        }
        while(t.word.empty()&&!base_stream.eof());
    }
protected:
    const string &doc;
private:
};



template <class StreamType >
reader<StreamType> &operator>>(reader<StreamType> &r,token &t)
{
    r.read_token(t);
    return r;
}


#endif // READER_H
