#include "ColorChannelSplitter.h"
#include <opencv2/imgproc.hpp>
#include <vector>

ColorChannelSplitter::ColorChannelSplitter(int order)
    : Node("ColorChannelSplitter", order), m_grayscaleOutput(true) {}

ColorChannelSplitter::~ColorChannelSplitter() {}

void ColorChannelSplitter::setGrayscaleOutput(bool grayscale)
{
    m_grayscaleOutput = grayscale;
}

cv::Mat ColorChannelSplitter::process(const cv::Mat &input)
{
    if (input.empty())
        return input;
    std::vector<cv::Mat> channels;
    cv::split(input, channels);
    // Convert each channel to grayscale if needed (each channel is single channel already).
    // For visualization, we horizontally concatenate channels.
    cv::Mat output;
    cv::hconcat(channels, output);
    return output;
}
