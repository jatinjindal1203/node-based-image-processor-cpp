#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDockWidget>

// Forward declaration for NodeItem
class NodeItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveImage();

    // New slots for adding nodes from the menu
    void addInputNode();
    void addBrightnessContrastNode();
    void addBlurNode();
    void addThresholdNode();
    void addEdgeDetectionNode();
    void addBlendNode();
    void addNoiseGenerationNode();
    void addConvolutionFilterNode();

private:
    QGraphicsView *canvasView;
    QGraphicsScene *scene;
    QDockWidget *propertiesPanel;

    void setupUI();
    void setupMenus();
};

#endif // MAINWINDOW_H
