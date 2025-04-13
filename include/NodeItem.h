#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>
#include <QString>
#include <QRectF>
#include <QPointF>

class NodeItem : public QGraphicsItem
{
public:
    // Constructor takes a node name.
    explicit NodeItem(const QString &nodeName, QGraphicsItem *parent = nullptr);

    // Set or get the node name.
    void setNodeName(const QString &name);
    QString nodeName() const;

    // Overridden methods from QGraphicsItem.
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    // Override mouse events to support dragging and resizing.
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QString m_nodeName;                      // The displayed name of the node.
    QRectF m_rect;                           // The rectangle representing the node's boundaries.
    bool m_isResizing;                       // Indicates if the node is currently resizing.
    QPointF m_resizeStartPos;                // Initial mouse position when resizing starts.
    QRectF m_originalRect;                   // The node's rectangle at the start of resizing.
    const qreal m_handleSize = 10.0;         // Base size of the resize handle.
    const qreal m_handlePaddingFactor = 2.0; // Factor to enlarge the clickable region.

    // Returns true if the given position (local coordinates) falls within the resize handle area.
    bool isInResizeArea(const QPointF &pos) const;
};

#endif // NODEITEM_H
