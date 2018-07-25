#include "mainwidget.h"
#include "pubgui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
extern QString sWindowTitle;
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    initObject();
}

void MainWidget::initObject()
{
    //主布局;
    m_frmMain = new QFrame(this);
    m_glayoutMain = new QGridLayout(m_frmMain);
    m_glayoutMain->setContentsMargins(1,1,1,1);

    //banner栏;
    createBanner(sWindowTitle,
                 tr("通过邮票,可以对在线的邮政购物,进行快速的邮票抢购！"),
                 ":/res/stamptitle.png");
    m_btnLoadData=new QPushButton(this);
    m_btnLoadData->setText(tr("导入数据"));
    m_btnLogin = new QPushButton(this);
    m_btnLogin->setText("登陆");
    m_btnLoadData->setMaximumWidth(300);
    m_btnGrap = new QPushButton(this);
    m_btnGrap->setText(tr("抢购"));
    m_ldtGrapNum = new QLineEdit(this);
    m_ldtGrapNum->setMaximumWidth(200);
    m_ldtNetAddr=new QLineEdit(this);
    m_cbxNowAddr=new QComboBox(this);
    m_cbxNowAddr->setMaximumWidth(200);
    m_cbxNowAddr->addItem(tr("中国邮政网上营业厅"));
    m_tbWidget=new QTableWidget(this);
    m_tbWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tbWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tbWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //2. 刷新头
    QStringList slHeaderList;
    slHeaderList.clear();
    slHeaderList<<tr("账号")<<tr("密码")<<tr("接收手机")<<tr("验证码")
               <<tr("登陆状态")<<tr("下单状态");

    //3. 设置列表配置
    m_tbWidget->setColumnCount(6);
    m_tbWidget->setColumnWidth(0,150);
    m_tbWidget->setColumnWidth(1,150);
    m_tbWidget->setColumnWidth(2,120);
    m_tbWidget->setColumnWidth(3,120);
    m_tbWidget->setColumnWidth(4,140);
    m_tbWidget->setColumnWidth(5,90);
    m_tbWidget->setHorizontalHeaderLabels(slHeaderList);
    m_tbWidget->horizontalHeader()->setStretchLastSection(true);  //最后拖拉
    setMainLayout();

    connect(m_btnLoadData,SIGNAL(clicked()),this,SLOT(slotClickLoadData()));
}

void MainWidget::createBanner(QString title, QString description, QString iconresname)
{
    m_frmBanner = new QFrame(this);
    m_frmBanner->setFixedHeight(BANNER::WINDOW_HIGHT);

    m_glayoutBanner = new QGridLayout(m_frmBanner);
    m_glayoutBanner->setContentsMargins(8, 8, 8, 0);
    m_glayoutBanner->setSpacing(4);

    m_lblTitle = new QLabel(this);
    m_lblTitle->setText(title);
    m_lblTitle->setAlignment(Qt::AlignTop);
    PUBGUI::SetFont(m_lblTitle, BANNER::TITLE_FONT_SIZE, "", true);
    PUBGUI::SetFontColor(m_lblTitle, BANNER::TITLE_FONT_COLOR);

    m_lblTitleDescribtion = new QLabel(this);
    m_lblTitleDescribtion->setText(description);
    m_lblTitleDescribtion->setAlignment(Qt::AlignTop);
    m_lblTitleDescribtion->setWordWrap(true);
    PUBGUI::SetFont(m_lblTitleDescribtion, BANNER::TITLE_DESCRIPTION_FONT_SIZE);
    PUBGUI::SetFontColor(m_lblTitleDescribtion,BANNER::TITLE_DESCRIPTION_FONT_COLOR);

    m_lblIcon = new QLabel(this);
    m_lblIcon->setFixedSize(BANNER::ICON_SIZE);
    QPixmap pp(iconresname);
    pp = pp.scaled(BANNER::ICON_SIZE, Qt::KeepAspectRatioByExpanding);
    m_lblIcon->setPixmap(pp);
    m_lblIcon->installEventFilter(this);
}

void MainWidget::setMainLayout()
{
    //banner;
    m_glayoutBanner->addWidget(m_lblTitle,0,0);
    m_glayoutBanner->addWidget(m_lblTitleDescribtion,1,0);
    m_glayoutBanner->addWidget(m_lblIcon,0,1,3,1);
    m_frmBanner->setLayout(m_glayoutBanner);

    QHBoxLayout *layoutTopNetAddr = new QHBoxLayout();
    QLabel *lblNetAddr=new QLabel(this);
    lblNetAddr->setMaximumWidth(40);
    lblNetAddr->setText("网址:");
    layoutTopNetAddr->addWidget(lblNetAddr);
    layoutTopNetAddr->addWidget(m_ldtNetAddr);

    QHBoxLayout *layoutLoginNetAddr = new QHBoxLayout();
    QLabel *lblLoginNetAddr=new QLabel(this);
    lblLoginNetAddr->setText("网址:");
    lblLoginNetAddr->setMaximumWidth(40);
    layoutLoginNetAddr->addWidget(lblLoginNetAddr);
    layoutLoginNetAddr->addWidget(m_cbxNowAddr);
    layoutLoginNetAddr->addSpacing(400);
    layoutLoginNetAddr->addWidget(m_btnLogin);

    QHBoxLayout *layoutTop = new QHBoxLayout();
    QLabel *lblGrapNum=new QLabel(this);
    lblGrapNum->setMaximumWidth(40);
    lblGrapNum->setText(tr("数量:"));
    layoutTop->addWidget(lblGrapNum);
    layoutTop->addWidget(m_ldtGrapNum);
    layoutTop->addSpacing(400);
    layoutTop->addWidget(m_btnLoadData);
    layoutTop->addWidget(m_btnGrap);


    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutTopNetAddr);
    layoutMain->addLayout(layoutLoginNetAddr);
    layoutMain->addLayout(layoutTop);
    layoutMain->addWidget(m_tbWidget);
    //主布局;
    m_glayoutMain->addWidget(m_frmBanner);
    m_glayoutMain->addLayout(layoutMain,1,0);

    setLayout(m_glayoutMain);
}

void MainWidget::refreshTable(QList<srt_stampuserInfo> stampUsrInfoList)
{
     m_tbWidget->setRowCount(stampUsrInfoList.size());
    for (int i=0; i<stampUsrInfoList.size(); i++)
    {
        srt_stampuserInfo stampUsrInfo=stampUsrInfoList.value(i);
        QTableWidgetItem *item1=new QTableWidgetItem(stampUsrInfo.usrName);
        item1->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item2=new QTableWidgetItem(stampUsrInfo.usrPassword);
        item2->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item3=new QTableWidgetItem(stampUsrInfo.usrPhone);
        item3->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item4= new QTableWidgetItem(stampUsrInfo.usrCode);
        item4->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item5= new QTableWidgetItem(stampUsrInfo.usrLoginState);
        item5->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item6= new QTableWidgetItem(stampUsrInfo.usrOrderStatue);
        item6->setTextAlignment(Qt::AlignCenter);
        m_tbWidget->setItem(i, 0, item1);
        m_tbWidget->setItem(i, 1, item2);
        m_tbWidget->setItem(i, 2, item3);
        m_tbWidget->setItem(i, 3, item4);
        m_tbWidget->setItem(i, 4, item5);
        m_tbWidget->setItem(i,5,item6);

    }
}

void MainWidget::slotClickLoadData()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Config Files (*.xls)"));
    if(fileName.isEmpty())
        return;
    emit sigLoadUsrData(fileName);
    qDebug()<<fileName;
}


void MainWidget::showEvent(QShowEvent *)
{
    //强制刷新banner;
    if (!m_bFirstRun)
    {
        return;
    }
    m_bFirstRun = false;
    resizeEvent(0);
    PUBGUI::AlignCenter(this,true,true,true);
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    QLinearGradient linearGradient(10, 10, m_frmBanner->width(), m_frmBanner->height()-2);
    linearGradient.setColorAt(0.20, QColor(0,0,0) );
    linearGradient.setColorAt(0.82, QColor(5,26,54) );
    linearGradient.setColorAt(1.0, QColor(50,141,90));

    QPalette palette;
    palette.setBrush(m_frmBanner->backgroundRole(), QBrush(linearGradient));
    m_frmBanner->setPalette(palette);
    m_frmBanner->setAutoFillBackground(true);
}

void MainWidget::refreshTableWidget()
{
    //1.. 获取机顶盒信息和在线机顶盒ip
    //    QList<SRT_STB_INFO> srtStbInfoList;
    //    m_stbInfoObject->getAllStbInfo(srtStbInfoList);
    //    StbReadOnLineInfo stbOnlineInfo;
    //    QStringList slStbOnlineList = stbOnlineInfo.getAllStbList();

    //    //2. 刷新头
    //    QStringList slHeaderList;
    //    slHeaderList.clear();
    //    slHeaderList<<tr("账号")<<tr("密码")<<tr("接收手机")<<tr("验证码")
    //               <<tr("登陆状态")<<tr("下单状态");

    //    //3. 设置列表配置
    //    m_tbWidgetStb->setColumnCount(6);
    //    m_tbWidgetStb->setColumnWidth(0,130);
    //    m_tbWidgetStb->setColumnWidth(1,120);
    //    m_tbWidgetStb->setColumnWidth(2,120);
    //    m_tbWidgetStb->setColumnWidth(3,120);
    //    m_tbWidgetStb->setColumnWidth(4,160);
    //    m_tbWidgetStb->setColumnWidth(5,90);
    //    m_tbWidgetStb->setRowCount(srtStbInfoList.size());
    //    m_tbWidgetStb->setHorizontalHeaderLabels(slHeaderList);
    //    m_tbWidgetStb->horizontalHeader()->setStretchLastSection(true);  //最后拖拉
    //4. 设置列表信息
    //    for (int i=0; i<srtStbInfoList.size(); i++)
    //    {
    //        SRT_STB_INFO srtStbInfo=srtStbInfoList.at(i);
    //        QTableWidgetItem *item1=new QTableWidgetItem(srtStbInfo.stbip);
    //        item1->setTextAlignment(Qt::AlignCenter);
    //        QTableWidgetItem *item2=new QTableWidgetItem(srtStbInfo.roomname);
    //        item2->setTextAlignment(Qt::AlignCenter);
    //        QTableWidgetItem *item3=new QTableWidgetItem(srtStbInfo.version);
    //        item3->setTextAlignment(Qt::AlignCenter);
    //        QTableWidgetItem *item4= new QTableWidgetItem(srtStbInfo.productid);
    //        item4->setTextAlignment(Qt::AlignCenter);

    //        QTableWidgetItem *item5= new QTableWidgetItem(srtStbInfo.lastupdatetime);
    //        item5->setTextAlignment(Qt::AlignCenter);

    //        QLabel *lblItem6 = new QLabel();
    //        if(slStbOnlineList.contains(srtStbInfo.stbip))
    //            lblItem6->setPixmap(m_cPixmapOnLine);
    //        else
    //            lblItem6->setPixmap(m_cPixmapOffLine);
    //        lblItem6->setAlignment(Qt::AlignHCenter);
    //        m_tbWidgetStb->setItem(i, 0, item1);
    //        m_tbWidgetStb->setItem(i, 1, item2);
    //        m_tbWidgetStb->setItem(i, 2, item3);
    //        m_tbWidgetStb->setItem(i, 3, item4);
    //        m_tbWidgetStb->setItem(i, 4, item5);
    //        m_tbWidgetStb->setCellWidget(i,5,lblItem6);



    //    }
}

