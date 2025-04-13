#include "ImageInputNode.h"

ImageInputNode::ImageInputNode() : Node("ImageInputNode", 0) {}

ImageInputNode::~ImageInputNode() {}

void ImageInputNode::setImage(const cv::Mat &img)
{
    m_image = img;
}

cv::Mat ImageInputNode::getImage() const
{
    return m_image;
}

cv::Mat ImageInputNode::process(const cv::Mat &input)
{
    Q_UNUSED(input);
    return m_image;
}
