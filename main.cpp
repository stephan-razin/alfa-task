#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "PathFinder.h"


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
    else
        std::cout << "no way from source to target" << std::endl;

    return 0;
}