#include "mainwindow.h"
#include <QPropertyAnimation>
#include <QDesktopWidget>

extern QString g_sWindowTitle;
QSize DefaultWindowSize(250,600);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    CreatAllObject();
    Setconnect();
    SetMainWindow();
}

MainWindow::~MainWindow()
{
    for(int i=m_toolbuttonlist.count()-1;i>=0;i--)
    {
        delete(m_toolbuttonlist.value(i));
    }
}


void MainWindow::init()
{
    m_bFirstRun=true;
    m_bHasPlayCloseAnimation=false;
    m_tmrSetWindowPos=new QTimer(this);
    m_tmrSetWindowPos->setInterval(100);
    connect(m_tmrSetWindowPos,SIGNAL(timeout()),this,SLOT(slotResetWindowPos()));
}


//对象创建初始化
void MainWindow::CreatAllObject()
{
    m_cAutoHideObject=new  AutoHideObject(this);

    CreateDataOject();
    //头部创建
    CreateBanner(g_sWindowTitle,
                 tr("系统工具箱集成了常用的系统扩展和维护工具,通过这些工具,可以对系统进行更高效的管理。"),
                 ":/image/gatewaytool.png");
    CreateSepLine();
    //中部创建
    CreateBody();
    //底部创建
    // CreateStatusBar();
}

void MainWindow::CreateDataOject()
{
    m_dataHandle =  new DataHandle(this);
}


void MainWindow::CreateBanner(QString title, QString description, QString iconresname)
{
    m_frmBanner = new QFrame(this);
    m_frmBanner->setFixedHeight(PLATFORMVARS::INTERFACE::BANNER::WINDOW_HIGHT);

    m_layoutBanner = new QGridLayout(m_frmBanner);
    m_layoutBanner->setContentsMargins(0, 0, 8, 0);
    m_layoutBanner->setSpacing(4);

    //居上黄色字体10
    m_lblTitle = new QLabel(this);
    m_lblTitle->setText(title);
    m_lblTitle->setAlignment(Qt::AlignTop);
    PUBGUI::SetFont(m_lblTitle, PLATFORMVARS::INTERFACE::BANNER::TITLE_FONT_SIZE, "", true);
    PUBGUI::SetFontColor(m_lblTitle, PLATFORMVARS::INTERFACE::BANNER::TITLE_FONT_COLOR);

    //居上白字可换行10
    m_lblTitleDescribtion = new QLabel(this);
    m_lblTitleDescribtion->setText(description);
    m_lblTitleDescribtion->setAlignment(Qt::AlignTop);
    m_lblTitleDescribtion->setWordWrap(true);
    PUBGUI::SetFont(m_lblTitleDescribtion, PLATFORMVARS::INTERFACE::BANNER::TITLE_DESCRIPTION_FONT_SIZE);
    PUBGUI::SetFontColor(m_lblTitleDescribtion,PLATFORMVARS::INTERFACE::BANNER::TITLE_DESCRIPTION_FONT_COLOR);

    QPixmap pp(iconresname);
    pp = pp.scaled(PLATFORMVARS::INTERFACE::BANNER::ICON_SIZE, Qt::KeepAspectRatioByExpanding);
    m_lblIcon = new QLabel(this);
    m_lblIcon->setFixedSize(PLATFORMVARS::INTERFACE::BANNER::ICON_SIZE);
    m_lblIcon->setPixmap(pp);

    m_layoutBanner->addWidget(m_lblTitle, 0, 0);
    m_layoutBanner->addWidget(m_lblTitleDescribtion, 1, 0);
    m_layoutBanner->addWidget(m_lblIcon, 0, 1, 3, 1);
    m_frmBanner->setLayout(m_layoutBanner);
}

void MainWindow::CreateSepLine()
{
    m_frmSepLine = new QFrame(this);
    m_frmSepLine->setFrameStyle(QFrame::HLine);
}

void MainWindow::CreateBody()
{
    m_bodyFlowLayout = new FlowLayout();
    m_dataHandle->createGroupBox(m_bodyFlowLayout,m_toolbuttonlist);

    m_widgetBody = new QWidget(this);
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widgetBody->setLayout(m_bodyFlowLayout);
    m_scrollArea->setWidget(m_widgetBody);
    m_scrollArea->setWidgetResizable(true);

}

void MainWindow::CreateStatusBar()
{
    m_frmStatusBar = new QFrame(this);
    m_frmStatusBar->setFixedHeight(35);

    m_statusLayout = new QGridLayout(m_frmStatusBar);
    m_statusLayout->setContentsMargins(0,0,8,0);

    m_statusBar = new QLabel(this);
    m_statusBar->clear();
    m_statusLayout->addWidget(m_statusBar);
}


//总布局
void MainWindow::SetMainWindow()
{
    m_layoutClientArea = new QVBoxLayout();
    m_layoutClientArea->setContentsMargins(1, 0, 1, 0);
    m_layoutClientArea->setSpacing(0);
    m_frmClientArea = new QFrame(this);

    //头部布局
    m_frmBanner->setVisible(false);
    m_layoutClientArea->addWidget(m_frmBanner);
    //分割栏
    m_layoutClientArea->addWidget(m_frmSepLine);
    //中部布局
    m_layoutClientArea->addWidget(m_scrollArea);
    //底部布局
    //m_layoutClientArea->addWidget(m_frmStatusBar);
    //总布局
    m_frmClientArea->setLayout(m_layoutClientArea);

    this->layout()->setContentsMargins(0,0,4,4);
    this->setCentralWidget(m_frmClientArea);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    //    QLinearGradient linearGradient(10, 10, m_frmBanner->width(), m_frmBanner->height() - 2);
    //    linearGradient.setColorAt(0.20, QColor(0, 0, 0));
    //    linearGradient.setColorAt(0.82, QColor(5, 26, 54));
    //    linearGradient.setColorAt(1.0, QColor(50, 141, 90));

    //    QPalette palette;
    //    palette.setBrush(m_frmBanner->backgroundRole(), QBrush(linearGradient));
    //    m_frmBanner->setPalette(palette);
    //    m_frmBanner->setAutoFillBackground(true);
}

void MainWindow::Setconnect()
{
    foreach(ToolButton *tmp,m_toolbuttonlist)
    {
        connect(tmp,SIGNAL(clicked()),m_dataHandle,SLOT(slotOpenApp()));
        connect(tmp,SIGNAL(sigChangeStatus(QString)),this,SLOT(slotChangeStatus(QString)));

    }
}

void MainWindow::slotChangeStatus(QString string)
{
    // m_statusBar->setText(string);
}

void MainWindow::showEvent(QShowEvent * )
{
    if (m_bFirstRun)
    {
        //m_cAutoHideObject->setAutoHideWidget(this);
        //m_cAutoHideObject->movetoRightSide(50);
        //m_cAutoHideObject->whenMouseLeaveWindow();

        execShowAnimation();
    }
    else
    {

    }
    m_bFirstRun=false;
}

void MainWindow::closeEvent(QCloseEvent *event )
{
    qDebug()<<"close";

    if (!m_bHasPlayCloseAnimation)
    {
        execCloseAnimation();
        m_bHasPlayCloseAnimation=true;
        event->ignore();
    }
}


void MainWindow::slotActiveApplication(const QString &mess)
{
    m_pUILastDisplayPosition=this->frameGeometry().topLeft();
    this->setUpdatesEnabled(false);
    this->setFixedSize(0,0);
    this->hide();
    this->showNormal();
    m_tmrSetWindowPos->start();
}

void MainWindow::slotResetWindowPos()
{
    this->setFixedSize(DefaultWindowSize);
    this->setUpdatesEnabled(false);
    this->move(m_pUILastDisplayPosition);
    this->setUpdatesEnabled(true);
}

void MainWindow::leaveEvent(QEvent *event)
{
    // m_cAutoHideObject->whenMouseLeaveWindow();
}

void MainWindow::enterEvent(QEvent *event)
{
    //m_cAutoHideObject->whenMouseEnterWindow();
}


void MainWindow::changeEvent(QEvent* event)
{
    if(event->type()==QEvent::WindowStateChange)
    {
        if(windowState() & Qt::WindowMinimized)
        {
            m_pUILastDisplayPosition=  this->frameGeometry().topLeft();
        }
        QMainWindow::changeEvent(event);
    }
}

void MainWindow::execShowAnimation()
{
    int iDesktopWidth,iDesktopHeight;
    PUBGUI::GetScreenSize(iDesktopWidth,iDesktopHeight);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(400);
    connect(animation,SIGNAL(finished()),this,SLOT(slotAfterShowAnimation()));
    m_pStartPos=QCursor::pos();
    QPoint pEndPos=QPoint(iDesktopWidth-DefaultWindowSize.width(),(iDesktopHeight-DefaultWindowSize.height())/2);
    animation->setStartValue(QRect(m_pStartPos.x() , m_pStartPos.y() ,
                                   10, 10));
    animation->setEndValue(QRect(pEndPos.x(),
                                 pEndPos.y(),
                                 DefaultWindowSize.width(),DefaultWindowSize.height()));

    animation->start();
}


void MainWindow::slotAfterShowAnimation()
{
    setFixedSize(DefaultWindowSize);
}

void MainWindow::execCloseAnimation()
{
    int iDesktopWidth,iDesktopHeight;
    PUBGUI::GetScreenSize(iDesktopWidth,iDesktopHeight);
    this->setMinimumSize(0,0);
    this->setMaximumSize(iDesktopWidth,iDesktopHeight);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(400);

    QPoint pEndPos=m_pStartPos;
    m_pStartPos=this->pos();
    animation->setStartValue(QRect(m_pStartPos.x() , m_pStartPos.y() ,
                                   DefaultWindowSize.width(), DefaultWindowSize.height()));
    animation->setEndValue(QRect(pEndPos.x(),
                                 pEndPos.y(),
                                 1,1));
    connect(animation,SIGNAL(finished()),this,SLOT(close()));
    animation->start();
}
