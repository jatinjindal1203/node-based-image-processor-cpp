#ifndef EDGEDETECTIONNODE_H
#define EDGEDETECTIONNODE_H

#include "Node.h"

class EdgeDetectionNode : public Node
{
public:
    EdgeDetectionNode(int order = 4);
    ~EdgeDetectionNode() override;

    void setThresholds(double low, double high);
    cv::Mat process(const cv::Mat &input) override;

private:
    double m_lowThreshold;
    double m_highThreshold;
};

#endif // EDGEDETECTIONNODE_H
