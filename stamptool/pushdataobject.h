#ifndef PUSHDATAOBJECT_H
#define PUSHDATAOBJECT_H

#include <QObject>

class pushDataObject : public QObject
{
    Q_OBJECT
public:
    explicit pushDataObject(QObject *parent = 0);
    void test();
    void getGoodDeatail();
private:
    void paraseGoodDetail();
signals:

public slots:
};

#endif // PUSHDATAOBJECT_H
