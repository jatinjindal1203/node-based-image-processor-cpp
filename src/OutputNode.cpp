#include "OutputNode.h"

OutputNode::OutputNode() : Node("OutputNode", 100) {} // High order so it comes at the end.

OutputNode::~OutputNode() {}

cv::Mat OutputNode::process(const cv::Mat &input)
{
    m_output = input.clone();
    return m_output;
}

cv::Mat OutputNode::output() const
{
    return m_output;
}
