#include "appsetting.h"
#include <QTextCodec>
#include <QTranslator>
#include <QDir>
#include <fstream>
#include <iostream>
#include <windows.h>
AppSetting::AppSetting():CoreAppSetting()
{
}

void AppSetting::setNoMaxmize(QWidget *mainwindow,bool allowminimize)
{
    Qt::WindowFlags flags;
    if (allowminimize)
        flags=Qt::Window;
    else
        flags=Qt::Dialog;

    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowMinimizeButtonHint;
    mainwindow->setWindowFlags(flags);
}

void AppSetting::setWindowIcon(QWidget *mainwindow,QIcon icon)
{
    mainwindow->setWindowIcon(icon);
}

void AppSetting::setFixedSize(QWidget *mainwindow,int width,int height)
{
    if (mainwindow==0)
        return;
    mainwindow->setFixedSize(width,height);
}

void AppSetting::setDefaultSize(QWidget *mainwindow,int width,int height)
{
    if (mainwindow==0)
        return;
    mainwindow->resize(width,height);
}

bool AppSetting::isFileExists(QString filepath)
{
    if (filepath=="")
        return false;

    QFileInfo qf(filepath);
    bool ok=qf.exists();
    if (ok)
        ok=qf.isFile();

    return ok;
}

/************************************************************************
 * 函数名称： setAppDefaultFont
 * 函数功能： 设置应用程序默认字体，可从统一配置文件加载；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2014-03-25
 ************************************************************************/
void AppSetting::setAppDefaultFont(QApplication *app)
{
    int iDefaultFontSize=10;
    QString sConfigFile="/evideoktv/bin/appinterface.cfg";
    if (isFileExists(sConfigFile))
    {
//        IniSettings *myIni=new IniSettings(sConfigFile);
//        iDefaultFontSize=myIni->value("interface/defaultfontsize",iDefaultFontSize).toInt();
//        delete myIni;
    }

    //
    QFont font  = app->font();
    font.setPointSize(iDefaultFontSize);
    app->setFont(font);
}

/************************************************************************
 * 函数名称： setAppTitle
 * 函数功能： 设置应用程序统一标题格式
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2014-03-25
 ************************************************************************/
void AppSetting::setAppTitle(QWidget *window,QString title, QString version)
{
    if (window>0)
    {
        if (version.isEmpty())
            window->setWindowTitle(title);
        else
            window->setWindowTitle(QString("%1 (%2)")
                                   .arg(title)
                                   .arg(getProgramVersion(version)));
    }
}

void AppSetting::setAppBaseInfo(QApplication *a,QString sProgramName,QString sProgramTitle,QString sProgramVersion)
{
    setAppDefaultFont(a);
    //gui程序不需要守护
    setCoreAppBaseInfo(a,sProgramName,sProgramTitle,sProgramVersion);
}

void AppSetting::setMainWindowBaseInfo(QWidget *mainwindow,QString sProgramTitle,QString sProgramVersion,bool bAllowMaximize,QIcon mainwindowIcon)
{
    setAppTitle(mainwindow,sProgramTitle,sProgramVersion);
    setWindowIcon(mainwindow,mainwindowIcon);
    setNoMaxmize(mainwindow,bAllowMaximize);
}

bool AppSetting::checkOnly()
{
    HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"fortest_abc123" );
       //  检查错误代码
       if  (GetLastError()  ==  ERROR_ALREADY_EXISTS)  {
         //  如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);
        m_hMutex  =  NULL;
         //  程序退出
         return  false;
       }
       else
           return true;
}
