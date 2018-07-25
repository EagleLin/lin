#ifndef PROTOCOLOBJECT_H
#define PROTOCOLOBJECT_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
class ProtocolObject : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolObject(QObject *parent = 0);
    void setHttpHeader(QString sRemoteUrl,QNetworkRequest &req,QByteArray &baContent,QString sBodyData);
    QString urlEncode(QString str,bool bOnlyEncodeSpecialChar=false);
    void postData(QString sRemoteUrl,QString sBodyData);
    QByteArray getResponseBody();
private:
    void paraseJson(QByteArray ba);
signals:

public slots:
    void slotTimeOut();
    void slotWhenGetResponseDataFinish(QNetworkReply *networkReply);
private:
    QByteArray m_byteResponseBody;
};

#endif // PROTOCOLOBJECT_H
