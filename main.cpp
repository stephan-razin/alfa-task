#include <iostream>



int main(int argc, char const *argv[])
{
    
    if(argc < 2 || !argv || !argv[0] || !argv[1])
    {
        std::cout << "invalid args" << std::endl;
        return 1;
    }

    std::cout << "ok" << std::endl;

    return 0;
}