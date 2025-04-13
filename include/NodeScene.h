#ifndef NODESCENE_H
#define NODESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

// Forward declarations; NodeItem is your visual node class, and ConnectionItem will be used to represent connections.
class NodeItem;
class ConnectionItem;

class NodeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NodeScene(QObject *parent = nullptr);

protected:
    // Override mouse events to facilitate connection creation.
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ConnectionItem *m_tempConnection; // Temporary connection during the drag.
    NodeItem *m_connectionSource;     // The source node where the connection starts.
};

#endif // NODESCENE_H
