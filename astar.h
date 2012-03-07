#ifndef _ASTAR_H_
#define _ASTAR_H_

#include <list>
#include <map>

class AStarAlgorithm;

class AStarNode {
public:
    virtual int heuristicCost(const AStarNode &goal) const = 0;
    virtual bool compare(const AStarNode &other) const = 0;
    virtual bool lessThan(const AStarNode &other) const = 0;
    virtual std::list<AStarNode> neighborNodes() const = 0;
    virtual int distBetween(const AStarNode *other) const = 0;

    bool operator ==(const AStarNode &other) const; 
    bool operator <(const AStarNode &other) const;
    
private:
    int gScore;
    int hScore;
    int fScore;
    AStarNode *cameFrom;
    
    friend class AStarAlgorithm;
};

class AStarAlgorithm {
public:
    static std::list<AStarNode> resolve(const AStarNode &start, const AStarNode &goal);
    
private:
    static std::list<AStarNode>::iterator searchMinimumFScore(std::list<AStarNode> &list);
    static std::list<AStarNode> reconstructPath(AStarNode *current);
    static bool listContain(std::list<AStarNode> &list, std::list<AStarNode>::iterator it);
};

#endif // _ASTAR_H_
