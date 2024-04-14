#include "helpclass.h"
#include"qlabel.h"
#include <qboxlayout.h>
helpclass::helpclass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidgetResizable(false);//可以使得图片可以拖拉

	ui.scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//显示上下拖拉栏

	ui.scrollArea->setWidget(ui.scrollAreaWidgetContents);
	QLabel* label = new QLabel;
	m_pix = QPixmap("E:\\c train\\QtWidgetsApplication1\\image\\basic_help.bmp");
	label->setPixmap(m_pix);
	label->setFixedSize(m_pix.size());
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);//保持自身大小，不受父控件影响
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(label);
	ui.scrollArea->setLayout(layout);
	ui.scrollArea->setWidget(label);
}

helpclass::~helpclass()
{}

