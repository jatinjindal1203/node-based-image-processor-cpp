#include "ThresholdNode.h"

ThresholdNode::ThresholdNode()
    : Node("Threshold Node"), thresholdValue(128.0), method(ThresholdMethod::Binary) {}
ThresholdNode::~ThresholdNode() {}

void ThresholdNode::setThresholdValue(double value)
{
    thresholdValue = value;
}

void ThresholdNode::setMethod(ThresholdMethod m)
{
    method = m;
}

void ThresholdNode::process()
{
    if (inputImage.empty())
        return;

    // Convert input to grayscale if it's not already (for thresholding)
    cv::Mat gray;
    if (inputImage.channels() == 3)
        cv::cvtColor(inputImage, gray, cv::COLOR_BGR2GRAY);
    else
        gray = inputImage;

    // Apply thresholding based on method.
    switch (method)
    {
    case ThresholdMethod::Binary:
        cv::threshold(gray, outputImage, thresholdValue, 255, cv::THRESH_BINARY);
        break;
    case ThresholdMethod::Adaptive:
        cv::adaptiveThreshold(gray, outputImage, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
        break;
    case ThresholdMethod::Otsu:
        cv::threshold(gray, outputImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        break;
    default:
        cv::threshold(gray, outputImage, thresholdValue, 255, cv::THRESH_BINARY);
        break;
    }
}

const cv::Mat &ThresholdNode::getResult() const
{
    return outputImage;
}
