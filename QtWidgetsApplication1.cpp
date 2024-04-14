#include "QtWidgetsApplication1.h"
#include"helpclass.h"
#include"basic_gameClass.h"
#include <QPainter>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::QtWidgetsApplication1Class)
{
    ui->setupUi(this);
    m_imgPicSrc = QImage("E:\\c train\\QtWidgetsApplication1\\image\\bg_m0ain.bmp");
    QSize initialSize = size(); 
    m_pixPic2Show = QPixmap::fromImage(m_imgPicSrc.scaled(initialSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    connect(ui->pb_helping, &QPushButton::clicked, this, &QtWidgetsApplication1::on_actionShow_help_triggered);//����
    connect(ui->pb_basic_game, &QPushButton::clicked, this, &QtWidgetsApplication1::on_actionShow_basic_game_clicked);//��ʼ������Ϸ

}
void QtWidgetsApplication1::paintEvent(QPaintEvent* event)//��дpainEvent,���Խ�ͼƬ��ӵ�widget��
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_pixPic2Show);
}
void QtWidgetsApplication1::on_actionShow_help_triggered()
{
    helpclass* help = new helpclass;
    help->show();
}
void QtWidgetsApplication1::on_actionShow_basic_game_clicked()
{
    basic_gameClass* bp = new basic_gameClass;
    bp->show();
}
QtWidgetsApplication1::~QtWidgetsApplication1()
{
    delete ui;
}
