#include "datahandle.h"

DataHandle::DataHandle(QObject *parent) :
    QObject(parent)
{
    m_groupLayout = new QGridLayout();
    m_toolIconList=new QKeyValueList(this);
    m_pathToName=new QKeyValueList(this);
    m_pathToDescription=new QKeyValueList(this);

    getToolList();
}

void DataHandle::getToolList()
{
    QString sLanguage;
    m_Language.getCurrentLanguage(sLanguage);

    QString sConfigFile=PUBFUN::APP::GetAppPath()+ "systoolbox.ini";//工具箱配置文件
    IniSettings myini(sConfigFile);
    foreach(QString pergroup,myini.childGroups())
    {
        QString sTemp=pergroup+"/name"+"_"+sLanguage;
        QString name = myini.value(sTemp).toString();
        QString path = myini.value(pergroup+"/path").toString();
        QString icon = myini.value(pergroup+"/icon").toString();
        QString description = myini.value(pergroup+"/description"+"_"+sLanguage).toString();

        if (!PUBFUN::FILES::FileExists(path))
            continue;

        m_toolIconList->append(path,icon);
        m_pathToName->append(path,name);
        m_pathToDescription->append(path,description);
         qDebug()<<name;
    }
}

void DataHandle::createGroupBox(FlowLayout *bodyFlowLayout,QList<ToolButton *> &toolbuttonlist)
{
    QStringList slToolPath;
    m_toolIconList->getKeyList(slToolPath);

    foreach (QString sToolPath,slToolPath)
    {
        QString sToolText,sToolDescription,sIcon;
        m_toolIconList->getValue(sToolPath,sIcon);
        m_pathToName->getValue(sToolPath,sToolText);
        m_pathToDescription->getValue(sToolPath,sToolDescription);

        ToolButton *toolbox = new ToolButton();
        toolbox->setAutoRaise(true);
        toolbox->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        QFontMetrics elidfont(toolbox->font());
        toolbox->setText(elidfont.elidedText(sToolText,Qt::ElideRight,96));
        toolbox->setToolTip(QString("【%1】\n%2").arg(sToolText).arg(sToolDescription));

        toolbox->setIcon(QIcon(sIcon));
        toolbox->setIconSize(QSize(56,56));
        toolbox->setAutoRaise(true);
        toolbox->setObjectName(sToolPath);
        toolbox->setAccessibleDescription(sToolDescription);
        toolbox->setFixedSize(QSize(100,100));
        toolbuttonlist.append(toolbox);
        bodyFlowLayout->addWidget(toolbox);
    }
}

void DataHandle::slotOpenApp()
{
    QProcess process;
    process.startDetached(this->sender()->objectName());
}
