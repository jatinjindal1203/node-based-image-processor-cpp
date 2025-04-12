#include "MainWindow.h"
#include <QMenuBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();
    setupMenus();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create the canvas for later node display
    canvasView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    canvasView->setScene(scene);
    layout->addWidget(canvasView);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Create a properties panel (placeholder for now)
    propertiesPanel = new QDockWidget(tr("Properties"), this);
    propertiesPanel->setWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, propertiesPanel);
}

void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Open"), this, SLOT(openImage()));
    fileMenu->addAction(tr("Save"), this, SLOT(saveImage()));
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    // For now, this is just a placeholder; later, you'll integrate this with your Image Input Node.
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    // Placeholder; later, this will interface with your Output Node.
}
