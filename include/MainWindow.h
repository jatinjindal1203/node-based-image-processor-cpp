#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveImage();

private:
    QGraphicsView *canvasView;
    QGraphicsScene *scene;
    QDockWidget *propertiesPanel;

    void setupUI();
    void setupMenus();
};

#endif // MAINWINDOW_H
