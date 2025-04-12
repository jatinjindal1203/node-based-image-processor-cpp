#include "BlurNode.h"
#include <algorithm>

BlurNode::BlurNode() : Node("Blur Node"), kernelSize(3) {} // default kernel size is 3 (must be odd)
BlurNode::~BlurNode() {}

void BlurNode::setKernelSize(int size)
{
    // Enforce odd value between 1 and 21
    if (size < 1)
        size = 1;
    if (size > 21)
        size = 21;
    if (size % 2 == 0)
        size += 1;
    kernelSize = size;
}

void BlurNode::process()
{
    if (inputImage.empty())
        return;
    // Apply Gaussian blur with kernel size (radius 1-21 pixels)
    cv::GaussianBlur(inputImage, outputImage, cv::Size(kernelSize, kernelSize), 0);
}

const cv::Mat &BlurNode::getResult() const
{
    return outputImage;
}
