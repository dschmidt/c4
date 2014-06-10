#ifndef ARTOOLKIWWIDGET_H
#define ARTOOLKIWWIDGET_H

#include <QGLWidget>

namespace Ui {
class ARToolkitWidget;
}

class ARToolkitWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit ARToolkitWidget(QWidget* parent = 0);
    virtual ~ARToolkitWidget();
};

#endif // ARTOOLKIWWIDGET_H
