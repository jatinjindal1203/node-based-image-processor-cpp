#include "NoiseGenerationNode.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdlib>
#include <ctime>

NoiseGenerationNode::NoiseGenerationNode(int order)
    : Node("NoiseGenerationNode", order),
      m_width(640), m_height(480), m_seed(static_cast<unsigned int>(time(nullptr))) {}

NoiseGenerationNode::~NoiseGenerationNode() {}

void NoiseGenerationNode::setSize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void NoiseGenerationNode::setSeed(unsigned int seed)
{
    m_seed = seed;
}

cv::Mat NoiseGenerationNode::process(const cv::Mat &input)
{
    Q_UNUSED(input);
    cv::Mat noise(m_height, m_width, CV_8UC1);
    cv::randu(noise, 0, 255);
    return noise;
}
