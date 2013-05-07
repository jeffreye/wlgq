#include "printer.h"
#include <boost/bind.hpp>
#include <algorithm>

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
    std::for_each(result.results.begin(),result.results.end(),boost::bind(boost::mem_fn(&printer::print),this,_1));
    cout<<"QUERY:"<<result.get_query_words()<<endl;
    cout<<"AMOUNT:"<<result.results.size()<<endl;
}

void printer::print(word_position *pos)
{
    cout<<"File:"<<pos->document_name<<"\t\t\tPosition:"<<pos->position<<endl;
}


void printer::hightlight(string s,int color,bool bold)
{
    cout << "\033["<< (bold?"1":"0") <<";" << color << "mHello!\033[0m";

//    for (int i = 31; i <= 37; i++)
//{
//std::cout << "\033[0;" << i << "mHello!\033[0m" << std::endl;
//std::cout << "\033[1;" << i << "mHello!\033[0m" << std::endl;
//}
}
