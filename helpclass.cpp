#include "helpclass.h"
#include"qlabel.h"
#include <qboxlayout.h>
helpclass::helpclass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidgetResizable(false);//����ʹ��ͼƬ��������

	ui.scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//��ʾ����������

	ui.scrollArea->setWidget(ui.scrollAreaWidgetContents);
	QLabel* label = new QLabel;
	m_pix = QPixmap("E:\\c train\\QtWidgetsApplication1\\image\\basic_help.bmp");
	label->setPixmap(m_pix);
	label->setFixedSize(m_pix.size());
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);//���������С�����ܸ��ؼ�Ӱ��
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(label);
	ui.scrollArea->setLayout(layout);
	ui.scrollArea->setWidget(label);
}

helpclass::~helpclass()
{}

