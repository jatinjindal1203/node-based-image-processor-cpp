#include "BlurNode.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>

BlurNode::BlurNode(int order) : Node("BlurNode", order), m_kernelSize(3) {}

BlurNode::~BlurNode() {}

void BlurNode::setKernelSize(int size)
{
    if (size % 2 == 0)
        size++; // force odd
    m_kernelSize = std::max(1, std::min(size, 21));
}

cv::Mat BlurNode::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    cv::Mat output;
    cv::GaussianBlur(input, output, cv::Size(m_kernelSize, m_kernelSize), 0);
    return output;
}
