#include"expand_file.h"
#include<fstream>

void ExpandFile(const std::string &fileName)
{
    std::string line;
    std::ifstream inFile(fileName);
    if(!inFile.is_open())
    {
        return;
    }
    while(std::getling(inFile,line))
    {
        auto posBegin=line.find("#include",0);
        if(pos!=std::string::npos)
        {

        }
    }
}
