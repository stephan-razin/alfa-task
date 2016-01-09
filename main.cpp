#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_set>

typedef std::vector<std::string> Dict;
typedef std::unordered_set<unsigned> Path;

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


Path m_bestPath;
void findPath(const unsigned sourceId, const unsigned targetId, const Dict &dict, const Path path)
{
    if(canBeNext(dict[sourceId], dict[targetId]))
    {
        for(Path::const_iterator it = path.begin(); it != path.end(); ++it)
            std::cout << dict[*it] << std::endl;
        std::cout << dict[targetId] << std::endl;
        if(!m_bestPath.size() || path.size()+1<m_bestPath.size())
        {
            m_bestPath = path;
            m_bestPath.insert(sourceId);
        }
        return;
    }
    

    for(unsigned i=0; i<dict.size(); ++i)
    {
        if(canBeNext(dict[i], dict[sourceId]))
        {
            if( path.find(i) == path.end())
            {
                Path pathCopy = path;
                pathCopy.insert(i);
                findPath(i, targetId, dict, path);
            }
        }
    }
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
    
    Path path;
    path.insert(sourceTarget.first);
    findPath(sourceTarget.first, sourceTarget.second, dict, path);

    return 0;
}