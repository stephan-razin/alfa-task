#include <iostream>
#include <map>
#include <string>
#include <fstream>

typedef std::map<std::string, bool> Dict;

bool readFiles(const char* taskName, const char * dictName, std::string &source, std::string &target, Dict &dict)
{
    std::ifstream tif(taskName);
    if( !tif ||
        !std::getline(tif, source) ||
        !std::getline(tif, target))
    {
        std::cout << "can't read task file [" << taskName << "]" << std::endl;
        return false;
    }
    std::cout << "source word: " << source << std::endl;
    std::cout << "target word: " << target << std::endl;
    if(source.size() != target.size())
    {
        std::cout << "wrong size for source and tirget" << std::endl;
        return false;
    }

    std::ifstream dif(dictName);
    std::string dictLine;
    while(dif && std::getline(dif, dictLine))
    {
        if(dictLine.size() != source.size())
            continue; // skip it
        dict[dictLine] = false; // in use - false
    }
    if(!dict.size())
    {
        std::cout << "dictionary is empty" << std::endl;
        return false;
    }
    std::cout << "dictionary size is " << dict.size() << std::endl;
    return true;
}







int main(int argc, char const *argv[])
{
    
    if(argc < 3 || !argv || !argv[1] || !argv[2])
    {
        std::cout << "invalid args" << std::endl;
        return 1;
    }

    std::string source, dest;
    Dict dict;

    if(!readFiles(argv[1], argv[2], source, dest, dict))
    {
        std::cout << "read files error" << std::endl;
        return 2;
    }
    

    return 0;
}