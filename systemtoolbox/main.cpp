#include <QtGui/QApplication>
#include <QTextCodec>
#include "pubfun.h"
#include "mainwindow.h"
#include "appsetting.h"
#include "qtsingleapplication.h"
#include "pubname.h"
QString g_sProgramVersion = "2.61";
QString g_sProgramName    = "systemtoolbox";
QString g_sWindowTitle    ;

int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    if (a.isRunning())
    {
        a.sendMessage("need show app:"+g_sProgramName);
        return EXIT_SUCCESS;
    }
    else
    {
        AppSetting appsetting;
        appsetting.setTextCodec();
        appsetting.setAppName(&a,g_sProgramName);
        appsetting.setAppVersion(&a,appsetting.getProgramVersion(g_sProgramVersion));
        appsetting.initLanguage(&a);
        appsetting.setTranslator(&a);
        g_sWindowTitle = PUBNAME::GATEWAYPART::GATEWAYTOOL::getSystemBoxTitle();
        appsetting.setAppDefaultFont(&a);
        appsetting.registerAppVersion(g_sProgramName, g_sWindowTitle, g_sProgramVersion);


        MainWindow w;
        appsetting.setAppTitle(&w,g_sWindowTitle,"");
        appsetting.setWindowIcon(&w,QIcon(":image/gatewaytool.png"));

        QObject::connect(&a,SIGNAL(messageReceived(const QString &)),&w,SLOT(slotActiveApplication(const QString &)));
        w.show();
        return a.exec();
    }
}
