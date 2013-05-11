#include "printer.h"
#include <boost/bind.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

printer::printer()
{
    //ctor
}

printer::~printer()
{
    //dtor
}

void printer::printAll(query &result)
{
    //now just print raw result
    result.for_each(boost::bind(boost::mem_fn(&printer::print),this,_1));
    cout<<"QUERY:"<<result.get_query_words()<<endl;
    cout<<"about "<<result.size()<<" results"<<endl;
}

void printer::print(word_position *pos)
{
    cout<<"File:"<<pos->document<<endl;

    ifstream fin;
    fin.open(pos->document);
    fin.seekg(pos->position);
    int line=3;
    string l;
    while (line-->0)
    {
        getline(fin,l);
        hightlight(l,35);
        cout<<endl;
    }
    fin.close();

    cout<<endl;
}


void printer::hightlight(string s,int color,bool bold)
{
    cout << "\033["<< (bold?"1":"0") <<";" << color << "m"<<s<<"\033[0m";

//    for (int i = 31; i <= 37; i++)
//{
//std::cout << "\033[0;" << i << "mHello!\033[0m" << std::endl;
//std::cout << "\033[1;" << i << "mHello!\033[0m" << std::endl;
//}
}
