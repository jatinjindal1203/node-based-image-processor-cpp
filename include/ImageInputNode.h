#ifndef IMAGEINPUTNODE_H
#define IMAGEINPUTNODE_H

#include "Node.h"

// The input node simply stores an image (loaded externally) and returns it.
class ImageInputNode : public Node
{
public:
    ImageInputNode();
    ~ImageInputNode() override;

    void setImage(const cv::Mat &img);
    cv::Mat getImage() const;

    // process() here ignores its argument and returns the stored image.
    cv::Mat process(const cv::Mat &input) override;

private:
    cv::Mat m_image;
};

#endif // IMAGEINPUTNODE_H
