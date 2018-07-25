#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "pubfun.h"
namespace BANNER
{
const int    WINDOW_HIGHT = 85;                     //banner的高度
const int    TITLE_FONT_SIZE = 13;                  //标题字体大小
const QString TITLE_FONT_COLOR ="yellow";           //标题颜色
const int    TITLE_DESCRIPTION_FONT_SIZE = 10;      //描述字体大小;
const QString TITLE_DESCRIPTION_FONT_COLOR ="white"; //描述字体颜色
const QSize  ICON_SIZE=QSize(56,56);                //图标大小
}

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void initObject();
    void createBanner(QString title, QString description, QString iconresname);
    void setMainLayout();
    void refreshTable(QList<srt_stampuserInfo> stampUsrInfoList);
signals:
    void sigLoadUsrData(QString sFilePath);
public slots:
    void slotClickLoadData();
private:
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);
    void refreshTableWidget();
private:
    //定义ui
    //=====================================================
    //顶部面板;
    QFrame      *m_frmBanner;
    QGridLayout *m_glayoutBanner;

    QLabel      *m_lblIcon;
    QLabel      *m_lblTitle;
    QLabel      *m_lblTitleDescribtion;
    //主体布局
    QFrame      *m_frmMain;
    QGridLayout *m_glayoutMain;
    bool m_bFirstRun;

    QPushButton *m_btnLoadData;
    QPushButton *m_btnLogin;
    QPushButton *m_btnGrap;
    QLineEdit   *m_ldtNetAddr;
    QLineEdit   *m_ldtGrapNum;
    QComboBox   *m_cbxNowAddr;
    QTableWidget *m_tbWidget;

};

#endif // MAINWIDGET_H
