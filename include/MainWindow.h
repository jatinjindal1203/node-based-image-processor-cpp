#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <memory>

class QGraphicsView;
class QDockWidget;
class NodeScene;
class NodeGraph;
class ImageInputNode; // our processing node for input

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage(); // Loads image and triggers processing.
    void saveImage(); // Saves the final processed image.

private:
    QGraphicsView *canvasView;
    QDockWidget *previewPanel; // Preview area widget.
    NodeScene *scene;          // Visual scene (if used for node visualization).
    NodeGraph *graph;          // Our processing pipeline graph.

    cv::Mat currentImage; // The image loaded from disk.
    cv::Mat finalImage;   // The final processed image.

    // Store the input node pointer so that we can update it when an image is opened.
    std::shared_ptr<ImageInputNode> m_inputNode;

    void setupUI();
    void processPipeline(); // Runs the pipeline and updates the preview.
};

#endif // MAINWINDOW_H
