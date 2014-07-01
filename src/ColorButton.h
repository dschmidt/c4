#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QColor>

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorButton(QWidget* parent = 0);

    const QColor color() const;

public slots:
    void setColor(const QColor& color);

private slots:
    void openColorDialog();

private:
    QColor m_color;
};

#endif // COLORBUTTON_H
