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
	m_image = QImage("E:\\c train\\QtWidgetsApplication1\\image\\fruit_b0g.bmp");//导入背景图片
	QSize initialSize = size(); //设置图片大小为Qwidget的默认大小
	m_Pixmap = QPixmap::fromImage(m_image.scaled(initialSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));//将图片加入到容器中
	setPicture();//设置水果图片
	connect(ui.pb_stop_game, &QPushButton::clicked, this, &basic_gameClass::toggleLockInterface);//暂停游戏
	connect(ui.pb_refresh_game, &QPushButton::clicked, this, &basic_gameClass::restartGame);//重排
	connect(ui.pb_showinfor_game, &QPushButton::clicked, this, &basic_gameClass::helpinformation);//提示
	connect(ui.pb_begin_game, &QPushButton::clicked, this, &basic_gameClass::startCountdown);//开始游戏
}
void basic_gameClass::paintEvent(QPaintEvent * event)//重写paintEvent类，使得点击图片会有红框显示
{
	QPainter painter(this);
	painter.drawPixmap(rect(), m_Pixmap);
}

void basic_gameClass::setPicture()
{
	gamecontrol.InitGraph();//初始化地图数组
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
	}; // 图片路径列表
	QGridLayout* gridLayout = new QGridLayout;//设置网格布局
	std::random_device rd; //设置随机数
	std::mt19937 g(rd()); //采用mt1997的g算法进行随机
	std::vector<int> shuff(19); //数组存储图片索引
	gridLayout->setVerticalSpacing(0); //设置布局中的图片横边距为0
	gridLayout->setHorizontalSpacing(0); //设置布局中的图片纵边距为0
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols;col++) {

			labelClicked* label = new labelClicked(this);
			std::uniform_int_distribution<> index(0, shuff.size());
			int randomIndex = index(g);//使用随机数引擎进行随机
			QPixmap pixmap(imagePaths[randomIndex]);
			label->setPixmap(pixmap);
			label->setFixedSize(40, 40);//设置label标签大小为40,40
			label->setMaximumSize(40, 40);//设置label最大大小为40，40
			label->setMinimumSize(40, 40);//设置最小为40，40
			labels.push_back(label);
			gridLayout->addWidget(label, row, col);//添加到布局
			connect(label, &labelClicked::mousePressed, this, &basic_gameClass::onLabelPressed1);//为每个label添加鼠标点击事件
			connect(label, &labelClicked::mouseReleased, this, &basic_gameClass::onLabelReleased);//为每个label添加鼠标释放事件
		}
	}
	ui.widget->setLayout(gridLayout);//将整个布局添加到widget容器
}

void basic_gameClass::onLabelPressed1(labelClicked* label, const QPoint& pos)
{
	
	if (clickedlabels.size() > 2)
	{
		clickedlabels.pop();
	}
	clickedlabels.push(label);//保证栈里最大只有两个元素
}

void basic_gameClass::onLabelReleased(labelClicked* label, const QPoint& pos)
{
	if (clickedlabels.size()==2)
	{
		labelClicked* firstClicked = clickedlabels.top();
		clickedlabels.pop();
		labelClicked* secondClicked = clickedlabels.top();
		if (areImagesEqual(firstClicked, secondClicked) == true)//判断两个图片是否为一种图片
		{
			QGridLayout* gridLayout = dynamic_cast<QGridLayout*>(ui.widget->layout());
			for (int row = 0; row < gridLayout->rowCount(); row++)
			{
				for (int col = 0; col < gridLayout->columnCount(); col++)
				{
					QWidget* widgetAtPosition = gridLayout->itemAtPosition(row, col)->widget();//获取图片的行、列
					if (widgetAtPosition == firstClicked)
					{
						gamecontrol.SetFirstPoint(row, col);//将图片的行列添加到第一个点中
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
						gamecontrol.SetSecPoint(row, col);//将图片的行列添加到第二个点中
					}
				}
			}
			if (gamecontrol.Link())
			{
				firstClicked->hide();
				secondClicked->hide();//隐藏图片
				gamelogic.Clear(gamecontrol.m_ptSelFirst, gamecontrol.m_ptSelSec);//更新地图数组
				if (success_game())
				{
					QMessageBox::information(nullptr, "success", "congratulate!");//图片全部消除后，弹出胜利窗口
				}
			}
		}

			while (!clickedlabels.empty())
			{
				clickedlabels.pop();//每次判断后，清空栈
			}
	}
	
}

bool basic_gameClass::areImagesEqual(const labelClicked* label1, const labelClicked* label2)//判断图片是否为同一种
{
	QPixmap imag1 = label1->pixmap();
	QPixmap imag2 = label2->pixmap();
	return imag1.toImage()==imag2.toImage();
}

void basic_gameClass::toggleLockInterface()//界面锁函数
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
void basic_gameClass::onLockInterface()//锁住界面
{
	m_isLocked = true;
	for (auto child : findChildren<QWidget*>()) {
		if(child!=ui.pb_stop_game)//除了暂停按钮，要用其为解锁按钮
			child->setEnabled(false);
	}
}

void basic_gameClass::onUnlockInterface()//界面开锁
{
	m_isLocked = false;
	for (auto child : findChildren<QWidget*>())
	{
		child->setEnabled(true);
	}
	this->setFocus(Qt::OtherFocusReason);
}
void basic_gameClass::restartGame()//重排
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
	}; // 图片路径列表
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
void basic_gameClass::helpinformation()//提示
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
							firstClicked->setStyleSheet("border:1px solid blue");//将图片边框变为蓝色
							secondClicked->setStyleSheet("border:1px solid blue");
							QTimer timer;
							connect(&timer, &QTimer::timeout, firstClicked, &QLabel::hide);
							connect(&timer, &QTimer::timeout, secondClicked, &QLabel::hide);
							timer.setSingleShot(true);
							timer.start(1000);//持续10秒
							return;
						}
					}
				}
			}
		}
	}
	
}
bool basic_gameClass::success_game()//判断游戏是否胜利
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
void basic_gameClass::startCountdown()//进度条开始计时
{
	countdowntimer = new QTimer(this);
	ui.progressBar->setRange(0, 400);
	ui.progressBar->setValue(400);
	countdowntimer->setInterval(1000);
	connect(countdowntimer, &QTimer::timeout, this, &basic_gameClass::updateCountdownProgress);
	countdowntimer->start();
	ui.pb_begin_game->setEnabled(false);
}
void basic_gameClass::updateCountdownProgress()//更新进度条
{
	if (m_isstop)
	{
		if (remainingSeconds > 0)
		{
			--remainingSeconds;
			ui.progressBar->setValue(remainingSeconds);
			ui.progressBar->setFormat("%v");//使得进度条旁显示剩余时间
		}
		else
		{
			countdowntimer->stop();
			ui.progressBar->setValue(0);
			QMessageBox::information(nullptr, "end", "failure");//时间为0，弹出失败
			ui.pb_begin_game->setEnabled(true);
		}
	}
}
void basic_gameClass::keyPressEvent(QKeyEvent* event)//重写键盘监听函数
{

		if (event->key() == Qt::Key_U)//按住u可以直接失败
		{
			remainingSeconds = 0;
			updateCountdownProgress();
			event->accept();
		}
		if (event->key() == Qt::Key_A)//按住a可以一键成功
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
