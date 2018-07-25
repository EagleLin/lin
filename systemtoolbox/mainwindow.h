#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QSize>
#include <QHash>
#include <QGroupBox>
#include <QPushButton>

#include <QToolButton>
#include <QDebug>
#include <QIcon>
#include <QCloseEvent>
#include "platformvars.h"
#include "pubgui.h"
#include "datahandle.h"
#include "autohideobject.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void resizeEvent(QResizeEvent*);
    void CreateDataOject();
    void CreateBanner(QString title,QString description,QString iconresname);
    void CreateSepLine();
    void CreateBody();
    void CreateStatusBar();
    void Setconnect();
    void CreatAllObject();
    void SetMainWindow();
    void showEvent(QShowEvent * );
    void closeEvent(QCloseEvent * event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void init();
    void changeEvent(QEvent* event);

    void execShowAnimation();
    void execCloseAnimation();

private slots:
    void slotChangeStatus(QString string);
    void slotActiveApplication(const QString &mess);
    void slotResetWindowPos();
    void slotAfterShowAnimation();

private:
    AutoHideObject  *m_cAutoHideObject;
    DataHandle *m_dataHandle;
    bool        m_bFirstRun;
    QPoint m_pUILastDisplayPosition;
private:
    //顶部面板;
    QLabel *m_lblIcon;
    QLabel *m_lblTitle;
    QLabel *m_lblTitleDescribtion;
    QGridLayout *m_layoutBanner;
    QFrame *m_frmBanner;

    //分割栏
    QFrame *m_frmSepLine;

    //中部面板
    //QGridLayout *m_bodyQGridLayout;
    FlowLayout *m_bodyFlowLayout;
    QList<ToolButton *> m_toolbuttonlist;
    QWidget* m_widgetBody;
    QScrollArea* m_scrollArea;


    //底部面板
    QFrame *m_frmStatusBar;
    QGridLayout *m_statusLayout;
    QLabel *m_statusBar;

    QVBoxLayout *m_layoutClientArea;
    QFrame *m_frmClientArea;
    QTimer  *m_tmrSetWindowPos;
    QPoint  m_pStartPos;
    bool    m_bHasPlayCloseAnimation;
};

#endif // MAINWINDOW_H
