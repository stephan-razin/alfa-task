#include "readData.h"
#include <iostream>
#include <string>
#include <algorithm>

std::pair<unsigned, unsigned> readData(std::istream &taskStr,std::istream &dictStr, std::vector<std::string> *dict)
{
    if(!dict) // wrong params
        return std::pair<unsigned, unsigned>(0,0);
    
    std::string source;
    std::string target;
    if( !taskStr ||
        !std::getline(taskStr, source) ||
        !std::getline(taskStr, target))
    {
        std::cout << "can't read task data" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }
    //std::cout << "source word: " << source << std::endl;
    //std::cout << "target word: " << target << std::endl;
    if(source.size() != target.size())
    {
        std::cout << "wrong size for source and tirget" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }

    std::string dictLine;
    while(dictStr && std::getline(dictStr, dictLine))
    {
        if(dictLine.size() != source.size())
            continue; // skip it
        dict->push_back(dictLine);
    }
    if(!dict->size())
    {
        std::cout << "dictionary is empty" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }
    
    std::pair<unsigned, unsigned> result( std::distance(dict->begin(), std::find(dict->begin(), dict->end(), source)),
                                          std::distance(dict->begin(), std::find(dict->begin(), dict->end(), target)) );
    
    if( result.first  == result.second ||
        result.first  == dict->size()   ||
        result.second == dict->size())
    {
        std::cout << "dictionary doesn't contain source or target. or source == target" << std::endl;
        return std::pair<unsigned, unsigned>(0,0);
    }

    //std::cout << "dictionary size is " << dict->size() << std::endl;
    return result;
}






