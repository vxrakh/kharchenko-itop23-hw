#include "iconwidget.h"
#include <QPainter>

IconWidget::IconWidget(QWidget *parent)
    : QWidget{parent}
{

}


void IconWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Set up the colors and pen
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    // Draw the cup body
    painter.setBrush(Qt::white);
    painter.drawEllipse(QRectF(50, 50, 200, 200));

    // Draw the cup handle
    painter.setBrush(Qt::black);
    painter.drawEllipse(QRectF(200, 110, 60, 80));

    // Draw the coffee
    painter.setBrush(Qt::darkGreen);
    painter.drawEllipse(QRectF(70, 70, 180, 180));

    // Draw steam lines
    painter.setPen(Qt::white);
    painter.drawLine(QPointF(120, 100), QPointF(120, 60));
    painter.drawLine(QPointF(150, 100), QPointF(150, 50));
    painter.drawLine(QPointF(180, 100), QPointF(180, 60));
}
