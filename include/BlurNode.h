#ifndef BLURNODE_H
#define BLURNODE_H

#include "Node.h"

class BlurNode : public Node
{
public:
    BlurNode(int order = 2);
    ~BlurNode() override;

    void setKernelSize(int size); // Must be odd, e.g. 3, 5, etc.
    cv::Mat process(const cv::Mat &input) override;

private:
    int m_kernelSize;
};

#endif // BLURNODE_H
