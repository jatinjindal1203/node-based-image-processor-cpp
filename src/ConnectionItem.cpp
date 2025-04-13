#include "ConnectionItem.h"
#include "NodeItem.h"
#include <QtMath>

ConnectionItem::ConnectionItem(NodeItem *source, NodeItem *dest, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), m_source(source), m_dest(dest)
{
    setPen(QPen(Qt::black, 2));
    setZValue(-1); // Draw behind nodes.
    updatePosition();
}

void ConnectionItem::updatePosition()
{
    if (m_source && m_dest)
    {
        // Use the center of the nodes as the connection points.
        QPointF start = m_source->pos() + m_source->boundingRect().center();
        QPointF end = m_dest->pos() + m_dest->boundingRect().center();
        setLine(QLineF(start, end));
    }
}

void ConnectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // Draw the connection line first.
    painter->setPen(pen());
    painter->drawLine(line());

    // Choose arrow size
    const double arrowSize = 10.0;
    QLineF ln = line();

    // Find the midpoint
    QPointF midpoint = ln.pointAt(0.5);

    // Compute the angle from source to destination
    double angle = std::atan2(ln.dy(), ln.dx());

    double forwardOffset = 0.0;
    QPointF arrowTip = midpoint + QPointF(std::cos(angle) * forwardOffset, std::sin(angle) * forwardOffset);

    // Now define the two corners of the arrow triangle, relative to arrowTip.
    // We rotate ±60° around arrowTip to get the corners.
    QPointF corner1 = arrowTip - QPointF(std::sin(angle + M_PI / 3) * arrowSize, -std::cos(angle + M_PI / 3) * arrowSize);
    QPointF corner2 = arrowTip + QPointF(std::sin(angle - M_PI / 3) * arrowSize, -std::cos(angle - M_PI / 3) * arrowSize);

    // Construct the arrowhead polygon (tip -> corner1 -> corner2).
    QPolygonF arrowHead;
    arrowHead << arrowTip << corner1 << corner2;

    painter->setBrush(Qt::black);
    painter->drawPolygon(arrowHead);
}
