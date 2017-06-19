#include"permute.h"
#include<algorithm>
#include<utility>

std::vector<std::string> permute(const std::string &str)
{
    std::vector<std::string> vs{};
    if(str.size() == 1)
    {
        vs.push_back(str);
        return vs;
        //return vs;
    }
    else if(str.size() == 0)
    {
        return vs;
    }
    //auto temStr = str[0];
    auto temStr = str.substr(0, 1);
    vs = permute(str.substr(1));
    std::vector<std::string> retVs{};
    for(const auto &elmStr:vs)
    {
        for(auto iteBegin = elmStr.cbegin(); iteBegin != elmStr.cend(); ++iteBegin)
        {
            std::string containChar = elmStr;
            containChar.insert(iteBegin - elmStr.cbegin(),temStr);
            retVs.push_back(containChar);
        }
        std::string containCharEnd = elmStr;
        //containCharEnd.push_back(temStr);
        containCharEnd.insert(containCharEnd.end() - containCharEnd.begin(),temStr);
        retVs.push_back(containCharEnd);
    }
    return retVs;
    //return retVs;
}
