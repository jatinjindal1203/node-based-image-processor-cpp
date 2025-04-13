#ifndef NOISEGENERATIONNODE_H
#define NOISEGENERATIONNODE_H

#include "Node.h"

class NoiseGenerationNode : public Node
{
public:
    NoiseGenerationNode(int order = 6);
    ~NoiseGenerationNode() override;

    // Set the desired size for the noise image.
    void setSize(int width, int height);
    // Optionally set a random seed.
    void setSeed(unsigned int seed);

    cv::Mat process(const cv::Mat &input) override;

private:
    int m_width;
    int m_height;
    unsigned int m_seed;
};

#endif // NOISEGENERATIONNODE_H
