#pragma once
#include <qlabel.h>
#include<QMouseEvent>
#include<QString>
class labelClicked :
    public QLabel//继承qlabel的类，用于添加鼠标点击事件
{
    Q_OBJECT
public:
    using QLabel::QLabel;
protected:
    void mousePressEvent(QMouseEvent* event)override;
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void mousePressed(labelClicked *,const QPoint &);
    void mouseReleased(labelClicked*, const QPoint&);
private:
    bool m_shouldDrawBox = false;
};

