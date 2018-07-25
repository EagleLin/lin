#include "protocolobject.h"
#include <QTimer>
#include <QEventLoop>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
ProtocolObject::ProtocolObject(QObject *parent) : QObject(parent)
{

}
void ProtocolObject::setHttpHeader(QString sRemoteUrl,QNetworkRequest &req,QByteArray &baContent,QString sBodyData)
{
    baContent = QString("body=%1").arg(urlEncode(sBodyData)).toUtf8();
    req.setUrl(QUrl(sRemoteUrl));
    req.setRawHeader("Accept-Charset", "utf8");
    req.setRawHeader("Accept", "json");

    //    QString sClientTag=QString("kmgate/%1/1/linux").arg(sAppVersion);
    //    QByteArray bClientTag=sClientTag.toAscii();
    //req.setRawHeader("User-Agent",bClientTag );
    req.setRawHeader("Content-Length", QString::number(baContent.length()).toUtf8());
    req.setRawHeader("content-type", "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentTypeHeader, "json");
    //    req.setRawHeader("sessionid", sSessionID.toUtf8());
    //    req.setRawHeader("companycode", sCompanyCode.toUtf8());
    //    req.setRawHeader("devicetag", sLocalDeviceID.toUtf8());
    //    req.setRawHeader("validcode", sValidateCode.toUtf8());

    //add extra http header if need; (2015-04-09)
    //    if (!slExtraHttpHeadData.isEmpty())
    //    {
    //        QString sFieldName,sFieldValue;
    //        for (int i=0;i<slExtraHttpHeadData.count();i++)
    //        {
    //            sFieldName="";
    //            sFieldValue="";

    //            if (!PUBFUN::STRINGLIST::GetListValue(&slExtraHttpHeadData,i,sFieldName,sFieldValue))
    //                continue;
    //            if (sFieldName.isEmpty() || sFieldValue.isEmpty())
    //                continue;
    //            if (slDefaultHttpHeadField.contains(sFieldName))  //这些特殊字段不处理;
    //                continue;
    //            req.setRawHeader(sFieldName.toUtf8(), sFieldValue.toUtf8());
    //        }
    //    }
}
/************************************************************************
 * 函数名称： urlEncode
 * 函数功能： url编码,对整串进行编码,收到之后必须进行urldecode才能使用
 * 参数说明：
            bOnlyEncodeSpecialChar //是否只对特殊字符进行编码(部分编码)
 * 作者 ：    levon
 * 最后修改：  2016-11-22
 ************************************************************************/
QString ProtocolObject::urlEncode(QString str,bool bOnlyEncodeSpecialChar)
{
    if (str.isEmpty())
    {
        return "";
    }
    else
    {
        if (bOnlyEncodeSpecialChar)
        {
            QString url=str;
            //修正反斜杠为斜杠
            url=url.replace("\\", "/");
            //使用长文本代替要保留字符串
            url=url.replace(":", "_.-colon.-_") ;
            url=url.replace("/", "_.-slash.-_");
            url=url.replace("\\", "_.-backslash.-_") ;
            url=url.replace(" ", "_.-blank.-_") ;
            url=url.replace("?", "_.-question.-_");
            url=url.replace("=", "_.-equal.-_") ;
            url=url.replace(";","_.-semicolon.-_");

            //进行编码
            url=urlEncode(url);

            url=url.replace("_.-colon.-_",":" );
            url=url.replace("_.-slash.-_","/");
            url=url.replace( "_.-backslash.-_","\\");
            url=url.replace( "_.-blank.-_","%20");
            url=url.replace( "_.-question.-_","?");
            url=url.replace("_.-equal.-_","=" ) ;
            url=url.replace("_.-semicolon.-_",";");
            return url;
        }
        else
        {
            QByteArray bb = QUrl::toPercentEncoding(str.toLatin1());
            return QString::fromLatin1(bb);
        }
    }
}

void ProtocolObject::postData(QString sRemoteUrl,QString sBodyData)
{
    QString sError;
    //2..待发送内容;
    QByteArray baContent;//待发送内容;
    QNetworkRequest req;//发送头;
    setHttpHeader(sRemoteUrl,req,baContent,sBodyData);

    //3..设置超时,
    QEventLoop eventLoop;
    QNetworkAccessManager *networkManager=new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QTimer  *tmrCommTimeOut=new QTimer();
    tmrCommTimeOut->setSingleShot(true);
    tmrCommTimeOut->setInterval(3*1000);
    connect(tmrCommTimeOut, SIGNAL(timeout()), &eventLoop, SLOT(quit()));

    //发送;
    QNetworkReply* reply= networkManager->post(req, baContent);
    tmrCommTimeOut->start();
    eventLoop.exec();
    slotWhenGetResponseDataFinish(reply);

}

QByteArray ProtocolObject::getResponseBody()
{
 return m_byteResponseBody;
}

void ProtocolObject::slotTimeOut()
{
    qDebug()<<"超时";
}

void ProtocolObject::slotWhenGetResponseDataFinish(QNetworkReply *networkReply)
{
    QString  sError="";
    if (networkReply==0)
    {
        sError=tr("无效的数据回应!");
        qDebug()<<sError;
        return;
    }
    if (networkReply->error()!=QNetworkReply::NoError)
    {
        sError=networkReply->errorString();
        qDebug()<<sError;
        return ;
    }

    //3..解析http协议头;
    QString sResponseFrom;
    if (networkReply->hasRawHeader(QByteArray("sessionid")))
        // sSessionID=QString(networkReply->rawHeader(QByteArray("sessionid")));

        if (networkReply->hasRawHeader(QByteArray("user-agent")))
            QString sResponseFrom=QString(networkReply->rawHeader(QByteArray("user-agent")));

    //先不验证来源;
    //            if (sResponseFrom!=REMOTESERVER_USERAGENT)
    //            {
    //                ok=false;
    //                sError=tr("不可识别的数据来源!");
    //            }
    //            else
    //            {
    qDebug()<<networkReply->bytesAvailable();
    QByteArray ba = networkReply->readAll();
    m_byteResponseBody=ba;
    qDebug()<<"返回"<<networkReply->errorString();
    paraseJson(ba);


}
void ProtocolObject::paraseJson(QByteArray ba){
    QJsonParseError jsonpe;
    QJsonDocument json = QJsonDocument::fromJson(ba, &jsonpe);
    if (jsonpe.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject obj = json.object();
            if (obj.contains("error"))
            {
                qDebug() << "error:" << obj["error"];
            }
            else
            {
                QJsonArray jarray = obj["invlist"].toArray();
                for (int row = 0; row < jarray.size(); row++)
                {
                    qDebug() << "====Row[" << row << "] Start===================";
                    QJsonObject jobj = jarray[row].toObject();
                    for (QJsonObject::Iterator it = jobj.begin();
                         it != jobj.end(); it++)
                    {
                        qDebug() << it.key() << " => " << it.value();
                    }
                }
            }
        }
        else
        {
            qDebug() << "error, shoud json object";
        }
    }
    else
    {
        qDebug()<< jsonpe.errorString();
    }


}
