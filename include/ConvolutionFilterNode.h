#ifndef CONVOLUTIONFILTERNODE_H
#define CONVOLUTIONFILTERNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>
#include <vector>

class ConvolutionFilterNode : public Node
{
public:
    ConvolutionFilterNode();
    virtual ~ConvolutionFilterNode();

    // Set custom kernel. The kernel should be 3x3 or 5x5.
    void setKernel(const cv::Mat &kernel);

    // Alternatively, set a preset filter by name (sharpen, emboss, edge enhance, etc.)
    void setPreset(const std::string &preset);

    // Process: Apply the convolution filter to the image.
    void process() override;

    const cv::Mat &getResult() const;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    cv::Mat kernel;

    // Helper: load a preset kernel.
    void loadPreset(const std::string &preset);
};

#endif // CONVOLUTIONFILTERNODE_H
