#ifndef CONVOLUTIONFILTERNODE_H
#define CONVOLUTIONFILTERNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include <string>

class ConvolutionFilterNode : public Node
{
public:
    ConvolutionFilterNode(int order = 7);
    ~ConvolutionFilterNode() override;

    // Set a custom kernel (3x3 or 5x5).
    void setKernel(const cv::Mat &kernel);
    // Or set a preset by name.
    void setPreset(const std::string &preset);

    cv::Mat process(const cv::Mat &input) override;

private:
    cv::Mat m_kernel;
    void loadPreset(const std::string &preset);
};

#endif // CONVOLUTIONFILTERNODE_H
