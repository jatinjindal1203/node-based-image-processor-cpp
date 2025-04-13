#ifndef NODE_H
#define NODE_H

#include <QString>
#include <opencv2/opencv.hpp>

// Abstract base class for processing nodes
class Node
{
public:
    Node(const QString &name, int order = 0)
        : m_name(name), m_order(order) {}
    virtual ~Node() {}

    QString name() const { return m_name; }
    int order() const { return m_order; }
    void setOrder(int order) { m_order = order; }

    // Process the input image and return the processed image.
    virtual cv::Mat process(const cv::Mat &input) = 0;

protected:
    QString m_name;
    int m_order;
};

#endif // NODE_H
