#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QObject>
#include <QString>
#include <QToolButton>
#include <QDebug>
class ToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ToolButton(QToolButton *parent = 0);
    
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

signals:
    void sigChangeStatus(QString string);
public slots:
    void slotDelframe();
    
};

#endif // TOOLBUTTON_H
