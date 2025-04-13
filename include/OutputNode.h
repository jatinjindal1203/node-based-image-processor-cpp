#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include "Node.h"

// The output node stores the final processed image.
class OutputNode : public Node
{
public:
    OutputNode();
    ~OutputNode() override;

    // Process simply stores the image and returns it.
    cv::Mat process(const cv::Mat &input) override;

    cv::Mat output() const;

private:
    cv::Mat m_output;
};

#endif // OUTPUTNODE_H
