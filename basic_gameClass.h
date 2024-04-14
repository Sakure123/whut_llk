#pragma once

#include <QWidget>
#include "ui_basic_gameClass.h"
#include <QLabel>
#include<stack>
#include"labelClicked.h"
#include "CGameControl.h"
#include"QDialog.h"

class basic_gameClass : public QWidget
{
	Q_OBJECT

public:
	basic_gameClass(QWidget *parent = nullptr);
	~basic_gameClass();
	virtual void paintEvent(QPaintEvent* event);
	virtual void keyPressEvent(QKeyEvent* event) override;
	void setPicture();
	void onLabelPressed1(labelClicked* label, const QPoint& pos);
	void onLabelReleased(labelClicked* label, const QPoint& pos);
	bool areImagesEqual(const labelClicked* label1, const labelClicked* label2);
	void toggleLockInterface();
	void onLockInterface();
	void onUnlockInterface();
	void restartGame();
	void helpinformation();
	bool success_game();
public slots:
	void startCountdown();
	void updateCountdownProgress();
private:
	Ui::basic_gameClassClass ui;
	int numRows = 10;//行
	int numCols = 16;//列
	QImage m_image;
	QPixmap m_Pixmap;
	std::vector<labelClicked*> labels;
	std::stack<labelClicked*> clickedlabels;
	CGameControl gamecontrol;//游戏逻辑控制
	CGameLogic gamelogic;//地图连线判断
	bool m_isLocked;
	QTimer* countdowntimer;
	int remainingSeconds = 400;//时间总数
	bool m_isstop = true;
};
