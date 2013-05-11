#include "quester.h"
#include "parallel_quester.h"
#include "query.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "stopwatch.h"
#define BOOST_DATE_TIME_SOURCE

using namespace std;
using namespace boost::filesystem;

inline vector<path> get_files(path p)
{

    vector<path> paths;
    //modified by qsz ---------------------------------------------------------------
    //copy(directory_iterator(p),directory_iterator(),back_inserter(paths));

    boost::filesystem::recursive_directory_iterator iter(p);
    boost::filesystem::recursive_directory_iterator end;
    for (; iter != end; ++iter)
    {
        if(boost::filesystem::is_regular_file(*iter))
        {
            paths.push_back(iter->path());

        }
    }
//------------------------------------------------------------------------------------------

    return paths;
}

template<typename Function>
void benchmark(Function f)
{
    stopwatch watch;
    watch.start();
    f();
    watch.stop();

    long milliseconds = watch.get_elapse_milliseconds();
    cout<<"time_elapse :"<<milliseconds<<"ms"<<endl;
}

int main()
{
//  ios::sync_with_stdio(false);
    query_operator o;
    quester q(o);


    cout<<"Input the datas' path(default:<current path>/data):";
    string data_path;
    getline(cin,data_path);


    path p;
    if (data_path!="")
        p=data_path;
    else
    {
        p=current_path();
        p+="/data";
        cout<<p<<endl;
    }

#if DEBUG
    benchmark([&q,&p]()mutable
    {
        q.read_stopwords("stopword.txt");
        q.read_documents(get_files(p));
    });
#else
    q.read_stopwords("stopword.txt");
    q.read_documents(get_files(p));
#endif

    string query;
    cout<<"Welcome to our search engine."<<endl;
    cout<<"Please input the text you want to search"<<endl;
    getline(cin,query);

    q.execute(query);//query once and exit

    return 0;
}
