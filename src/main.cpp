#include <QApplication>
#include "MainWindow.h"
#include "NodeGraph.h"
#include "ImageInputNode.h"
#include "OutputNode.h"
#include "BrightnessContrastNode.h"
#include "ColorChannelSplitter.h"
#include "BlurNode.h"
#include "ThresholdNode.h"
#include "EdgeDetectionNode.h"
#include "BlendNode.h"
#include "NoiseGenerationNode.h"
#include "ConvolutionFilterNode.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create main window and show UI
    MainWindow window;
    window.show();

    // Create a node graph instance
    NodeGraph graph;

    // Create input and output nodes (assume these have methods to set images externally)
    auto inputNode = std::make_shared<ImageInputNode>();
    auto brightnessNode = std::make_shared<BrightnessContrastNode>();
    auto blurNode = std::make_shared<BlurNode>();
    auto thresholdNode = std::make_shared<ThresholdNode>();
    auto edgeNode = std::make_shared<EdgeDetectionNode>();
    auto blendNode = std::make_shared<BlendNode>();
    auto noiseNode = std::make_shared<NoiseGenerationNode>();
    auto convFilterNode = std::make_shared<ConvolutionFilterNode>();
    auto outputNode = std::make_shared<OutputNode>();

    // Add nodes to the graph (the order here is sequential; later you would connect outputs to inputs)
    graph.addNode(inputNode);
    graph.addNode(brightnessNode);
    graph.addNode(blurNode);
    graph.addNode(thresholdNode);
    graph.addNode(edgeNode);
    graph.addNode(blendNode);
    graph.addNode(noiseNode);
    graph.addNode(convFilterNode);
    graph.addNode(outputNode);

    // Process all nodes (for demonstration, this sequentially calls process() on each node)
    graph.processAll();

    return app.exec();
}
