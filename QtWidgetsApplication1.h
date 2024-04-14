#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();
    //virtual void resizeEvent(QResizeEvent* event);
    //virtual void showEvent(QShowEvent* event);
    virtual void paintEvent(QPaintEvent* event);
public slots:
    void on_actionShow_help_triggered();
    void on_actionShow_basic_game_clicked();
private:
    Ui::QtWidgetsApplication1Class *ui;
    QImage m_imgPicSrc;
    QImage m_imgPicShow;
    QPixmap m_pixPic2Show;
    
};
