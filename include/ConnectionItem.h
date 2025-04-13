#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QGraphicsLineItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

// Forward declaration of NodeItem (assuming it represents a visual node)
class NodeItem;

class ConnectionItem : public QGraphicsLineItem
{
public:
    ConnectionItem(NodeItem *source, NodeItem *dest, QGraphicsItem *parent = nullptr);

    // Update the connection line according to current positions of source and destination nodes.
    void updatePosition();

    // Accessor functions
    NodeItem *sourceNode() const { return m_source; }
    NodeItem *destNode() const { return m_dest; }

protected:
    // Override paint to draw the connection line and the arrowhead.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    NodeItem *m_source;
    NodeItem *m_dest;
};

#endif // CONNECTIONITEM_H
