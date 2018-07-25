#include "progressbar.h"
#include <QDebug>

ProgressBar::ProgressBar(QWidget *parent) :
    QWidget(parent)
{
    initVariables();
}

void ProgressBar::initVariables()
{
    m_bgClr = QColor(100,100,100);
    m_nMin = 0;
    m_nMax = 100;
    m_nCurrentValue = 0;
    m_nValue = 0;
    m_BarLength = 0;
    m_nCurrentXPos = 0;

    m_bReverse = false;
    m_bBarReverse = false;
    m_bSuspending = true;

    m_updateTimer=new QTimer(this);
    m_updateTimer->setInterval(30);
    connect(m_updateTimer,SIGNAL(timeout()),this,SLOT(UpdateData()));

    m_suspendingTimer=new QTimer(this);
    m_suspendingTimer->setInterval(10);
    connect(m_suspendingTimer,SIGNAL(timeout()),this,SLOT(DoSuspending()));
//    StartSuspending();

}

void ProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.setRenderHints(QPainter::Antialiasing);
    drawBackground(&painter);
    drawBar(&painter);
}
/*!
  private slot functions
*/
void ProgressBar::UpdateData()
{

}

void ProgressBar::DoSuspending()
{
    if(!m_bBarReverse)
    {
        m_nCurrentXPos++;

        if(m_nCurrentXPos + m_BarLength >= width() - PB_EXTRA_SPACE)
        {
            m_bBarReverse = true;
        }
    }else{
        m_nCurrentXPos--;

        if(m_nCurrentXPos <= 0)
        {
            m_bBarReverse = false;
        }
    }

    update();
}

/*!
  private painting functions
*/
void ProgressBar::drawBackground(QPainter *painter)
{

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBackground(m_bgClr);
    painter->drawRect(rect());
    painter->restore();
}

void ProgressBar::drawBar(QPainter *painter)
{
    painter->save();

    // draw underground bar
    QPointF  BarTopLeft(PB_EXTRA_SPACE,PB_EXTRA_SPACE);
    QPointF  BarBottomRight(width()- PB_EXTRA_SPACE,height()-PB_EXTRA_SPACE);
    QRectF BarRect(BarTopLeft,BarBottomRight);

    painter->setPen(QColor(200,200,200));

    QLinearGradient BarGradient(BarRect.topLeft(),BarRect.bottomLeft());
    BarGradient.setColorAt(0.0,QColor(30,30,30));
    BarGradient.setColorAt(0.5,QColor(140,140,140));
    BarGradient.setColorAt(1.0,QColor(30,30,30));

//    BarGradient.setColorAt(0.0,QColor(250,250,250));
//    BarGradient.setColorAt(0.5,QColor(210,210,210));
//    BarGradient.setColorAt(1.0,QColor(250,250,250));
//

    painter->setBrush(BarGradient);
    painter->drawRoundedRect(BarRect,PB_RADIUS,PB_RADIUS);


    // draw animation bar
    if(m_bSuspending)
    {
        m_BarLength = width() * PB_BAR_WIDTH_FACTOR;
        QPointF MovingBarTopLeft(m_nCurrentXPos,PB_EXTRA_SPACE);
        QPointF MovingBarBottomRight(m_nCurrentXPos + m_BarLength,height() - PB_EXTRA_SPACE);
        QRectF MovingBarRect(MovingBarTopLeft,MovingBarBottomRight);

        QLinearGradient MovingBarGradient(MovingBarRect.topLeft(),MovingBarRect.bottomLeft());
        MovingBarGradient.setColorAt(0.0,QColor(250,250,250));
        MovingBarGradient.setColorAt(0.5,QColor(210,210,210));
        MovingBarGradient.setColorAt(1.0,QColor(250,250,250));

//        MovingBarGradient.setColorAt(0.0,QColor(30,30,30));
//        MovingBarGradient.setColorAt(0.5,QColor(140,140,140));
//        MovingBarGradient.setColorAt(1.0,QColor(30,30,30));

        painter->setBrush(MovingBarGradient);
        painter->drawRoundedRect(MovingBarRect,PB_RADIUS,PB_RADIUS);
    }else{
        int Length = m_nMax - m_nMin;
        qreal XDiff = (qreal)BarRect.width()/Length;

        qDebug() << __FUNCTION__ << m_nValue;
        QPointF BarTopLeft(PB_EXTRA_SPACE,PB_EXTRA_SPACE);
        QPointF BarBottomRight(XDiff * m_nValue,height() - PB_EXTRA_SPACE);
        QRectF Bar(BarTopLeft,BarBottomRight);

        QLinearGradient BarGradient(BarRect.topLeft(),BarRect.bottomLeft());
        BarGradient.setColorAt(0.0,QColor(250,250,250));
        BarGradient.setColorAt(0.5,QColor(210,210,210));
        BarGradient.setColorAt(1.0,QColor(250,250,250));

//        BarGradient.setColorAt(0.0,QColor(30,30,30));
//        BarGradient.setColorAt(0.5,QColor(140,140,140));
//        BarGradient.setColorAt(1.0,QColor(30,30,30));
//
        painter->setBrush(BarGradient);
        painter->drawRoundedRect(Bar,PB_RADIUS,PB_RADIUS);


    }

    painter->restore();
}

/*!
  public slot functions
*/
void ProgressBar::SetBackgroundColor(const QColor &clr)
{
    m_bgClr = clr;
    update();
}

void ProgressBar::SetValue(int value)
{
    if(value == m_nValue || m_bSuspending || value > m_nMax || value < m_nMin )
    {
        return ;
    }



    if(value > m_nValue)
    {
        m_bReverse = false;
    }else{
        m_bReverse = true;
    }

    m_nValue = value;
//    m_updateTimer->start();
    update();
}

void ProgressBar::StartSuspending()
{
    m_bSuspending = true;
    m_suspendingTimer->start();
}

void ProgressBar::StopSuspending()
{
    m_suspendingTimer->stop();
    m_bSuspending = false;
}

void ProgressBar::SetRange(int min, int max)
{
    m_nMin = min;
    m_nMax = max;
    update();
}

