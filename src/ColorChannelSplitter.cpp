#include "ColorChannelSplitter.h"

ColorChannelSplitter::ColorChannelSplitter()
    : Node("Color Channel Splitter"), outputGrayscale(false)
{
}

ColorChannelSplitter::~ColorChannelSplitter() {}

void ColorChannelSplitter::setOutputGrayscale(bool grayscale)
{
    outputGrayscale = grayscale;
}

void ColorChannelSplitter::process()
{
    channels.clear();
    if (inputImage.empty())
    {
        return;
    }

    // Split image into channels
    cv::split(inputImage, channels);

    if (outputGrayscale)
    {
        // For each channel, convert it to grayscale image (this is often already single channel)
        for (auto &ch : channels)
        {
            // Optionally, normalize or adjust display here.
        }
    }
}

const std::vector<cv::Mat> &ColorChannelSplitter::getChannels() const
{
    return channels;
}
