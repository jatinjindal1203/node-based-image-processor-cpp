#include "BlendNode.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>

BlendNode::BlendNode(int order)
    : Node("BlendNode", order), m_opacity(0.5) {}

BlendNode::~BlendNode() {}

void BlendNode::setSecondImage(const cv::Mat &img)
{
    m_secondImage = img;
}

void BlendNode::setOpacity(double opacity)
{
    m_opacity = std::max(0.0, std::min(1.0, opacity));
}

cv::Mat BlendNode::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    cv::Mat img2;
    // If no valid second image, use input.
    if (m_secondImage.empty() ||
        m_secondImage.size() != input.size() || m_secondImage.type() != input.type())
        img2 = input.clone();
    else
        img2 = m_secondImage;

    cv::Mat output;
    cv::addWeighted(input, 1.0 - m_opacity, img2, m_opacity, 0, output);
    return output;
}
