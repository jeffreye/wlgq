#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <string>
#include <vector>

using namespace std;

class parser
{
public:
    parser();
    virtual ~parser();


    query parse(string cmd);
protected:
private:
};

#endif // COMMANDPARSER_H
