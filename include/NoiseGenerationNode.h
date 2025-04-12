#ifndef NOISEGENERATIONNODE_H
#define NOISEGENERATIONNODE_H

#include "Node.h"
#include <opencv2/opencv.hpp>

enum class NoiseType
{
    Perlin,
    Simplex,
    Worley
};

class NoiseGenerationNode : public Node
{
public:
    NoiseGenerationNode();
    virtual ~NoiseGenerationNode();

    // Set noise parameters
    void setNoiseType(NoiseType type);
    void setScale(double scale);
    void setOctaves(int octaves);
    void setPersistence(double persistence);

    // Process: generate noise. For demonstration, we'll generate random noise.
    void process() override;

    const cv::Mat &getResult() const;

private:
    cv::Mat noiseImage;
    NoiseType noiseType;
    double scale;       // affects frequency of noise
    int octaves;        // number of noise layers
    double persistence; // roughness or amplitude
};

#endif // NOISEGENERATIONNODE_H
