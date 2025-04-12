#include "ImageInputNode.h"
#include <opencv2/imgcodecs.hpp>

ImageInputNode::ImageInputNode() : Node("Image Input Node") {}
ImageInputNode::~ImageInputNode() {}

void ImageInputNode::loadImage(const QString &filePath)
{
    image = cv::imread(filePath.toStdString(), cv::IMREAD_COLOR);
}

const cv::Mat &ImageInputNode::getImage() const
{
    return image;
}

void ImageInputNode::process()
{
    if (image.empty())
    {
        // Add error handling if needed.
    }
}
