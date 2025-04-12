#ifndef BLURNODE_H
#define BLURNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

class BlurNode : public Node
{
public:
    BlurNode();
    virtual ~BlurNode();

    // Set the blur radius (kernel size; must be odd, between 1 and 21 ideally)
    void setKernelSize(int size);

    // Optionally, set if directional blur (for simplicity, we just use GaussianBlur for now)
    // void setDirectional(bool directional);

    // Process: Apply Gaussian blur using given kernel size.
    void process() override;

    const cv::Mat &getResult() const;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    int kernelSize;
};

#endif // BLURNODE_H
