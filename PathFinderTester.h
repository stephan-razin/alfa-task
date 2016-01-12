#ifndef PathFinderTester_H
#define PathFinderTester_H

#include "PathFinder.h"
#include <iostream>

bool PathFinderTest()
{

    {
        std::cout << "1. empty dict" << std::endl;
        Dict dict;
        PathFinder finder(dict);
        if(finder.find(0,1) != false)
            return false;
        if(finder.find(1,0) != false)
            return false;
        if(finder.find(1,2) != false)
            return false;

        std::cout << " passed" << std::endl;
    }

    {
        std::cout << "2. no way" << std::endl;
        std::string data[] ={"aa", "bb", "cc"};
        Dict dict(data, data+sizeof(data)/sizeof(data[0]));
        PathFinder finder(dict);
        if(finder.find(0,2) != false)
            return false;
        if(finder.find(0,1) != false)
            return false;
        if(finder.find(1,2) != false)
            return false;
        std::cout << " passed" << std::endl;
    }

    {
        std::cout << "3. source = target" << std::endl;
        std::string data[] ={"aa", "ab", "bb"};
        Dict dict(data, data+sizeof(data)/sizeof(data[0]));
        PathFinder finder(dict);
        if(finder.find(0,0) != false)
            return false;
        if(finder.find(1,1) != false)
            return false;
        if(finder.find(2,2) != false)
            return false;

        std::cout << " passed" << std::endl;
    }


    {
        std::cout << "4. dict with duplicates" << std::endl;
        std::string data[] ={"aa", "aa", "aa","ab", "ab", "ab", "ba", "bb"};
        Dict dict(data, data+sizeof(data)/sizeof(data[0]));
        PathFinder finder(dict);
        if(finder.find(0,7) != true || finder.pathLenght() !=3)
            return false;
        if(finder.find(7,0) != true || finder.pathLenght() !=3)
            return false;
        if(finder.find(1,7) != true || finder.pathLenght() !=3)
            return false;
        if(finder.find(7,1) != true || finder.pathLenght() !=3)
            return false;

        std::cout << " passed" << std::endl;
    }


    {
        std::cout << "5. normal search" << std::endl;
        std::string data[] ={"CB","GB","MB","QB","JC","JF","MF","JG","GH","DH","DG","AC",};
        Dict dict(data, data+sizeof(data)/sizeof(data[0]));
        PathFinder finder(dict);
        if(finder.find(0,11) != true || finder.pathLenght() !=6)
            return false;
        Path res = finder.path();
        unsigned shouldBee[6] = {0,2,6,5,4,11};
        if(!std::equal(res.begin(), res.end(), shouldBee))
            return false;
        std::cout << " passed" << std::endl;
    }
    return true;
}




#endif