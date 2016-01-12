#ifndef PathFinder_H
#define PathFinder_H


#include <vector>
#include <string>
#include <unordered_set>

typedef std::vector<std::string> Dict;
typedef std::unordered_set<unsigned> Path;


class PathFinder
{
    const Dict m_dict;
    Path       m_bestPath;

    static bool canBeNext(const std::string &s1, const std::string &s2);
    static bool firstIsBeter(const Path &f, const Path &s);

    void findPath(unsigned targetId, Path &path, unsigned sourceId);

public:
    PathFinder(const Dict & dict):m_dict(dict){}
    
    bool find(unsigned source, unsigned target);
    unsigned pathLenght()const{return m_bestPath.size();}
    Path path()const{return m_bestPath;}
    void print() const;
};

#endif