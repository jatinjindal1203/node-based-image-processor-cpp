#ifndef COLORCHANNELSPLITTER_H
#define COLORCHANNELSPLITTER_H

#include "Node.h"

class ColorChannelSplitter : public Node
{
public:
    ColorChannelSplitter(int order = 2);
    ~ColorChannelSplitter() override;

    // Optionally, add a flag to output grayscale channels.
    void setGrayscaleOutput(bool grayscale);

    cv::Mat process(const cv::Mat &input) override;

private:
    bool m_grayscaleOutput; // If true, output each channel as grayscale
};

#endif // COLORCHANNELSPLITTER_H
