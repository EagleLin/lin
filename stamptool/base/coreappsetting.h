#ifndef COREAPPSETTING_H
#define COREAPPSETTING_H
#include <QString>
#include <QCoreApplication>

class CoreAppSetting
{
public:
    CoreAppSetting();
    void setTextCodec();
    void setCoreAppBaseInfo(QCoreApplication *a,QString sProgramName,
                            QString sProgramTitle,QString sProgramVersion);
    void setAppName(QCoreApplication *a,QString name);
    void setAppVersion(QCoreApplication *a,QString version);
    void setTranslator(QCoreApplication *a);
    QString getProgramVersion(const QString sVer);
private:

    QString getCompiledDate_mmdd();
};

#endif // COREAPPSETTING_H
