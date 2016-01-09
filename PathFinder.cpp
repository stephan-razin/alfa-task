#include "PathFinder.h"

#include <iostream>
#include <algorithm>


bool PathFinder::canBeNext(const std::string &s1, const std::string &s2)
{
    if(s1.size()!=s2.size())
        return false;

    unsigned count = 0;
    for(unsigned i=0; i<s1.size(); ++i)
        if(s1.at(i) != s2.at(i))
            if(count++ > 1)
                return false;
    return count == 1;
}

bool PathFinder::firstIsBeter(const Path &f, const Path &s)
{
    return (f.size() && f.size()<=s.size());
}



void PathFinder::findPath(unsigned targetId, Path &path)
{
    if(firstIsBeter(m_bestPath, path))
        return;

    unsigned sourceId = *(--(path.end()));
    if(canBeNext(m_dict[sourceId], m_dict[targetId]))
    {
        m_bestPath = path;
        return;
    }


    for(unsigned i=0; i<m_dict.size(); ++i)
        if( path.find(i) == path.end())
            if(canBeNext(m_dict[i], m_dict[sourceId]))
            {
                path.insert(i);
                findPath(targetId, path);
                path.erase(i);
            }
}

bool PathFinder::find(unsigned source, unsigned target)
{
    Path path;
    path.insert(source);
    findPath(target, path);
    if(m_bestPath.size()>0)
    {
        m_bestPath.insert(target);
        return true;
    }
    return false;
}

void PathFinder::print() const
{
    for(Path::const_iterator it = m_bestPath.begin(); it != m_bestPath.end(); ++it)
        std::cout << m_dict[*it] << std::endl;
    std::cout << std::endl;
}
