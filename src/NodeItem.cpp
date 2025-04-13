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
    // Set a default size (you can adjust as needed)
    m_rect = QRectF(0, 0, 120, 60);

    // Enable moving, selection, and hover events
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
    // Return the node's area with extra padding for pen width.
    return m_rect.adjusted(-2, -2, 2, 2);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // Draw the node rectangle.
    QPen pen(Qt::black);
    if (isSelected())
    {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(m_rect);

    // Draw the node's name centered.
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(m_rect, Qt::AlignCenter, m_nodeName);

    // Draw the resize handle in the bottom-right corner.
    QRectF handleRect(m_rect.bottomRight() - QPointF(m_handleSize, m_handleSize), QSizeF(m_handleSize, m_handleSize));
    painter->setBrush(Qt::darkGray);
    painter->drawRect(handleRect);

    // Optionally, draw the connection port region on the right side.
    // (For visualization; you may remove this once the behavior is confirmed.)
    qreal portX = m_rect.right() - m_portWidth;
    qreal portY = m_rect.center().y() - m_portHeight / 2;
    QRectF portRect(portX, portY, m_portWidth, m_portHeight);
    QPen portPen(Qt::blue);
    painter->setPen(portPen);
    painter->setBrush(Qt::transparent);
    painter->drawRect(portRect);
}

bool NodeItem::isInConnectionPort(const QPointF &pos) const
{
    // Define a rectangle at the middle of the right side as connection port.
    qreal portX = m_rect.right() - m_portWidth;
    qreal portY = m_rect.center().y() - m_portHeight / 2;
    QRectF portRect(portX, portY, m_portWidth, m_portHeight);
    return portRect.contains(pos);
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Check if the click occurs in the resize handle area first.
    // (We already had resizing logic; assume that's unchanged.)
    QRectF resizeRect(m_rect.bottomRight() - QPointF(m_handleSize * m_handlePaddingFactor, m_handleSize * m_handlePaddingFactor),
                      QSizeF(m_handleSize * m_handlePaddingFactor, m_handleSize * m_handlePaddingFactor));
    if (resizeRect.contains(event->pos()))
    {
        m_isResizing = true;
        m_resizeStartPos = event->pos();
        m_originalRect = m_rect;
        setCursor(Qt::SizeFDiagCursor);
        event->accept();
        return;
    }
    // Otherwise, let the event pass on normally (for movement, etc.).
    QGraphicsItem::mousePressEvent(event);
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
    QPointF pos = event->pos();
    // Set cursor based on hover: over resize area => resize cursor; over connection port => connection cursor; else default.
    QRectF resizeRect(m_rect.bottomRight() - QPointF(m_handleSize * m_handlePaddingFactor, m_handleSize * m_handlePaddingFactor),
                      QSizeF(m_handleSize * m_handlePaddingFactor, m_handleSize * m_handlePaddingFactor));
    if (resizeRect.contains(pos))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (isInConnectionPort(pos))
    {
        setCursor(Qt::CrossCursor); // Change to a distinct cursor to indicate "start connection"
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsItem::hoverMoveEvent(event);
}
