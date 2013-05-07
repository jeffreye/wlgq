#include "quester.h"
#include "parallel_quester.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#define BOOST_DATE_TIME_SOURCE

using namespace std;
using namespace boost::filesystem;

inline vector<path> get_files(path p)
{

    vector<path> paths;
    //modified by qsz ---------------------------------------------------------------
    //copy(directory_iterator(p),directory_iterator(),back_inserter(paths));
    //TODO:filter some unusable files


        boost::filesystem::path path(p);
        boost::filesystem::recursive_directory_iterator iter(path);
        boost::filesystem::recursive_directory_iterator end;
        for (; iter != end; ++iter)
        {
            if(boost::filesystem::is_regular_file(*iter))
            {
                //cout << iter->path().leaf().string() << endl;
               paths.push_back(iter->path());

            }
        }
//------------------------------------------------------------------------------------------
    return paths;
}

void read_documents(quester &quester,vector<path> files)
{
    boost::posix_time::ptime time1,time_now;
    boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;

    time1 = boost::posix_time::microsec_clock::universal_time();

    quester.read_documents(files);

    time_now = boost::posix_time::microsec_clock::universal_time();

    time_elapse = time_now - time1;


    long milliseconds = time_elapse.total_milliseconds();
    cout<<"time_elapse :"<<milliseconds<<"ms"<<endl;
}

class test:public query_operator {};;


int main()
{
//    ios::sync_with_stdio(false);
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
    read_documents(q,get_files(p));
#else
    q.read_documents(get_files(p));
#endif

    string query;
    cout<<"Welcome to our search engine."<<endl;
    cout<<"Please input the text you want to search"<<endl;
    getline(cin,query);

    q.execute(query);//query once and exit

    return 0;
}
