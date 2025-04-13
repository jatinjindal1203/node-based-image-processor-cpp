#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>
#include <QString>
#include <QRectF>
#include <QPointF>

class NodeItem : public QGraphicsItem
{
public:
    explicit NodeItem(const QString &nodeName, QGraphicsItem *parent = nullptr);

    void setNodeName(const QString &name);
    QString nodeName() const;

    // Overridden functions from QGraphicsItem:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // New: Check if a given local position is within the connection port area.
    bool isInConnectionPort(const QPointF &pos) const;

protected:
    // Mouse event overrides for moving and resizing:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QString m_nodeName;
    QRectF m_rect;
    bool m_isResizing;
    QPointF m_resizeStartPos;
    QRectF m_originalRect;
    const qreal m_handleSize = 10.0;
    const qreal m_handlePaddingFactor = 2.0;

    // New: Define the connection port dimensions (located on the right edge)
    const qreal m_portWidth = 15.0;
    const qreal m_portHeight = 20.0;
};

#endif // NODEITEM_H
