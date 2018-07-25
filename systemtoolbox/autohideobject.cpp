#include "autohideobject.h"
#include "pubgui.h"
#include <QDebug>
#include "pubfun.h"

const int CONST_WindowWidthWhenHide=2; //隐藏时窗体的宽度;
const int CONST_AutoHideAfterLeave=3000; //离开窗体多久后自动隐藏;


AutoHideObject::AutoHideObject(QObject *parent) :
    QObject(parent)
{
    init();
}

void AutoHideObject::init()
{
    m_wDestWidget=0;
    m_iDestWidgetWidth=0;
    m_iDestWidgetHeight=0;
    PUBGUI::GetScreenSize(m_iDesktopWidth,m_iDesktopHeight);

    m_tmrDelayHide=new  QTimer(this);
    m_tmrDelayHide->setInterval(CONST_AutoHideAfterLeave);
    connect(m_tmrDelayHide,SIGNAL(timeout()),this,SLOT(slotAutoHideWindow()));

}

void AutoHideObject::setAutoHideWidget(QWidget *wgt)
{
    if (wgt==0)
        return;
    m_wDestWidget=wgt;
    m_iDestWidgetWidth=m_wDestWidget->width();
    m_iDestWidgetHeight=m_wDestWidget->height();
}

bool AutoHideObject::isInHideMode()
{
    if (m_wDestWidget==0)
        return false;
    return  m_wDestWidget->width()==CONST_WindowWidthWhenHide;
}

bool AutoHideObject::isNeedAutoHide()
{
    if (m_wDestWidget==0)
        return false;

    int iTemp=qAbs(qRound(m_wDestWidget->x()+m_wDestWidget->width()-m_iDesktopWidth));
    return  qAbs(qRound(m_wDestWidget->x()+m_wDestWidget->width()-m_iDesktopWidth))<=20; //处于边缘(设定一定的容差);
}

void AutoHideObject::hideWidget()
{
    if (m_wDestWidget==0)
        return;
    if (isInHideMode())
        return;

    //backup
    m_iDestWidgetWidth=m_wDestWidget->width();
    m_iDestWidgetHeight=m_wDestWidget->height();

    m_wDestWidget->setFixedSize(CONST_WindowWidthWhenHide ,m_iDestWidgetHeight /2 );
    m_wDestWidget->move(m_iDesktopWidth-CONST_WindowWidthWhenHide, m_wDestWidget->y());

}

void AutoHideObject::showWidget()
{
    if (m_wDestWidget==0)
        return;

    m_wDestWidget->move(m_iDesktopWidth-m_iDestWidgetWidth, m_wDestWidget->y());
    m_wDestWidget->setFixedSize(m_iDestWidgetWidth ,m_iDestWidgetHeight);
}

void AutoHideObject::slotAutoHideWindow()
{
    m_tmrDelayHide->stop();
    hideWidget();
}

void AutoHideObject::whenMouseLeaveWindow()
{
    if (!isNeedAutoHide())
        return;

    m_tmrDelayHide->stop();
    m_tmrDelayHide->start();
}

void AutoHideObject::whenMouseEnterWindow()
{
    m_tmrDelayHide->stop();
    if (!isInHideMode())
        //    if (!isNeedAutoHide() )
        return;

    showWidget();
}

void AutoHideObject::movetoRightSide(int iTop)
{
    if (m_wDestWidget==0)
        return;

    m_wDestWidget->move(m_wDestWidget->x(),iTop);
    m_tmrDelayHide->stop();
    showWidget();
}
