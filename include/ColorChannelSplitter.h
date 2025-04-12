#ifndef COLORCHANNELSPLITTER_H
#define COLORCHANNELSPLITTER_H

#include "Node.h"
#include <opencv2/opencv.hpp>
#include <vector>

class ColorChannelSplitter : public Node
{
public:
    ColorChannelSplitter();
    virtual ~ColorChannelSplitter();

    // Optionally, if you want to output grayscale versions of each channel, set this flag.
    void setOutputGrayscale(bool grayscale);

    // Process: split the image into its color channels.
    void process() override;

    // Get the individual channel images.
    const std::vector<cv::Mat> &getChannels() const;

private:
    cv::Mat inputImage;
    std::vector<cv::Mat> channels;
    bool outputGrayscale; // false by default
};

#endif // COLORCHANNELSPLITTER_H
