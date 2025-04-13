#include "ThresholdNode.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>

ThresholdNode::ThresholdNode(int order)
    : Node("ThresholdNode", order), m_threshold(128.0) {}

ThresholdNode::~ThresholdNode() {}

void ThresholdNode::setThreshold(double threshold)
{
    m_threshold = std::max(0.0, std::min(255.0, threshold));
}

cv::Mat ThresholdNode::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    cv::Mat gray, output;
    if (input.channels() == 3)
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    else
        gray = input;
    cv::threshold(gray, output, m_threshold, 255, cv::THRESH_BINARY);
    return output;
}
