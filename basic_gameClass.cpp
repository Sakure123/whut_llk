#include "basic_gameClass.h"
#include<Qpainter>
#include<QKeyEvent>
#include <qlayout.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <random>
#include <qlabel.h>
#include<qtimer.h>
#include<QMessageBox>
#include"labelClicked.h"
#include"CGameControl.h"
basic_gameClass::basic_gameClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_isLocked = false;
	m_image = QImage("E:\\c train\\QtWidgetsApplication1\\image\\fruit_b0g.bmp");//���뱳��ͼƬ
	QSize initialSize = size(); //����ͼƬ��СΪQwidget��Ĭ�ϴ�С
	m_Pixmap = QPixmap::fromImage(m_image.scaled(initialSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));//��ͼƬ���뵽������
	setPicture();//����ˮ��ͼƬ
	connect(ui.pb_stop_game, &QPushButton::clicked, this, &basic_gameClass::toggleLockInterface);//��ͣ��Ϸ
	connect(ui.pb_refresh_game, &QPushButton::clicked, this, &basic_gameClass::restartGame);//����
	connect(ui.pb_showinfor_game, &QPushButton::clicked, this, &basic_gameClass::helpinformation);//��ʾ
	connect(ui.pb_begin_game, &QPushButton::clicked, this, &basic_gameClass::startCountdown);//��ʼ��Ϸ
}
void basic_gameClass::paintEvent(QPaintEvent * event)//��дpaintEvent�࣬ʹ�õ��ͼƬ���к����ʾ
{
	QPainter painter(this);
	painter.drawPixmap(rect(), m_Pixmap);
}

void basic_gameClass::setPicture()
{
	gamecontrol.InitGraph();//��ʼ����ͼ����
	std::vector<QString> imagePaths = {
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_0.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_1.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_2.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_3.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_4.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_5.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_6.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_7.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_8.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_9.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_10.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_11.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_12.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_13.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_14.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_15.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_16.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_17.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_18.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_19.png"
	}; // ͼƬ·���б�
	QGridLayout* gridLayout = new QGridLayout;//�������񲼾�
	std::random_device rd; //���������
	std::mt19937 g(rd()); //����mt1997��g�㷨�������
	std::vector<int> shuff(19); //����洢ͼƬ����
	gridLayout->setVerticalSpacing(0); //���ò����е�ͼƬ��߾�Ϊ0
	gridLayout->setHorizontalSpacing(0); //���ò����е�ͼƬ�ݱ߾�Ϊ0
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols;col++) {

			labelClicked* label = new labelClicked(this);
			std::uniform_int_distribution<> index(0, shuff.size());
			int randomIndex = index(g);//ʹ�����������������
			QPixmap pixmap(imagePaths[randomIndex]);
			label->setPixmap(pixmap);
			label->setFixedSize(40, 40);//����label��ǩ��СΪ40,40
			label->setMaximumSize(40, 40);//����label����СΪ40��40
			label->setMinimumSize(40, 40);//������СΪ40��40
			labels.push_back(label);
			gridLayout->addWidget(label, row, col);//��ӵ�����
			connect(label, &labelClicked::mousePressed, this, &basic_gameClass::onLabelPressed1);//Ϊÿ��label���������¼�
			connect(label, &labelClicked::mouseReleased, this, &basic_gameClass::onLabelReleased);//Ϊÿ��label�������ͷ��¼�
		}
	}
	ui.widget->setLayout(gridLayout);//������������ӵ�widget����
}

void basic_gameClass::onLabelPressed1(labelClicked* label, const QPoint& pos)
{
	
	if (clickedlabels.size() > 2)
	{
		clickedlabels.pop();
	}
	clickedlabels.push(label);//��֤ջ�����ֻ������Ԫ��
}

void basic_gameClass::onLabelReleased(labelClicked* label, const QPoint& pos)
{
	if (clickedlabels.size()==2)
	{
		labelClicked* firstClicked = clickedlabels.top();
		clickedlabels.pop();
		labelClicked* secondClicked = clickedlabels.top();
		if (areImagesEqual(firstClicked, secondClicked) == true)//�ж�����ͼƬ�Ƿ�Ϊһ��ͼƬ
		{
			QGridLayout* gridLayout = dynamic_cast<QGridLayout*>(ui.widget->layout());
			for (int row = 0; row < gridLayout->rowCount(); row++)
			{
				for (int col = 0; col < gridLayout->columnCount(); col++)
				{
					QWidget* widgetAtPosition = gridLayout->itemAtPosition(row, col)->widget();//��ȡͼƬ���С���
					if (widgetAtPosition == firstClicked)
					{
						gamecontrol.SetFirstPoint(row, col);//��ͼƬ��������ӵ���һ������
					}
				}
			}
			for (int row = 0; row < gridLayout->rowCount(); row++)
			{
				for (int col = 0; col < gridLayout->columnCount(); col++)
				{
					QWidget* widge = gridLayout->itemAtPosition(row, col)->widget();
					if (widge == secondClicked)
					{
						gamecontrol.SetSecPoint(row, col);//��ͼƬ��������ӵ��ڶ�������
					}
				}
			}
			if (gamecontrol.Link())
			{
				firstClicked->hide();
				secondClicked->hide();//����ͼƬ
				gamelogic.Clear(gamecontrol.m_ptSelFirst, gamecontrol.m_ptSelSec);//���µ�ͼ����
				if (success_game())
				{
					QMessageBox::information(nullptr, "success", "congratulate!");//ͼƬȫ�������󣬵���ʤ������
				}
			}
		}

			while (!clickedlabels.empty())
			{
				clickedlabels.pop();//ÿ���жϺ����ջ
			}
	}
	
}

bool basic_gameClass::areImagesEqual(const labelClicked* label1, const labelClicked* label2)//�ж�ͼƬ�Ƿ�Ϊͬһ��
{
	QPixmap imag1 = label1->pixmap();
	QPixmap imag2 = label2->pixmap();
	return imag1.toImage()==imag2.toImage();
}

void basic_gameClass::toggleLockInterface()//����������
{
	if (m_isLocked)
	{
		onUnlockInterface();
	}
	else
	{
		onLockInterface();
	}
}
void basic_gameClass::onLockInterface()//��ס����
{
	m_isLocked = true;
	for (auto child : findChildren<QWidget*>()) {
		if(child!=ui.pb_stop_game)//������ͣ��ť��Ҫ����Ϊ������ť
			child->setEnabled(false);
	}
}

void basic_gameClass::onUnlockInterface()//���濪��
{
	m_isLocked = false;
	for (auto child : findChildren<QWidget*>())
	{
		child->setEnabled(true);
	}
	this->setFocus(Qt::OtherFocusReason);
}
void basic_gameClass::restartGame()//����
{
	gamecontrol.InitGraph();
	std::vector<QString> imagePaths = {
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_0.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_1.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_2.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_3.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_4.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_5.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_6.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_7.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_8.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_9.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_10.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_11.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_12.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_13.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_14.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_15.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_16.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_17.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_18.png",
		"E:\\c train\\QtWidgetsApplication1\\image\\output\\new_image_19.png"
	}; // ͼƬ·���б�
	int numRows = 10;
	int numCols = 16;
	std::random_device rd;
	std::mt19937 g(rd());
	std::vector<int> shuff(19);
	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			labelClicked* label = labels[row*16+col];
			std::uniform_int_distribution<> index(0, shuff.size());
			int randomIndex = index(g);
			QPixmap pixmap(imagePaths[randomIndex]);
			label->setPixmap(pixmap);
		}
	}
}
void basic_gameClass::helpinformation()//��ʾ
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			labelClicked* firstClicked = labels[i * 16 + j];
			for (int k = 0; k < 10; k++)
			{
				for (int g = 0; g < 16; g++)
				{
					labelClicked* secondClicked = labels[k * 16 + g];
					if (areImagesEqual(firstClicked, secondClicked) == true)
					{
						gamecontrol.SetFirstPoint(i, j);
						gamecontrol.SetSecPoint(k, g);
						if (gamecontrol.Link())
						{
							firstClicked->setStyleSheet("border:1px solid blue");//��ͼƬ�߿��Ϊ��ɫ
							secondClicked->setStyleSheet("border:1px solid blue");
							QTimer timer;
							connect(&timer, &QTimer::timeout, firstClicked, &QLabel::hide);
							connect(&timer, &QTimer::timeout, secondClicked, &QLabel::hide);
							timer.setSingleShot(true);
							timer.start(1000);//����10��
							return;
						}
					}
				}
			}
		}
	}
	
}
bool basic_gameClass::success_game()//�ж���Ϸ�Ƿ�ʤ��
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (GGraph::m_AdjMatrix[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
void basic_gameClass::startCountdown()//��������ʼ��ʱ
{
	countdowntimer = new QTimer(this);
	ui.progressBar->setRange(0, 400);
	ui.progressBar->setValue(400);
	countdowntimer->setInterval(1000);
	connect(countdowntimer, &QTimer::timeout, this, &basic_gameClass::updateCountdownProgress);
	countdowntimer->start();
	ui.pb_begin_game->setEnabled(false);
}
void basic_gameClass::updateCountdownProgress()//���½�����
{
	if (m_isstop)
	{
		if (remainingSeconds > 0)
		{
			--remainingSeconds;
			ui.progressBar->setValue(remainingSeconds);
			ui.progressBar->setFormat("%v");//ʹ�ý���������ʾʣ��ʱ��
		}
		else
		{
			countdowntimer->stop();
			ui.progressBar->setValue(0);
			QMessageBox::information(nullptr, "end", "failure");//ʱ��Ϊ0������ʧ��
			ui.pb_begin_game->setEnabled(true);
		}
	}
}
void basic_gameClass::keyPressEvent(QKeyEvent* event)//��д���̼�������
{

		if (event->key() == Qt::Key_U)//��סu����ֱ��ʧ��
		{
			remainingSeconds = 0;
			updateCountdownProgress();
			event->accept();
		}
		if (event->key() == Qt::Key_A)//��סa����һ���ɹ�
		{
			for (auto child : ui.widget->children()) {
				if (auto childWidget = dynamic_cast<labelClicked*>(child)) {
					childWidget->setVisible(false);
				}
			}
			m_isstop = false;
			QMessageBox::information(nullptr, "success", "congratulate!");
		}
		QWidget::keyPressEvent(event);
}
basic_gameClass::~basic_gameClass()
{}
