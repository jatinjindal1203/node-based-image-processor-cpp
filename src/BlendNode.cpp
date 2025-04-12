#include "BlendNode.h"
#include <algorithm>

BlendNode::BlendNode()
    : Node("Blend Node"), blendMode(BlendMode::Normal), opacity(0.5) {}
BlendNode::~BlendNode() {}

void BlendNode::setInputImages(const cv::Mat &img1, const cv::Mat &img2)
{
    image1 = img1;
    image2 = img2;
}

void BlendNode::setBlendMode(BlendMode mode)
{
    blendMode = mode;
}

void BlendNode::setOpacity(double op)
{
    opacity = std::max(0.0, std::min(1.0, op));
}

void BlendNode::process()
{
    if (image1.empty() || image2.empty())
        return;
    // Ensure both images are the same size and type, otherwise resize:
    if (image1.size() != image2.size() || image1.type() != image2.type())
    {
        cv::resize(image2, image2, image1.size());
    }

    // For demonstration, implement normal blend using weighted addition.
    // In a real scenario, you'd implement different blend modes.
    if (blendMode == BlendMode::Normal)
    {
        cv::addWeighted(image1, opacity, image2, 1 - opacity, 0, blendedImage);
    }
    else
    {
        // For other modes, simply falling back to normal blend for now.
        cv::addWeighted(image1, opacity, image2, 1 - opacity, 0, blendedImage);
    }
}

const cv::Mat &BlendNode::getResult() const
{
    return blendedImage;
}
