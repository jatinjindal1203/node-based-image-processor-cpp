#include "ConvolutionFilterNode.h"
#include <opencv2/imgproc.hpp>

ConvolutionFilterNode::ConvolutionFilterNode(int order)
    : Node("ConvolutionFilterNode", order)
{
    // Default identity kernel 3x3.
    m_kernel = cv::Mat::eye(3, 3, CV_32F);
}

ConvolutionFilterNode::~ConvolutionFilterNode() {}

void ConvolutionFilterNode::setKernel(const cv::Mat &kernel)
{
    if ((kernel.rows == 3 && kernel.cols == 3) || (kernel.rows == 5 && kernel.cols == 5))
        m_kernel = kernel.clone();
    else
        throw std::invalid_argument("Kernel must be 3x3 or 5x5.");
}

void ConvolutionFilterNode::setPreset(const std::string &preset)
{
    loadPreset(preset);
}

void ConvolutionFilterNode::loadPreset(const std::string &preset)
{
    if (preset == "sharpen")
    {
        float data[9] = {0, -1, 0,
                         -1, 5, -1,
                         0, -1, 0};
        m_kernel = cv::Mat(3, 3, CV_32F, data).clone();
    }
    else if (preset == "emboss")
    {
        float data[9] = {-2, -1, 0,
                         -1, 1, 1,
                         0, 1, 2};
        m_kernel = cv::Mat(3, 3, CV_32F, data).clone();
    }
    else if (preset == "edge_enhance")
    {
        float data[9] = {0, 0, 0,
                         -1, 1, -1,
                         0, 0, 0};
        m_kernel = cv::Mat(3, 3, CV_32F, data).clone();
    }
    else
    {
        m_kernel = cv::Mat::eye(3, 3, CV_32F);
    }
}

cv::Mat ConvolutionFilterNode::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    cv::Mat output;
    cv::filter2D(input, output, -1, m_kernel);
    return output;
}
