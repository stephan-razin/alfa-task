#ifndef READDATATESTER_H
#define READDATATESTER_H

#include "readData.h"
#include <fstream>
#include <sstream>
#include <string>

bool ReadDataTest()
{

    {
        std::cout << "1. empty data" << std::endl;
        std::istringstream s1, s2;
        std::pair<unsigned, unsigned> res = readData(s1, s2, NULL);
        if(res.first != res.second && res.second != 0)
            return false;
        std::cout << " passed" << std::endl;
    }

    {
        std::cout << "2. equal source and target" << std::endl;
        std::istringstream ts("123\n123"), ds("123\n456\n789");
        std::vector<std::string> dict;
        std::pair<unsigned, unsigned> res = readData(ts, ds, &dict);
        if(res.first != res.second && res.second != 0)
            return false;
        std::cout << " passed" << std::endl;
    }
    {
        std::cout << "3. no source in dict" << std::endl;
        std::istringstream ts("123\n456"), ds("12333\n456\n789\012");
        std::vector<std::string> dict;
        std::pair<unsigned, unsigned> res = readData(ts, ds, &dict);
        if(res.first != res.second && res.second != 0)
            return false;
        std::cout << " passed" << std::endl;
    }
    {
        std::cout << "4. no target in dict" << std::endl;
        std::istringstream ts("123\n456"), ds("000\n789\012\n456789");
        std::vector<std::string> dict;
        std::pair<unsigned, unsigned> res = readData(ts, ds, &dict);
        if(res.first != res.second && res.second != 0)
            return false;
        std::cout << " passed" << std::endl;
    }
    {
        std::cout << "5. wrong data task" << std::endl;
        std::istringstream ts("123"), ds("123\n456\n789\n");
        std::vector<std::string> dict;
        std::pair<unsigned, unsigned> res = readData(ts, ds, &dict);
        if(res.first != res.second && res.second != 0)
            return false;
        std::cout << " passed" << std::endl;
    }
    {
        std::cout << "6. wrong data dict" << std::endl;
        std::istringstream ts("123\n456"), ds("12345689");
        std::vector<std::string> dict;
        std::pair<unsigned, unsigned> res = readData(ts, ds, &dict);
        if(res.first != res.second && res.second != 0)
            return false;
        std::cout << " passed" << std::endl;
    }
    {
        std::cout << "7. normal case" << std::endl;
        std::istringstream ts("123\n456"), ds("123\n123123\n11111\n111\n678\n456\n213gjh12\nhjj\nuiqoweoiuqw\n23094890238409\n");
        std::vector<std::string> dict;
        std::pair<unsigned, unsigned> res = readData(ts, ds, &dict);
        if(res.first != 0 && res.second != 3 && dict.size() != 5)
            return false;
        std::cout << " passed" << std::endl;
    }
    return true;
}
#endif
