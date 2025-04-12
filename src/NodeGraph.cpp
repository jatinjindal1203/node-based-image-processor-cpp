#include "NodeGraph.h"

NodeGraph::NodeGraph()
{
    // You could initialize additional state here if needed.
}

NodeGraph::~NodeGraph()
{
    // Resources will be cleaned automatically since we're using smart pointers.
}

void NodeGraph::addNode(std::shared_ptr<Node> node)
{
    nodes.push_back(node);
}

void NodeGraph::processAll()
{
    // For now, simply process each node in the order they were added.
    for (auto &node : nodes)
    {
        node->process();
    }
}
