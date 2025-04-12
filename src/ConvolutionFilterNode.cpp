#include "ConvolutionFilterNode.h"
#include <opencv2/imgproc.hpp>
#include <stdexcept>
#include <string>

ConvolutionFilterNode::ConvolutionFilterNode() : Node("Convolution Filter Node")
{
    // Default kernel: identity filter (no change)
    kernel = cv::Mat::eye(3, 3, CV_32F);
}

ConvolutionFilterNode::~ConvolutionFilterNode() {}

void ConvolutionFilterNode::setKernel(const cv::Mat &k)
{
    // Verify kernel size is 3x3 or 5x5
    if ((k.rows == 3 && k.cols == 3) || (k.rows == 5 && k.cols == 5))
    {
        kernel = k.clone();
    }
    else
    {
        throw std::invalid_argument("Kernel must be 3x3 or 5x5.");
    }
}

void ConvolutionFilterNode::setPreset(const std::string &preset)
{
    loadPreset(preset);
}

void ConvolutionFilterNode::loadPreset(const std::string &preset)
{
    if (preset == "sharpen")
    {
        float data[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
        kernel = cv::Mat(3, 3, CV_32F, data).clone();
    }
    else if (preset == "emboss")
    {
        float data[9] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
        kernel = cv::Mat(3, 3, CV_32F, data).clone();
    }
    else if (preset == "edge_enhance")
    {
        float data[9] = {0, 0, 0, -1, 1, -1, 0, 0, 0};
        kernel = cv::Mat(3, 3, CV_32F, data).clone();
    }
    else
    {
        // Default identity filter if no valid preset
        kernel = cv::Mat::eye(3, 3, CV_32F);
    }
}

void ConvolutionFilterNode::process()
{
    if (inputImage.empty())
        return;
    cv::filter2D(inputImage, outputImage, -1, kernel);
}

const cv::Mat &ConvolutionFilterNode::getResult() const
{
    return outputImage;
}
