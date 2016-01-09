#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_set>


typedef std::vector<std::string> Dict;
typedef std::unordered_set<unsigned> Path;


class PathFinder
{
    const Dict m_dict;
    Path m_bestPath;

    bool canBeNext(const std::string &s1, const std::string &s2)
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





    void findPath(const unsigned sourceId, const unsigned targetId, Path &path)
    {
        if(m_bestPath.size() && path.size()+1>=m_bestPath.size())
            return;

        if(canBeNext(m_dict[sourceId], m_dict[targetId]))
        {
            std::cout << "[" << path.size()+1 <<"] ";
            for(Path::const_iterator it = path.begin(); it != path.end(); ++it)
                std::cout << *it << " -> ";
            std::cout << targetId << std::endl;
            //if(!m_bestPath.size() || path.size()+1<m_bestPath.size())
            {
                m_bestPath = path;
                m_bestPath.insert(targetId);
            }
            return;
        }


        for(unsigned i=0; i<m_dict.size(); ++i)
        {
            if(canBeNext(m_dict[i], m_dict[sourceId]))
            {
                if( path.find(i) == path.end())
                {
                    path.insert(i);
                    findPath(i, targetId, path);
                    path.erase(i);
                }
            }
        }
    }

public:
    PathFinder(const Dict & dict):m_dict(dict)
    {
    }
    
    bool find(unsigned source, unsigned target)
    {
        Path path;
        path.insert(source);
        findPath(source, target, path);
        return m_bestPath.size()>0;
    }

    void print() const
    {
        std::cout << "[" << m_bestPath.size()+1 <<"] ";
        for(Path::const_iterator it = m_bestPath.begin(); it != m_bestPath.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;

        for(Path::const_iterator it = m_bestPath.begin(); it != m_bestPath.end(); ++it)
            std::cout << m_dict[*it] << std::endl;
        std::cout << std::endl;
    }
};




std::pair<unsigned, unsigned> readFiles(const char* taskName, const char * dictName, Dict &dict)
{
    std::string source;
    std::string target;
    std::ifstream tif(taskName);
    if( !tif ||
        !std::getline(tif, source) ||
        !std::getline(tif, target))
    {
        std::cout << "can't read task file [" << taskName << "]" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }
    std::cout << "source word: " << source << std::endl;
    std::cout << "target word: " << target << std::endl;
    if(source.size() != target.size())
    {
        std::cout << "wrong size for source and tirget" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }

    std::ifstream dif(dictName);
    std::string dictLine;
    while(dif && std::getline(dif, dictLine))
    {
        if(dictLine.size() != source.size())
            continue; // skip it
        dict.push_back(dictLine);
    }
    if(!dict.size())
    {
        std::cout << "dictionary is empty" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }
    
    std::pair<unsigned, unsigned> result( std::distance(dict.begin(), std::find(dict.begin(), dict.end(), source)),
                                          std::distance(dict.begin(), std::find(dict.begin(), dict.end(), target)) );
    
    if( result.first  == result.second ||
        result.first  == dict.size()   ||
        result.second == dict.size())
    {
        std::cout << "dictionary doesn't contain source or target" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }

    std::cout << "dictionary size is " << dict.size() << std::endl;
    return result;
}




int main(int argc, char const *argv[])
{
    
    if(argc < 3 || !argv || !argv[1] || !argv[2])
    {
        std::cout << "invalid args" << std::endl;
        return 1;
    }

    Dict dict;

    std::pair<unsigned, unsigned> sourceTarget = readFiles(argv[1], argv[2], dict);
    if(sourceTarget.first == sourceTarget.second)
    {
        std::cout << "read files error" << std::endl;
        return 2;
    }
    
    PathFinder finder(dict);
    if(finder.find(sourceTarget.first, sourceTarget.second))
        finder.print();

    return 0;
}