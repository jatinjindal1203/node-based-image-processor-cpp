#include "BrightnessContrastNode.h"
#include <algorithm>

BrightnessContrastNode::BrightnessContrastNode(int order)
    : Node("BrightnessContrastNode", order), m_brightness(0), m_contrast(1.0) {}

BrightnessContrastNode::~BrightnessContrastNode() {}

void BrightnessContrastNode::setBrightness(int brightness)
{
    m_brightness = std::max(-100, std::min(100, brightness));
}

void BrightnessContrastNode::setContrast(double contrast)
{
    m_contrast = std::max(0.0, std::min(3.0, contrast));
}

cv::Mat BrightnessContrastNode::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    cv::Mat output;
    input.convertTo(output, -1, m_contrast, m_brightness);
    return output;
}
