#include "qastar.h"
#include <QDebug>
#include <QPoint>

class MyAStar : public QAStar<QPoint>
{
public:
    int heuristicCostEstimate(QPoint start, QPoint goal)
    {
        return (start - goal).manhattanLength();
    }

    int distanceBetween(QPoint, QPoint)
    {
        return 1;
    }

    QList<QPoint> neighborNodes(QPoint current)
    {
        QList<QPoint> list;
        list << current + QPoint(1, 0);
        list << current + QPoint(0, 1);
        list << current + QPoint(-1, 0);
        list << current + QPoint(0, -1);
        return list;
    }
};

uint qHash(const QPoint &p)
{
    return ((p.x() & 0x0000FFFF) << 16) | (p.y() & 0x0000FFFF);
}

int main()
{
    MyAStar ass;
    qDebug() << ass.findPath(QPoint(0, 0), QPoint(10, 10));
    return 0;
}
