#ifndef BLENDNODE_H
#define BLENDNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

class BlendNode : public Node
{
public:
    BlendNode(int order = 5);
    ~BlendNode() override;

    void setSecondImage(const cv::Mat &img);
    void setOpacity(double opacity); // 0.0 to 1.0
    cv::Mat process(const cv::Mat &input) override;

private:
    cv::Mat m_secondImage;
    double m_opacity;
};

#endif // BLENDNODE_H
