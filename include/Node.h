#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(const QString &name) : name(name) {}
    virtual ~Node() {}

    QString getName() const { return name; }
    virtual void process() = 0;

protected:
    QString name;
};

#endif // NODE_H
