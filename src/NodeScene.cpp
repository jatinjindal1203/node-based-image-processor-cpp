#include "NodeScene.h"
#include "ConnectionItem.h"
#include "NodeItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include <QDebug>

NodeScene::NodeScene(QObject *parent)
    : QGraphicsScene(parent), m_tempConnection(nullptr), m_connectionSource(nullptr)
{
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    NodeItem *node = dynamic_cast<NodeItem *>(item);
    if (node)
    {
        // Map scene position to node's local coordinates.
        QPointF localPos = node->mapFromScene(event->scenePos());
        if (node->isInConnectionPort(localPos))
        {
            // Begin connection creation if the click is in the connection port.
            m_connectionSource = node;
            m_tempConnection = new ConnectionItem(node, nullptr);
            QPointF start = node->pos() + node->boundingRect().center();
            m_tempConnection->setLine(QLineF(start, start));
            addItem(m_tempConnection);
            event->accept();
            return;
        }
    }
    // Otherwise, default processing (moving/resizing, etc.)
    QGraphicsScene::mousePressEvent(event);
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_tempConnection && m_connectionSource)
    {
        QPointF start = m_connectionSource->pos() + m_connectionSource->boundingRect().center();
        QLineF newLine(start, event->scenePos());
        m_tempConnection->setLine(newLine);
        event->accept();
        return;
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_tempConnection && m_connectionSource)
    {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        NodeItem *destNode = dynamic_cast<NodeItem *>(item);
        if (destNode && destNode != m_connectionSource)
        {
            removeItem(m_tempConnection);
            delete m_tempConnection;
            m_tempConnection = nullptr;
            ConnectionItem *connection = new ConnectionItem(m_connectionSource, destNode);
            addItem(connection);
        }
        else
        {
            removeItem(m_tempConnection);
            delete m_tempConnection;
            m_tempConnection = nullptr;
        }
        m_connectionSource = nullptr;
        event->accept();
        return;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
