#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include "Node.h"
#include <vector>
#include <memory>
#include <algorithm>

class NodeGraph
{
public:
    NodeGraph() {}
    ~NodeGraph() {}

    // Add a processing node
    void addNode(std::shared_ptr<Node> node)
    {
        nodes.push_back(node);
    }

    // Execute the pipeline: sort nodes by order, then pass the image through each.
    cv::Mat processAll(const cv::Mat &input)
    {
        std::vector<std::shared_ptr<Node>> sortedNodes = nodes;
        std::sort(sortedNodes.begin(), sortedNodes.end(), [](const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b)
                  { return a->order() < b->order(); });
        cv::Mat current = input;
        for (auto &node : sortedNodes)
            current = node->process(current);
        return current;
    }

private:
    std::vector<std::shared_ptr<Node>> nodes;
};

#endif // NODEGRAPH_H
