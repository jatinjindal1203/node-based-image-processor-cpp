#include "EdgeDetectionNode.h"

EdgeDetectionNode::EdgeDetectionNode()
    : Node("Edge Detection Node"), method(EdgeMethod::Canny),
      threshold1(50), threshold2(150), kernelSize(3) {}
EdgeDetectionNode::~EdgeDetectionNode() {}

void EdgeDetectionNode::setMethod(EdgeMethod m)
{
    method = m;
}

void EdgeDetectionNode::setThresholds(double t1, double t2)
{
    threshold1 = t1;
    threshold2 = t2;
}

void EdgeDetectionNode::setKernelSize(int size)
{
    kernelSize = (size % 2 == 0) ? size + 1 : size;
}

void EdgeDetectionNode::process()
{
    if (inputImage.empty())
        return;

    cv::Mat gray;
    if (inputImage.channels() == 3)
        cv::cvtColor(inputImage, gray, cv::COLOR_BGR2GRAY);
    else
        gray = inputImage;

    if (method == EdgeMethod::Canny)
    {
        cv::Canny(gray, outputImage, threshold1, threshold2);
    }
    else if (method == EdgeMethod::Sobel)
    {
        cv::Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
        cv::Sobel(gray, grad_x, CV_16S, 1, 0, kernelSize);
        cv::Sobel(gray, grad_y, CV_16S, 0, 1, kernelSize);
        cv::convertScaleAbs(grad_x, abs_grad_x);
        cv::convertScaleAbs(grad_y, abs_grad_y);
        cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, outputImage);
    }
}

const cv::Mat &EdgeDetectionNode::getResult() const
{
    return outputImage;
}
