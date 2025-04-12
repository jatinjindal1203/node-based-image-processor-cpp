#ifndef BLENDNODE_H
#define BLENDNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

enum class BlendMode
{
    Normal,
    Multiply,
    Screen,
    Overlay,
    Difference
};

class BlendNode : public Node
{
public:
    BlendNode();
    virtual ~BlendNode();

    // Set second image for blending. For simplicity, we assume two images are provided.
    void setInputImages(const cv::Mat &img1, const cv::Mat &img2);
    // Set blend mode and opacity (0.0 to 1.0)
    void setBlendMode(BlendMode mode);
    void setOpacity(double opacity);

    // Process: Blend the two images using the selected mode.
    void process() override;

    const cv::Mat &getResult() const;

private:
    cv::Mat image1, image2;
    cv::Mat blendedImage;
    BlendMode blendMode;
    double opacity; // opacity/mix factor for image blending
};

#endif // BLENDNODE_H
