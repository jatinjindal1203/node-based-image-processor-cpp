#include "EdgeDetectionNode.h"
#include <opencv2/imgproc.hpp>

EdgeDetectionNode::EdgeDetectionNode(int order)
    : Node("EdgeDetectionNode", order), m_lowThreshold(50), m_highThreshold(150) {}

EdgeDetectionNode::~EdgeDetectionNode() {}

void EdgeDetectionNode::setThresholds(double low, double high)
{
    m_lowThreshold = low;
    m_highThreshold = high;
}

cv::Mat EdgeDetectionNode::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    cv::Mat gray, edges;
    if (input.channels() == 3)
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    else
        gray = input;
    cv::Canny(gray, edges, m_lowThreshold, m_highThreshold);
    return edges;
}
