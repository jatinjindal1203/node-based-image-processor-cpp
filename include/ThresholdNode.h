#ifndef THRESHOLDNODE_H
#define THRESHOLDNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

enum class ThresholdMethod
{
    Binary,
    Adaptive,
    Otsu
};

class ThresholdNode : public Node
{
public:
    ThresholdNode();
    virtual ~ThresholdNode();

    // Set parameters for thresholding.
    void setThresholdValue(double value);
    void setMethod(ThresholdMethod method);

    // Process: Apply thresholding to the image.
    void process() override;

    const cv::Mat &getResult() const;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    double thresholdValue;
    ThresholdMethod method;
};

#endif // THRESHOLDNODE_H
