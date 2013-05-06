#include "sync_query.h"
#include "quester.h"
#include "parallel_quester.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

inline vector<path> get_files()
{
    path data=current_path();
    data+="/data";

    vector<path> paths;
    copy(directory_iterator(data),directory_iterator(),back_inserter(paths));
    //TODO:filter some unusable files

    return paths;
}

int main()
{
    ios::sync_with_stdio(false);

    query_operator *o=new query_operator;
//    parallel_quester q(dynamic_cast<query_operator*>(o));
    quester q(dynamic_cast<query_operator*>(o));

    q.read_documents(get_files());

    string query;
    cout<<"Welcome to our search engine."<<endl;
    cout<<"Please input the text you want to search"<<endl;
    getline(cin,query);

    q.execute(query);//query once and exit

    delete o;
    return 0;
}
