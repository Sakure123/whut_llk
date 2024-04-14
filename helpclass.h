#pragma once

#include <QWidget>
#include"qpainter.h"
#include "ui_helpclass.h"

class helpclass : public QWidget
{
	Q_OBJECT

public:
	helpclass(QWidget *parent = nullptr);
	~helpclass();
private:
	Ui::helpclass ui;
	QImage m_img;
	QPixmap m_pix;
};
