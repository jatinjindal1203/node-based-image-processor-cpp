#include "BrightnessContrastNode.h"

BrightnessContrastNode::BrightnessContrastNode()
    : Node("Brightness/Contrast Node"), brightness(0), contrast(1.0)
{
}

BrightnessContrastNode::~BrightnessContrastNode() {}

void BrightnessContrastNode::setBrightness(int b)
{
    brightness = std::max(-100, std::min(100, b));
}

void BrightnessContrastNode::setContrast(double c)
{
    contrast = std::max(0.0, std::min(3.0, c));
}

void BrightnessContrastNode::resetParameters()
{
    brightness = 0;
    contrast = 1.0;
}

void BrightnessContrastNode::process()
{
    // For demonstration, assume inputImage has been set externally.
    if (inputImage.empty())
    {
        // Nothing to process
        return;
    }
    // Use convertScaleAbs to adjust brightness and contrast:
    // new_image = input * contrast + brightness
    inputImage.convertTo(outputImage, -1, contrast, brightness);
}

const cv::Mat &BrightnessContrastNode::getResult() const
{
    return outputImage;
}
