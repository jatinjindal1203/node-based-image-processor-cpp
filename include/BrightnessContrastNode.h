#ifndef BRIGHTNESSCONTRASTNODE_H
#define BRIGHTNESSCONTRASTNODE_H

#include "Node.h"

class BrightnessContrastNode : public Node
{
public:
    // Default order for a processing node is 1; you can change it later.
    BrightnessContrastNode(int order = 1);
    ~BrightnessContrastNode() override;

    void setBrightness(int brightness); // -100 to +100
    void setContrast(double contrast);  // 0.0 to 3.0

    cv::Mat process(const cv::Mat &input) override;

private:
    int m_brightness;
    double m_contrast;
};

#endif // BRIGHTNESSCONTRASTNODE_H
