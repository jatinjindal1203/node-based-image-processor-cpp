#include "MainWindow.h"
#include "NodeItem.h" // Our visual node representation
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QFileDialog>
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupMenus();
}

MainWindow::~MainWindow() {}

// This function sets up the central UI: the graphics scene and view, plus the properties panel.
void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create a QGraphicsView and QGraphicsScene as the canvas.
    canvasView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    canvasView->setScene(scene);
    layout->addWidget(canvasView);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Create a properties panel as a dockable widget.
    propertiesPanel = new QDockWidget(tr("Properties"), this);
    // For now, it is an empty widget; later you will add controls dynamically based on selected node.
    propertiesPanel->setWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, propertiesPanel);
}

// This function sets up all the menus (File and Nodes) in the menu bar.
void MainWindow::setupMenus()
{
    // File Menu: Open/Save actions.
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Open"), this, SLOT(openImage()));
    fileMenu->addAction(tr("Save"), this, SLOT(saveImage()));

    // Nodes Menu: Actions to add different types of nodes.
    QMenu *nodesMenu = menuBar()->addMenu(tr("Nodes"));

    // Add action to create an Input Node
    QAction *inputAction = new QAction(tr("Add Input Node"), this);
    connect(inputAction, &QAction::triggered, this, &MainWindow::addInputNode);
    nodesMenu->addAction(inputAction);

    // Add action to create a Brightness/Contrast Node
    QAction *brightContrastAction = new QAction(tr("Add Brightness/Contrast Node"), this);
    connect(brightContrastAction, &QAction::triggered, this, &MainWindow::addBrightnessContrastNode);
    nodesMenu->addAction(brightContrastAction);

    // Add action to create a Blur Node
    QAction *blurAction = new QAction(tr("Add Blur Node"), this);
    connect(blurAction, &QAction::triggered, this, &MainWindow::addBlurNode);
    nodesMenu->addAction(blurAction);

    // Add action to create a Threshold Node
    QAction *thresholdAction = new QAction(tr("Add Threshold Node"), this);
    connect(thresholdAction, &QAction::triggered, this, &MainWindow::addThresholdNode);
    nodesMenu->addAction(thresholdAction);

    // Add action to create an Edge Detection Node
    QAction *edgeAction = new QAction(tr("Add Edge Detection Node"), this);
    connect(edgeAction, &QAction::triggered, this, &MainWindow::addEdgeDetectionNode);
    nodesMenu->addAction(edgeAction);

    // Add action to create a Blend Node
    QAction *blendAction = new QAction(tr("Add Blend Node"), this);
    connect(blendAction, &QAction::triggered, this, &MainWindow::addBlendNode);
    nodesMenu->addAction(blendAction);

    // Add action to create a Noise Generation Node
    QAction *noiseAction = new QAction(tr("Add Noise Generation Node"), this);
    connect(noiseAction, &QAction::triggered, this, &MainWindow::addNoiseGenerationNode);
    nodesMenu->addAction(noiseAction);

    // Add action to create a Convolution Filter Node
    QAction *convAction = new QAction(tr("Add Convolution Filter Node"), this);
    connect(convAction, &QAction::triggered, this, &MainWindow::addConvolutionFilterNode);
    nodesMenu->addAction(convAction);
}

void MainWindow::openImage()
{
    // Open image file dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty())
    {
        // For now, simply display the file name in console (later integrate with Input Node)
        qDebug() << "Open image:" << fileName;
    }
}

void MainWindow::saveImage()
{
    // Save image file dialog
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty())
    {
        // For now, simply display the file name in console (later integrate with Output Node)
        qDebug() << "Save image as:" << fileName;
    }
}

// Node creation slots – these create a NodeItem (the visual representation) and add it to the scene.
// In a complete system, you might also instantiate a processing node (e.g., a BrightnessContrastNode class)
// and store its pointer in a NodeGraph for processing.

// This is an example for Input Node:
void MainWindow::addInputNode()
{
    NodeItem *node = new NodeItem("Input Node");
    node->setPos(50, 50); // You may choose a suitable position or center it in the view
    scene->addItem(node);
}

// Brightness/Contrast Node:
void MainWindow::addBrightnessContrastNode()
{
    NodeItem *node = new NodeItem("Brightness/Contrast Node");
    node->setPos(200, 50);
    scene->addItem(node);
}

// Blur Node:
void MainWindow::addBlurNode()
{
    NodeItem *node = new NodeItem("Blur Node");
    node->setPos(350, 50);
    scene->addItem(node);
}

// Threshold Node:
void MainWindow::addThresholdNode()
{
    NodeItem *node = new NodeItem("Threshold Node");
    node->setPos(500, 50);
    scene->addItem(node);
}

// Edge Detection Node:
void MainWindow::addEdgeDetectionNode()
{
    NodeItem *node = new NodeItem("Edge Detection Node");
    node->setPos(650, 50);
    scene->addItem(node);
}

// Blend Node:
void MainWindow::addBlendNode()
{
    NodeItem *node = new NodeItem("Blend Node");
    node->setPos(50, 150);
    scene->addItem(node);
}

// Noise Generation Node:
void MainWindow::addNoiseGenerationNode()
{
    NodeItem *node = new NodeItem("Noise Generation Node");
    node->setPos(200, 150);
    scene->addItem(node);
}

// Convolution Filter Node:
void MainWindow::addConvolutionFilterNode()
{
    NodeItem *node = new NodeItem("Convolution Filter Node");
    node->setPos(350, 150);
    scene->addItem(node);
}
