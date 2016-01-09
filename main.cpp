#include <iostream>
#include <fstream>
#include "readData.h"
#include "PathFinder.h"

#include "PathFinderTester.h"
#include "readDataTester.h"

int main(int argc, char const *argv[])
{
    
    if(argc < 3 || !argv || !argv[1] || !argv[2])
    {
        std::cout << "invalid args" << std::endl;
        std::cout << "start self tests" << std::endl;
        if(!PathFinderTest())
            std::cout << "test error!" << std::endl;
        if(!ReadDataTest())
            std::cout << "test error!" << std::endl;
        return 1;
    }

    Dict dict;
    std::ifstream taskFile(argv[1]);
    std::ifstream dictFile(argv[2]);
    std::pair<unsigned, unsigned> sourceTarget = readData(taskFile, dictFile, &dict);
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