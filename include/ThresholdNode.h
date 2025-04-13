#ifndef THRESHOLDNODE_H
#define THRESHOLDNODE_H

#include "Node.h"

class ThresholdNode : public Node
{
public:
    ThresholdNode(int order = 3);
    ~ThresholdNode() override;

    void setThreshold(double threshold); // 0.0 to 255.0
    cv::Mat process(const cv::Mat &input) override;

private:
    double m_threshold;
};

#endif // THRESHOLDNODE_H
