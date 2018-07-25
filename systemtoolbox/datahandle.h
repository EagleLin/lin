#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include <QObject>
#include <QMap>
#include <QSettings>
#include <QStringList>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QList>
#include <QDebug>
#include <QToolButton>
#include <QScrollArea>
#include <QLinearGradient>
#include <QPalette>
#include <QProcess>
#include <QFontMetrics>
#include "pubfun.h"
#include "toolbutton.h"
#include "flowlayout.h"
#include "multilanguageobject.h"
#include "qkeyvaluelist.h"
#include "inisettings.h"

#define DEFAULT_COLUMN 8
class DataHandle : public QObject
{
    Q_OBJECT
public:
    explicit DataHandle(QObject *parent = 0);
    QSettings *m_qsetting;
    QKeyValueList  *m_toolIconList;
    QKeyValueList  *m_pathToName;
    QKeyValueList  *m_pathToDescription;
    QGridLayout* m_groupLayout;
    MultiLanguageObject m_Language;
    void getToolList();
    void createGroupBox(FlowLayout *bodyFlowLayout,QList<ToolButton *> &toolbuttonlist);

private:

signals:
    
public slots:
    void slotOpenApp();
    
};

#endif // DATAHANDLE_H
