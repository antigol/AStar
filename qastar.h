#ifndef QASTAR_H
#define QASTAR_H

#include <QList>
#include <QSet>
#include <QHash>

template <class Node>
class QAStar
{
    class NodeInfo
    {
    public:
        NodeInfo()
            : gScore(0), hScore(0), fScore(0), comeFrom(Node())
        {
        }

        NodeInfo(int g, int h, Node comeFrom)
            : gScore(g), hScore(h), fScore(g + h), comeFrom(comeFrom)
        {
        }

        int gScore; // prix depuis start
        int hScore; // prix estimé pour aller au goal
        int fScore; // prix total (g + h)
        Node comeFrom;
    };

public:
    QAStar()
    {
    }

    QList<Node> findPath(const Node &start, const Node &goal)
    {
        QSet<Node> closedset;
        QSet<Node> openset;
        QHash<Node, NodeInfo> infos;

        {
            int h = heuristicCostEstimate(start, goal);
            infos[start] = NodeInfo(0, h, start);

            openset.insert(start);
        }

        while (!openset.isEmpty()) {
            Node current = bestFromOpenSet(openset, infos);
            if (current == goal) {
                return reconstructPath(current, infos);
            }

            openset.remove(current);
            closedset.insert(current);

            QList<Node> neighbors = neighborNodes(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                if (closedset.contains(neighbors[i])) {
                    continue;
                }

                int g = infos[current].gScore + distanceBetween(current, neighbors[i]);

                if (!openset.contains(neighbors[i])) {
                    infos[neighbors[i]] = NodeInfo(g,
                                                   heuristicCostEstimate(neighbors[i], goal),
                                                   current);

                    openset.insert(neighbors[i]);
                } else if (g < infos[neighbors[i]].gScore) {
                    NodeInfo &in = infos[neighbors[i]];
                    in.gScore = g;
                    in.fScore = g * in.hScore;
                    in.comeFrom = current;
                }
            }
        }
        return QList<Node>();
    }

    Node bestFromOpenSet(const QSet<Node> &openset, const QHash<Node, NodeInfo> &infos)
    {
        QSetIterator<Node> i(openset);
        Node current = i.next();
        Node bestNode = current;
        int bestFScore = infos[current].fScore;

        while (i.hasNext()) {
            current = i.next();
            int f = infos[current].fScore;

            if (f < bestFScore) {
                bestNode = current;
                bestFScore = f;
            }
        }
        return bestNode;
    }

    QList<Node> reconstructPath(const Node &current, const QHash<Node, NodeInfo> &infos)
    {
        Node comeFrom = infos[current].comeFrom;

        if (comeFrom != current) {
            QList<Node> head = reconstructPath(comeFrom, infos);
            head << current;
            return head;
        } else {
            return QList<Node>();
        }
    }

    virtual int heuristicCostEstimate(Node start, Node goal) = 0;
    virtual int distanceBetween(Node current, Node neighbor) = 0;
    virtual QList<Node> neighborNodes(Node current) = 0;
};

#endif // QASTAR_H
