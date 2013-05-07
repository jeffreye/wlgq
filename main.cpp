#include "quester.h"
#include "parallel_quester.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

inline vector<path> get_files(string p = "/home/daniel/Desktop/C++/Assignment/data (copy)")
{
    /*path data=current_path();
    data="/home/daniel/Desktop/C++/Assignment/data";

    vector<path> paths;
    copy(directory_iterator(data),directory_iterator(),back_inserter(paths));
    //TODO:filter some unusable files
*/

vector<path> paths;
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

return paths;
}

int main()
{
   //ios::sync_with_stdio(false);

    query_operator *o=new query_operator;
//    parallel_quester q(dynamic_cast<query_operator*>(o));
    quester q(dynamic_cast<query_operator*>(o));

    string query;
    string path;
    cout<<"Welcome to our search engine."<<endl;
    cout <<"please enter the path you want to search(leave blank for debug mode):" << endl;
    getline(cin,path);
    if(path == "")
    {
        q.read_documents(get_files());
    }
    else
    {
        q.read_documents(get_files(path));
    }


    cout<<"Please input the text you want to search"<<endl;
    getline(cin,query);

    q.execute(query);//query once and exit*/
    cout << "done";
    delete o;
    return 0;
}
