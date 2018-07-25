#include "mainwindow.h"
#include <QApplication>
#include "singleApplication/qsingleapplication.h"
#include "appsetting.h"
QString sProgramVersion = "2.60-alpha1";
QString sProgramName    = "gateway";
QString sWindowTitle   ="";
int main(int argc, char *argv[])
{
    QSingleApplication a(argc, argv);
    AppSetting appsetting;
    if(a.isRunning())
        return 0;
    appsetting.setTextCodec();
    //    sWindowTitle = QObject::tr("测试");
    //    appsetting.setAppBaseInfo(&a,sProgramName,sWindowTitle,sProgramVersion);
    MainWindow w;
    sWindowTitle=QObject::tr("邮件抢购工具");
    appsetting.setMainWindowBaseInfo(&w,sWindowTitle,sProgramVersion,true,QIcon(":/res/stamptitle.png"));
    appsetting.setFixedSize(&w,1200,800);
    w.show();
    return a.exec();
}
