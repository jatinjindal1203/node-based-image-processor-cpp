#ifndef BRIGHTNESSCONTRASTNODE_H
#define BRIGHTNESSCONTRASTNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

class BrightnessContrastNode : public Node
{
public:
    BrightnessContrastNode();
    virtual ~BrightnessContrastNode();

    // Set parameters in the range specified:
    // brightness: -100 to +100, contrast: 0.0 to 3.0
    void setBrightness(int brightness);
    void setContrast(double contrast);

    // Reset to default parameters
    void resetParameters();

    // Process: Adjust brightness and contrast using OpenCV conversion.
    void process() override;

    // Get the processed image result.
    const cv::Mat &getResult() const;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    int brightness;  // default 0
    double contrast; // default 1.0
};

#endif // BRIGHTNESSCONTRASTNODE_H
