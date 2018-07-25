#include "pushdataobject.h"
#include "protocolobject.h"
#include <QJsonObject>
#include <QDomDocument>
#include <QWebView>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QFile>
const QString g_sGetUserInfo="http://jiyou.retail.11185.cn//retail/JSONGetUserInfoByUserId.html";
const QString g_sGetGoodDetail="http://jiyou.11185.cn/retail/ticketDetail_78557.html?mainType=1005";
const QString g_sGetuserMember="http://jiyou.retail.11185.cn/JSONPmemtitleaciton.html?jsoncallback=success_jsonpCallback&_1529983035419=";
pushDataObject::pushDataObject(QObject *parent) : QObject(parent)
{

}

void pushDataObject::test()
{
    ProtocolObject protocalObject;

    protocalObject.postData(g_sGetGoodDetail,"");
    // protocalObject.postData(g_sGetUserInfo,"");
}

void pushDataObject::getGoodDeatail()
{
    QJsonObject jsonObject;
    ProtocolObject protocalObject;
    protocalObject.postData(g_sGetGoodDetail,"");
    QString sBody= protocalObject.getResponseBody();
    QDomDocument doc;
    bool ret= doc.setContent(sBody);
    QDomElement  dataElement =  doc.firstChildElement("script");
    while(!dataElement.isNull())
    {
        QString tag_name = dataElement.tagName();
        QString tag_value = dataElement.text();
        qDebug()<<tag_name<<tag_value;
        dataElement = dataElement.nextSiblingElement("script");
    }
    //dataElement.toText().data();

    QFile file("dd.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
    {
        QTextStream out(&file);

        out << sBody << endl;

        file.close();
    }

}

void pushDataObject::paraseGoodDetail()
{
    QDomDocument doc;
    //       if(!doc.setContent(&file, false))
    //       {
    //           return -1;
    //       }

    //       QDomElement root = doc.documentElement();
    //       parseElement(root);

}

