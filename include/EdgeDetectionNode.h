#ifndef EDGEDETECTIONNODE_H
#define EDGEDETECTIONNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

enum class EdgeMethod
{
    Sobel,
    Canny
};

class EdgeDetectionNode : public Node
{
public:
    EdgeDetectionNode();
    virtual ~EdgeDetectionNode();

    // Set method and parameters
    void setMethod(EdgeMethod m);
    void setThresholds(double thresh1, double thresh2);
    void setKernelSize(int size);

    // Process: Detect edges using the chosen method.
    void process() override;

    const cv::Mat &getResult() const;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    EdgeMethod method;
    double threshold1, threshold2;
    int kernelSize; // for Sobel, a typical value might be 3
};

#endif // EDGEDETECTIONNODE_H
