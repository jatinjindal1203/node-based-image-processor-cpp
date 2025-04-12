#include "NoiseGenerationNode.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdlib>

NoiseGenerationNode::NoiseGenerationNode()
    : Node("Noise Generation Node"), noiseType(NoiseType::Perlin), scale(1.0), octaves(1), persistence(0.5) {}
NoiseGenerationNode::~NoiseGenerationNode() {}

void NoiseGenerationNode::setNoiseType(NoiseType type)
{
    noiseType = type;
}

void NoiseGenerationNode::setScale(double s)
{
    scale = s;
}

void NoiseGenerationNode::setOctaves(int o)
{
    octaves = o;
}

void NoiseGenerationNode::setPersistence(double p)
{
    persistence = p;
}

void NoiseGenerationNode::process()
{
    // For simplicity, create a noise image using random numbers.
    // In a real implementation, you would implement Perlin, Simplex, or Worley noise.
    int width = 640, height = 480;
    noiseImage.create(height, width, CV_8UC1);
    cv::randu(noiseImage, 0, 255);
}

const cv::Mat &NoiseGenerationNode::getResult() const
{
    return noiseImage;
}
