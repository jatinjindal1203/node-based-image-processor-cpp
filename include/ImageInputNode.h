#ifndef IMAGEINPUTNODE_H
#define IMAGEINPUTNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

class ImageInputNode : public Node
{
public:
    ImageInputNode();
    ~ImageInputNode();

    void loadImage(const QString &filePath);
    const cv::Mat &getImage() const;
    void process() override;

private:
    cv::Mat image;
};

#endif // IMAGEINPUTNODE_H
