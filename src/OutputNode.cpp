#include "OutputNode.h"
#include <opencv2/imgcodecs.hpp>

OutputNode::OutputNode() : Node("Output Node") {}
OutputNode::~OutputNode() {}

void OutputNode::setInput(const cv::Mat &inputImage)
{
    processedImage = inputImage.clone();
}

void OutputNode::saveImage(const QString &filePath)
{
    if (!processedImage.empty())
    {
        cv::imwrite(filePath.toStdString(), processedImage);
    }
}

void OutputNode::process()
{
    // Currently, it's a simple pass-through.
}
