#include "MainWindow.h"
#include "NodeGraph.h"
#include "NodeScene.h"
#include "ImageInputNode.h"
#include "OutputNode.h"
#include "BrightnessContrastNode.h"
#include "BlurNode.h"
#include "ThresholdNode.h"
#include "EdgeDetectionNode.h"
#include "BlendNode.h"
#include "NoiseGenerationNode.h"
#include "ConvolutionFilterNode.h"
#include "ColorChannelSplitter.h"

#include <QGraphicsView>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QDebug>

// Helper function to convert cv::Mat to QImage.
QImage cvMatToQImage(const cv::Mat &mat)
{
    if (mat.empty())
        return QImage();
    cv::Mat rgb;
    if (mat.channels() == 3)
    {
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
        return QImage(rgb.data, rgb.cols, rgb.rows, static_cast<int>(rgb.step), QImage::Format_RGB888).copy();
    }
    else if (mat.channels() == 1)
    {
        return QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8).copy();
    }
    return QImage();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();

    // Create our processing graph.
    graph = new NodeGraph();

    // Create nodes for the processing pipeline.
    // Store the ImageInputNode so we can update it later.
    m_inputNode = std::make_shared<ImageInputNode>();
    auto brightNode = std::make_shared<BrightnessContrastNode>(2);
    brightNode->setBrightness(20);
    brightNode->setContrast(1.2);
    auto blurNode = std::make_shared<BlurNode>(3);
    blurNode->setKernelSize(5);
    auto threshNode = std::make_shared<ThresholdNode>(4);
    threshNode->setThreshold(150);
    auto edgeNode = std::make_shared<EdgeDetectionNode>(5);
    edgeNode->setThresholds(30, 100);
    auto outNode = std::make_shared<OutputNode>(); // Output node, order 100 by default

    // Add nodes to the processing graph.
    graph->addNode(m_inputNode);
    graph->addNode(brightNode);
    graph->addNode(blurNode);
    graph->addNode(threshNode);
    graph->addNode(edgeNode);
    graph->addNode(outNode);

    // Create a simple toolbar for load/save operations.
    QToolBar *toolbar = addToolBar("Main Controls");
    QAction *openAct = toolbar->addAction("Load Image");
    QAction *saveAct = toolbar->addAction("Save Image");
    connect(openAct, &QAction::triggered, this, &MainWindow::openImage);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveImage);
}

MainWindow::~MainWindow()
{
    delete graph;
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // Create a graphics view (can be used for visual node representation).
    canvasView = new QGraphicsView(this);
    // For now, use a basic QGraphicsScene. (Later, you might use your NodeScene.)
    canvasView->setScene(new QGraphicsScene(this));
    layout->addWidget(canvasView);

    central->setLayout(layout);
    setCentralWidget(central);

    // Create a preview panel at the bottom.
    previewPanel = new QDockWidget("Preview", this);
    // Set an initial label.
    previewPanel->setWidget(new QLabel("Preview will appear here", this));
    addDockWidget(Qt::BottomDockWidgetArea, previewPanel);
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        // Load the image using OpenCV.
        currentImage = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);
        if (currentImage.empty())
        {
            qDebug() << "Error loading image.";
            return;
        }
        qDebug() << "Image loaded:" << currentImage.cols << "x" << currentImage.rows;

        // Update the input node with the loaded image.
        m_inputNode->setImage(currentImage);

        // Run the processing pipeline.
        processPipeline();
    }
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty() && !finalImage.empty())
    {
        cv::imwrite(fileName.toStdString(), finalImage);
        qDebug() << "Image saved to:" << fileName;
    }
}

void MainWindow::processPipeline()
{
    // Process the image through the node graph.
    finalImage = graph->processAll(currentImage);

    // Update the preview panel with the final image.
    QImage qimg = cvMatToQImage(finalImage);
    QLabel *previewLabel = new QLabel();
    previewLabel->setPixmap(QPixmap::fromImage(qimg));
    previewLabel->setScaledContents(true);
    previewPanel->setWidget(previewLabel);
}
