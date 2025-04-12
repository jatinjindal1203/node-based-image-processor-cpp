#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <vector>
#include <memory>
#include "Node.h"

// A simple manager for nodes that makes up the processing graph
class NodeGraph
{
public:
    NodeGraph();
    ~NodeGraph();

    // Adds a new node to the graph
    void addNode(std::shared_ptr<Node> node);

    // Processes all nodes in the graph sequentially.
    // Later, you can extend this to implement specific ordering or dependency checks.
    void processAll();

private:
    // A list to hold all nodes managed by this graph.
    std::vector<std::shared_ptr<Node>> nodes;
};

#endif // NODEGRAPH_H
