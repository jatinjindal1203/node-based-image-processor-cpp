#include "NodeItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <algorithm>
#include <QDebug>

NodeItem::NodeItem(const QString &nodeName, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_nodeName(nodeName), m_isResizing(false)
{
    // Set the default rectangle size.
    m_rect = QRectF(0, 0, 120, 60);

    // Enable moving, selection, and hover events.
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);
}

void NodeItem::setNodeName(const QString &name)
{
    m_nodeName = name;
    update();
}

QString NodeItem::nodeName() const
{
    return m_nodeName;
}

QRectF NodeItem::boundingRect() const
{
    // Provide a little extra space.
    return m_rect.adjusted(-2, -2, 2, 2);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen(Qt::black);
    if (isSelected())
    {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(m_rect);

    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(m_rect, Qt::AlignCenter, m_nodeName);

    // Draw the resize handle using an enlarged clickable area.
    // We actually draw a handle of size m_handleSize.
    QRectF handleRect(m_rect.bottomRight() - QPointF(m_handleSize, m_handleSize), QSizeF(m_handleSize, m_handleSize));
    painter->setBrush(Qt::darkGray);
    painter->drawRect(handleRect);
}

bool NodeItem::isInResizeArea(const QPointF &pos) const
{
    // Define a larger clickable area for the resize handle.
    qreal areaSize = m_handleSize * m_handlePaddingFactor;
    QRectF resizeArea(m_rect.bottomRight() - QPointF(areaSize, areaSize), QSizeF(areaSize, areaSize));
    // For debugging:
    // qDebug() << "Resize area:" << resizeArea << "Pos:" << pos;
    return resizeArea.contains(pos);
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isInResizeArea(event->pos()))
    {
        m_isResizing = true;
        m_resizeStartPos = event->pos();
        m_originalRect = m_rect;
        setCursor(Qt::SizeFDiagCursor);
        event->accept();
    }
    else
    {
        QGraphicsItem::mousePressEvent(event);
    }
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isResizing)
    {
        QPointF delta = event->pos() - m_resizeStartPos;
        qreal newWidth = std::max(30.0, m_originalRect.width() + delta.x());
        qreal newHeight = std::max(20.0, m_originalRect.height() + delta.y());
        m_rect.setWidth(newWidth);
        m_rect.setHeight(newHeight);
        update();
        event->accept();
    }
    else
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isResizing)
    {
        m_isResizing = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    }
    else
    {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

void NodeItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (isInResizeArea(event->pos()))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsItem::hoverMoveEvent(event);
}
