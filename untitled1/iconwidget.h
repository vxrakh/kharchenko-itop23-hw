#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>

class IconWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IconWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
signals:

};

#endif // ICONWIDGET_H
