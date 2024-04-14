#include "labelClicked.h"
#include<qpainter.h>
#include<qpoint.h>
void labelClicked::mousePressEvent(QMouseEvent* event)
{
        if (event->button() == Qt::LeftButton)
        {
            m_shouldDrawBox = true;
            update();
            emit mousePressed(this,event->pos());
        }
        QLabel::mousePressEvent(event);
}
void labelClicked::paintEvent(QPaintEvent* event)
{
    QLabel::paintEvent(event);
    if (m_shouldDrawBox)
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine));
        painter.drawRect(rect().adjusted(1, 1, -1, -1));
    }
}

void labelClicked::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit mouseReleased(this, event->pos());
    }
    QLabel::mouseReleaseEvent(event);
}
