#ifndef AUTOHIDEOBJECT_H
#define AUTOHIDEOBJECT_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QTimer>

class AutoHideObject : public QObject
{
    Q_OBJECT
public:
    explicit AutoHideObject(QObject *parent = 0);
    void setAutoHideWidget(QWidget *wgt);

    void whenMouseLeaveWindow();
    void whenMouseEnterWindow();
    void movetoRightSide(int iTop);
signals:
    
private slots:
    void slotAutoHideWindow();

private:
    void init();
    bool isInHideMode();
    bool isNeedAutoHide();
    void showWidget();
    void hideWidget();
private:
    QWidget* m_wDestWidget;
    QTimer* m_tmrDelayHide;
    int m_iDesktopWidth;
    int m_iDesktopHeight;

    int m_iDestWidgetWidth;
    int m_iDestWidgetHeight;
    
};

#endif // AUTOHIDEOBJECT_H
