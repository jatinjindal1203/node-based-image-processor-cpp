#include <QApplication>
#include "MainWindow.h"
#include "NodeGraph.h"
#include "ImageInputNode.h"
#include "OutputNode.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create main window
    MainWindow window;
    window.show();

    // Create a node graph instance
    NodeGraph graph;

    // Create instances of nodes (for now, simply using input and output nodes)
    auto inputNode = std::make_shared<ImageInputNode>();
    auto outputNode = std::make_shared<OutputNode>();

    // Add nodes to the graph
    graph.addNode(inputNode);
    graph.addNode(outputNode);

    // Process the graph (this will, as an example, process each node sequentially)
    graph.processAll();

    return app.exec();
}
