#include "coreappsetting.h"
#include <QTextCodec>
#include <QTranslator>
#include <QDir>
#include <fstream>
#include <iostream>
#include <QObject>
CoreAppSetting::CoreAppSetting()
{

}


void CoreAppSetting::setTextCodec()
{
  //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
  //  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
}

void CoreAppSetting::setTranslator(QCoreApplication *a)
{
    static QTranslator qtTranslator2;
    qtTranslator2.load("qt_zh_CN.qm");
     a->installTranslator(&qtTranslator2);


}

void CoreAppSetting::setAppVersion(QCoreApplication *a,QString version)
{
    a->setApplicationVersion(getProgramVersion(version));
}

void CoreAppSetting::setAppName(QCoreApplication *a,QString name)
{
    a->setApplicationName(name);
}


QString CoreAppSetting::getCompiledDate_mmdd()
{
    static char _buf[5] = {0};
    if(_buf[0] == 0)
    {
        static const char * _month[] =
        {
            "Jan", "Feb", "Mar", "Apr", "May", "Jun",
            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
        };
        const char * _date = __DATE__;
        //dd
        memcpy(_buf+2, _date + 4, 2);
        if(_buf[2]==' ')
        {
            _buf[2] = '0';
        }
        //mm
        int month = 0;
        for(int i = 0; i < 12; i++)
        {
            if(memcmp(_month[i], _date, 3) == 0)
            {
                month = i+1;
                break;
            }
        }
        _buf[0] = month / 10 % 10 + '0';
        _buf[1] = month % 10 + '0';
    }
    return QString(_buf);
}

QString CoreAppSetting::getProgramVersion(const QString sVer)
{
    return QString("Ver%1 Build%2").arg(sVer).arg(getCompiledDate_mmdd());
}


QString IncludeSlash(QString APath)
{
    if (APath=="")
        return "";

    QChar lastchar=APath[APath.length()-1];
    if (lastchar!=QDir::separator())
        return APath+QDir::separator();
    else
        return APath;
}

QString GetAppPath()
{
    return IncludeSlash(QCoreApplication::applicationDirPath());
}

void CoreAppSetting::setCoreAppBaseInfo(QCoreApplication *a,QString sProgramName,
                                        QString sProgramTitle,QString sProgramVersion)
{

    setTextCodec();
    setTranslator(a);
    //registerAppVersion(sProgramName, sProgramTitle, sProgramVersion);
    setAppVersion(a,sProgramVersion);
    setAppName(a,sProgramName);

}
