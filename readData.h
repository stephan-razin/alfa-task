#ifndef readData_H
#define readData_H

#include <vector>
#include <istream>

std::pair<unsigned, unsigned> readData(std::istream &taskStr, std::istream &dictStr,  std::vector<std::string> *dict);


#endif
