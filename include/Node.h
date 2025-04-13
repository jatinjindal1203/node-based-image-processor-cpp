#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    explicit Node(const QString &name) : m_name(name) {}
    virtual ~Node() {}
    QString name() const { return m_name; }
    virtual void process() = 0; // Pure virtual: must be overridden in derived classes.
private:
    QString m_name;
};

#endif // NODE_H
