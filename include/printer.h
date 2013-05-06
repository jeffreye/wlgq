#include <iostream>
#include <query.h>
#ifndef PRINTER_H
#define PRINTER_H

using namespace std;

class query;

class printer
{
    public:
        printer();
        virtual ~printer();

        void printAll(query result);
        virtual void print(word_position pos);
        virtual void hightlight(string s,int color,bool bold=false);
    protected:
    private:
};

#endif // PRINTER_H
