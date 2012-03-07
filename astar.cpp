#include "astar.h"

using namespace std;

std::list<AStarNode> AStarAlgorithm::resolve(const AStarNode &start, const AStarNode &goal)
{
    list<AStarNode> closedset;
    list<AStarNode> openset;
    
    openset.push_back(start);

    openset.front().gScore = 0;
    openset.front().hScore = openset.front().heuristicCost(goal);
    openset.front().fScore = openset.front().gScore + openset.front().hScore;
    openset.front().cameFrom = 0;
    
    
    while (openset.size() != 0) {
        list<AStarNode>::iterator it = searchMinimumFScore(openset);
        closedset.push_back(*it);
        openset.erase(it);

        AStarNode *current = &closedset.back();

        if (current->compare(goal))
            return reconstructPath(current->cameFrom);


        list<AStarNode> neighbor = current->neighborNodes();
        for (list<AStarNode>::iterator nei = neighbor.begin(); nei != neighbor.end(); nei++) {
            if (listContain(closedset, nei))
                continue;

            int tentativeGScore = current->gScore + nei->distBetween(current);

            if (!listContain(openset, nei)) {
                nei->hScore = nei->heuristicCost(goal);
                openset.push_back(*nei);

                // ajoute dans openset
                node.gScore = tentativeGScore;
                node.fScore = node.gScore + node.hScore;
                node.cameFrom = current;
            } else if (tentativeGScore < /*modif existant*/) {
                node.gScore = tentativeGScore;
                node.fScore = node.gScore + node.hScore;
                node.cameFrom = current;
            }
        }
    }
    
    return list<AStarNode>();
}

list::iterator AStarAlgorithm::searchMinimumFScore(list &list)
{
}

list AStarAlgorithm::reconstructPath(AStarNode *current)
{
}

bool AStarAlgorithm::listContain(list<AStarNode> &list, list<AStarNode>::iterator it)
{
}
