#ifndef APPSETTING_H
#define APPSETTING_H
#include "coreappsetting.h"
#include <QApplication>
#include <QWidget>
#include <QIcon>
class AppSetting : public CoreAppSetting
{
public:
    AppSetting();
    bool checkOnly();
    //设置应用程序信息
      void setAppBaseInfo(QApplication *a,QString sProgramName,QString sProgramTitle,QString sProgramVersion);

      //设置主窗体信息
      void setMainWindowBaseInfo(QWidget *mainwindow,QString sProgramTitle,QString sProgramVersion,bool bAllowMaximize,QIcon mainwindowIcon);

      void setNoMaxmize(QWidget *mainwindow, bool allowminimize=true);
      void setWindowIcon(QWidget *mainwindow,QIcon icon);
      void setFixedSize(QWidget *mainwindow,int width,int height);
      void setDefaultSize(QWidget *mainwindow,int width,int height);
      void setAppDefaultFont(QApplication *app);
      void setAppTitle(QWidget *window,QString title, QString version);

private:
    bool isFileExists(QString filepath);
};

#endif // APPSETTING_H
