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



void PathFinder::findPath(unsigned targetId, Path &path, unsigned sourceId)
{
    if(firstIsBeter(m_bestPath, path))
        return;

    if(canBeNext(m_dict[sourceId], m_dict[targetId]))
    {
        m_bestPath = path;
        return;
    }


    for(unsigned i=0; i<m_dict.size(); ++i)
        if( std::find(path.begin(), path.end(), i) == path.end())
            if(canBeNext(m_dict[i], m_dict[sourceId]))
            {
                path.insert(path.end(),i);
                findPath(targetId, path, i);
                //path.erase(i);
                path.pop_back();
            }
}

bool PathFinder::find(unsigned source, unsigned target)
{
    if(source >= m_dict.size() || target >= m_dict.size() || source == target)
        return false;
    
    Path path;
    path.insert(path.end(),source);
    findPath(target, path, source);
    if(m_bestPath.size()>0)
    {
        m_bestPath.insert(m_bestPath.end(),target);
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
