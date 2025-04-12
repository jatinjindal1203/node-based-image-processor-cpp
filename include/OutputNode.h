#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

class OutputNode : public Node
{
public:
    OutputNode();
    ~OutputNode();

    void setInput(const cv::Mat &inputImage);
    void saveImage(const QString &filePath);
    void process() override;

private:
    cv::Mat processedImage;
};

#endif // OUTPUTNODE_H
