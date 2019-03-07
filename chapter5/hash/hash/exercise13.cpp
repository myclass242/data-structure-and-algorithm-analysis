#include "exercise13.h"
#include "hash.h"

int findString(const std::string & ori, const std::string & target)
{
    Hash<std::string> hash;

    const auto targetLength = target.length();
    const auto oriLength = ori.length();
    const std::size_t targetHash = hash(target);
    std::size_t oriPreHashVal = hash(ori, 0, targetLength);

    if (targetHash == oriPreHashVal && target == ori.substr(0, targetLength))
    {
        return 0;
    }

    int index = 1;
    for (; index < oriLength - targetLength + 1; ++index)
    {
        oriPreHashVal = hash(ori, index, targetLength, oriPreHashVal);
        if (targetHash == oriPreHashVal && target == ori.substr(index, targetLength))
        {
            return index;
        }
    }
    return -1;
}
