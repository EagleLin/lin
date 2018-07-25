#ifndef PUBFUN_H
#define PUBFUN_H
#include <QString>
struct srt_stampuserInfo{
    QString usrName;
    QString usrPassword;
    QString usrPhone;
    QString usrCode;
    bool bUsrLoginState;
    QString usrLoginState;
    QString usrOrderStatue;
    int usrOrderNum;
    void clear(){
        usrName.clear();
        usrPassword.clear();
        usrPhone.clear();
        usrCode.clear();
        bUsrLoginState=false;
        usrLoginState="未登录";
        usrOrderStatue="未下单";
        usrOrderNum=0;
    }
};

class PubFun
{
public:
    PubFun();
};

#endif // PUBFUN_H
