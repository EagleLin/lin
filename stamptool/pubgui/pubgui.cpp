/*########################################################################
 # 单元名称： pubgui
 # 单元说明： 通用gui 函数单元
 # 系统说明： （锋云系统）
 # 作者 ：    Levon
 # 修改记录：
             1. 2010-11-20 创建；
             2. 2014-04-11 整理,使用命名空间,避免冲突
########################################################################*/

#include "pubgui.h"
#include <QAbstractButton>


namespace PUBGUI {

/************************************************************************
 * 函数名称： Information
 * 函数功能： 提示对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void Information(QString mess,QString title,QWidget *parentWindow)
{
    QMessageBox::information(parentWindow, title,mess,QObject::tr("确定(&O)"));
}

void Information(QString mess,QWidget *parentWindow)
{
    Information(mess,QObject::tr("提示"),parentWindow);
}

/************************************************************************
 * 函数名称： Error
 * 函数功能： 错误对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void ErrorMsg(QString mess,QString title,QWidget *parentWindow)
{
    QMessageBox::critical(parentWindow, title,mess,QObject::tr("确定(&O)"));
}

void ErrorMsg(QString mess,QWidget *parentWindow)
{
    ErrorMsg(mess,QObject::tr("错误"),parentWindow);
}

/************************************************************************
 * 函数名称： Question
 * 函数功能： 询问对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool Question(QString mess,QString title,QWidget *parentWindow)
{
    if (QMessageBox::question(parentWindow, title,mess,QObject::tr("是(&Y)"),QObject::tr("否(&N)"))==0)
        return true;
    else
        return false;

}

bool Question(QString mess,QWidget *parentWindow)
{
    return Question(mess,QObject::tr("系统询问"),parentWindow);
}

int QuestionYNC(QString mess,QString title,QWidget *parentWindow)
{
    return QMessageBox::question(parentWindow,title,mess,QObject::tr("是(&Y)"),QObject::tr("否(&N)"),QObject::tr("取消"));
}

/************************************************************************
 * 函数名称： Warning
 * 函数功能： 警告对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool Warning(QString mess,QString title,QWidget *parentWindow)
{
    if (QMessageBox::warning(parentWindow,title,mess ,QObject::tr("是(&Y)"),QObject::tr("否(&N)"))==0)
        return true;
    else
        return false;

}

bool Warning(QString mess,QWidget *parentWindow)
{
    return Warning(mess,QObject::tr("警告"),parentWindow);
}

QString Warning(QString mess, QStringList slButtonInfoList, QString title, QWidget *parentWindow)
{
    QMessageBox qMessBox(QMessageBox::Warning, title, mess, QMessageBox::NoButton, parentWindow);

    foreach (QString sButtonInfo, slButtonInfoList) {
        qMessBox.addButton(sButtonInfo, QMessageBox::AcceptRole);
    }

    qMessBox.exec();

    QAbstractButton* clickedButton = qMessBox.clickedButton();
    return clickedButton->text();
}

/************************************************************************
 * 函数名称： InputText
 * 函数功能： 输入文本
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool InputText(QString &ResultText, QString PromptStr,QString DialogCaption,QString DefaultText,QWidget *parent)
{
    bool ok;
    ResultText="";
    QString text = QInputDialog::getText(parent, DialogCaption,
                                         PromptStr, QLineEdit::Normal,
                                         DefaultText, &ok);

    if (ok && !text.isEmpty())
    {
        ResultText=text;
        return true;
    }
    else
    {
        ResultText="";
        return false;
    }

}


/************************************************************************
 * 函数名称： InputPassword
 * 函数功能： 输入文本
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool InputPassword(QString &ResultText, QString PromptStr,QString DialogCaption,QString DefaultText,QWidget *parent)
{
    bool ok;
    ResultText="";
    QString text = QInputDialog::getText(parent, DialogCaption,
                                         PromptStr, QLineEdit::Password,
                                         DefaultText, &ok);

    if (ok && !text.isEmpty())
    {
        ResultText=text;
        return true;
    }
    else
    {
        ResultText="";
        return false;
    }
}

/************************************************************************
 * 函数名称： ShowOpenDialog
 * 函数功能： 显示打开对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
QString ShowOpenDialog(QString title,QString FileFilter,QString InitDir)
{
    QString ss=QFileDialog::getOpenFileName(0,title,InitDir,FileFilter,0,0);
    return ss;
}

/************************************************************************
 * 函数名称：
 * 函数功能： 显示多文件打开对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
int ShowOpenDialogMulti(QStringList &FileList, QString Title,QString FileFilter,QString InitDir)
{
    //QStringList *ts=new QStringList();

    //ts->clear();
    int kk=0;

    FileList.clear();
    try
    {
        FileList=QFileDialog::getOpenFileNames(0,Title,InitDir,FileFilter);
    }
    catch(...)
    {
    }

    kk=FileList.count();
    return kk;
}

/************************************************************************
 * 函数名称： ShowSaveDialog
 * 函数功能： 显示文件保存对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
QString ShowSaveDialog(QString title,QString FileFilter,QString DefaultFilter, QString InitDir)
{
    //    QFileDialog *dd=new QFileDialog(0);
    //    dd->setOption(QFileDialog::DontUseNativeDialog,false);
    //    dd->setViewMode(QFileDialog::List);
    //    dd->setOption(QFileDialog::DontResolveSymlinks,true);
    //    dd->setOption(QFileDialog::DontConfirmOverwrite,true);

    QString pp=QFileDialog::getSaveFileName(0,title,InitDir,FileFilter,0,
                                            QFileDialog::DontConfirmOverwrite | QFileDialog::DontResolveSymlinks |  QFileDialog::DontUseNativeDialog);
    //delete dd;

    QString ss;
    if (!DefaultFilter.isEmpty())
    {
        ss=DefaultFilter.replace("*","");
        if (!ss.isEmpty())
        {
            if (QString(ss.at(0))!=".")
                ss="."+ss;
        }
    }

    return pp;
}


/************************************************************************
 * 函数名称： ShowColorDialog
 * 函数功能： 显示颜色选择对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool ShowColorDialog(QColor &SelectedColor, QString title,QColor InitColor)
{
    SelectedColor=QColorDialog::getColor(InitColor,0,title);
    if (SelectedColor.isValid())
        return true;
    else
    {
        SelectedColor=InitColor;
        return false;
    }
}



/************************************************************************
 * 函数名称： ShowFontDialog
 * 函数功能： 显示颜色选择对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool ShowFontDialog(QFont &SelectedFont, QString title,QFont InitFont)
{
    bool ok;
    SelectedFont=QFontDialog::getFont(&ok,InitFont,0,title);
    if (ok)
        return true;
    else
    {
        SelectedFont=InitFont;
        return false;
    }
}


/************************************************************************
 * 函数名称： SelectDirectory
 * 函数功能： 显示目录选择对话框；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
bool SelectDirectory(QString &SelectDir, QString title,QString InitDir)
{
    if (!InitDir.isEmpty())
        SelectDir=InitDir;
    else
        SelectDir="";

    QString ADir=QFileDialog::getExistingDirectory(0,title,SelectDir);
    SelectDir=ADir;

    return (SelectDir!="");
}



/************************************************************************
 * 函数名称： BeginProgress
 * 函数功能： 开始等待;
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 * 调用例子：  看头文件说明;
 ************************************************************************/
QProgressDialog* BeginProgress(QWidget *ParentWidget,QString WaitingMessage, bool CanBeCanceld, int TheMinValue,int TheMaxValue,
                               QString FormTitle,QString CancelCaption)

{
    QProgressDialog *progress=new QProgressDialog(WaitingMessage,
                                                  CancelCaption,TheMinValue, TheMaxValue, ParentWidget);
    progress->setMinimumDuration(500);
    progress->setWindowTitle(FormTitle);
    if (!CanBeCanceld)
        progress->setCancelButtonText(QString());
    else
        progress->setCancelButton(0);

    progress->setWindowModality(Qt::WindowModal);
    if (!CanBeCanceld)
    {
        QApplication::setOverrideCursor(Qt::BlankCursor);
        //progress->setCursor(Qt::BlankCursor);
        progress->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint |Qt::Dialog);
    }

    progress->setValue(0);
    return progress;
}


QProgressDialog* BeginProgress2(QWidget *ParentWidget,QString WaitingMessage,QString FormTitle)

{
    int TheMinValue=0;
    int TheMaxValue=0;
    QString CancelCaption="";

    QProgressDialog *progress=new QProgressDialog(WaitingMessage,
                                                  CancelCaption,TheMinValue, TheMaxValue, ParentWidget);
    progress->setMinimumDuration(0);
    progress->setWindowTitle(FormTitle);
    progress->setCancelButton(0);

    progress->setWindowModality(Qt::WindowModal);
    progress->show();
    return progress;
}


void EndProgress(QProgressDialog *progress)
{
    if (progress>0 )
    {
        progress->setValue(progress->maximum());
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        delete progress;
        progress=0;
    }
}


bool UpdateProgress(QProgressDialog *progress, int NewPercent,QString WaitingMessage)
{
    if (progress==0 )
        return false;
    if (progress->wasCanceled())
        return false;

    if ((NewPercent<0) || (NewPercent>100))
        return false;

    int FinalValue;
    FinalValue=progress->minimum()+(NewPercent*(progress->maximum()-progress->minimum()) /100 ) ;
    if (progress->value()==FinalValue) //进度没变化;
        return true;

    progress->setValue(FinalValue);
    if ((WaitingMessage!=progress->labelText())  && (WaitingMessage!=""))
        progress->setLabelText(WaitingMessage);

    QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    return true;
}

void BeginWait(QWidget* AWidget)
{
    AWidget->setCursor(Qt::WaitCursor);
}

void EndWait(QWidget* AWidget)
{
    AWidget->setCursor(Qt::ArrowCursor);
}


/************************************************************************
 * 函数名称： AlignCenter
 * 函数功能： 居中显示一个组件；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void AlignCenter(QWidget *AWidget,bool Horizonal,bool Vertical,bool Absolute)
{
    int iWidth,iHeight, iParentWidth,iParentHeight,iParentLeft,iParentTop;
    int iFinalLeft,iFinalTop;

    //1..判断父对象；
    if (AWidget->parent()==0)
    {
        GetScreenSize(iParentWidth,iParentHeight);
    }
    else
    {
        iParentWidth= AWidget->parentWidget()->frameGeometry().width();
        iParentHeight= AWidget->parentWidget()->frameGeometry().height();
    }

    iParentLeft=0;
    iParentTop=0;
    if ((Absolute) && (AWidget->parent()>0))
    {
        iParentLeft=AWidget->parentWidget()->x();
        iParentTop=AWidget->parentWidget()->y();
    }

    //2..计算位置；
    iWidth=AWidget->frameGeometry().width();
    iHeight=AWidget->frameGeometry().height();

    if (Horizonal)
        iFinalLeft= ( iParentWidth-iWidth)/2;
    else
        iFinalLeft= AWidget->x();

    if (Vertical)
        iFinalTop=(iParentHeight-iHeight)/2;
    else
        iFinalTop=AWidget->y();

    AWidget->move(iParentLeft+iFinalLeft,iParentTop+iFinalTop);

}


/************************************************************************
 * 函数名称： GetScreenSize
 * 函数功能： 取得屏幕尺寸；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void GetScreenSize(int &ScreenWidth,int &ScreenHeight)
{
    ScreenWidth= qApp->desktop()->screen()->width();
    ScreenHeight= qApp->desktop()->screen()->height();
}


/************************************************************************
 * 函数名称： SetSize
 * 函数功能： 更改组建大小；-1表示保持不变；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetSize(QWidget* AWidget,int NewWidth=-1,int NewHeight=-1)
{
    int aWidth,aHeight;

    aWidth=AWidget->size().width();
    aHeight=AWidget->size().height();

    if (NewWidth>=0)
        aWidth=NewWidth;

    if (NewHeight>=0)
        aHeight=NewHeight;

    AWidget->resize(aWidth,aHeight);
}

/************************************************************************
 * 函数名称： SetPosition
 * 函数功能： 设置位置；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetPosition(QWidget* AWidget,int LeftPos,int TopPos)
{
    if (AWidget ==0)
        return;

    AWidget->move(LeftPos,TopPos);
}


/************************************************************************
 * 函数名称： SetFontColor
 * 函数功能： 设置前景字体色；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetFontColor(QWidget* AWidget,QColor NewColor)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText,NewColor);
    AWidget->setPalette(pa);
}

void SetFontColor2(QWidget* AWidget,QColor NewColor)
{
    QPalette pa=AWidget->palette();
    pa.setColor(QPalette::Text,NewColor);
    AWidget->setPalette(pa);
}

/************************************************************************
 * 函数名称： SetColor
 * 函数功能： 设置背景色；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetColor(QWidget* AWidget,QColor NewColor)
{
    QString sRed= QString::number(NewColor.red());
    QString sGreen= QString::number(NewColor.green());
    QString sBlue= QString::number(NewColor.blue());

    QString ss=QString("background-color:rgb(")
            +sRed +"," +sGreen +","+sBlue
            +");";

    AWidget->setStyleSheet(ss);
}


/************************************************************************
 * 函数名称： SetFont
 * 函数功能： 设置字体；
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetFont(QWidget* AWidget,int FontSize,QString FontName,bool Bold,bool Italic,bool UnderLine)
{
    if (AWidget ==0)
        return;

    QFont ff;
    ff=AWidget->font();

    if (FontName!="")
        ff.setFamily(FontName);
    ff.setItalic(Italic);
    ff.setBold(Bold);
    ff.setUnderline(UnderLine);

    if ((FontSize>=6) &&(FontSize<=50))
        ff.setPointSize(FontSize);

    AWidget->setFont(ff);
}

void SetIPEdit(QLineEdit *ALineEdit)
{
    if (ALineEdit==0)
        return;

    QRegExp rx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator v(rx, 0);

    ALineEdit->setValidator(&v);
    ALineEdit->setInputMask("000.000.000.000");//只要加上;0保证有默认值即可使得正则和mask同时生效。
}

/************************************************************************
 * 函数名称： SetALabel
 * 函数功能： 设置一个label标签;
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetALabel(QLabel* aLabel, QString LabelCaption,QWidget *OwnParent,
               bool CanVisible,QString Hint,int HorizonAlign,bool AllowWrap
               )
{
    if (aLabel==0)
        return;

    aLabel->setParent(OwnParent);

    // 2..设置对齐方式;
    if ((HorizonAlign>3) || (HorizonAlign<0))
        HorizonAlign=1;

    switch (HorizonAlign)
    {
    case 1:
        aLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter );
        break;
    case 2:
        aLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter );
        break;
    case 3:
        aLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter );
        break;
    default:
        aLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter );
        break;
    }

    //3.. 折行;
    aLabel->setWordWrap(AllowWrap);

    //4.文本格式自动;
    aLabel->setTextFormat(Qt::AutoText);
    aLabel->setText(LabelCaption);
    aLabel->setToolTip(Hint);

    aLabel->setVisible(CanVisible);

}



/************************************************************************
 * 函数名称： SetAEdit
 * 函数功能： 设置一个edit编辑框;
 * 参数说明：
 * 作者 ：    Levon
 * 最后修改：  2010-11-20
 ************************************************************************/
void SetAEdit(QLineEdit* aEdit,QString EditText,QWidget *OwnParent,
              int MaxLen,QString Mask,bool ReadOnlyMode, bool PasswordMode,
              QString Hint,int HorizonAlign)
{
    if (aEdit==0)
        return;

    aEdit->setParent(OwnParent);

    // 1..设置对齐方式;
    if ((HorizonAlign>3) || (HorizonAlign<0))
        HorizonAlign=1;
    switch (HorizonAlign)
    {
    case 1:
        aEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter );
        break;
    case 2:
        aEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter );
        break;
    case 3:
        aEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter );
        break;
    default:
        aEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter );
        break;
    }

    //3.. 只读;长度限制；
    aEdit->setReadOnly(ReadOnlyMode);
    if (MaxLen>0)
        aEdit->setMaxLength(MaxLen);
    else
        aEdit->setMaxLength(32767);


    //4.。密码模式；
    if (PasswordMode)
        aEdit->setEchoMode(QLineEdit::Password);
    else
        aEdit->setEchoMode(QLineEdit::Normal);

    //4.文本格式自动;
    aEdit->setText(EditText);
    aEdit->setToolTip(Hint);

    aEdit->setInputMask(Mask);
}


/***********************************************************************
 * 函数名称： setIP4Validator
 * 函数功能： 输入时检查IP地址的合法性，如果是非法的IP地址则无法进行输入
 * 参数说明：
 * 作者 ：
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
void SetIP4Validator(QLineEdit *lineEdit)
{
    QString Octet = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    lineEdit->setValidator(new QRegExpValidator(
                               QRegExp("^" + Octet + "\\." + Octet + "\\." + Octet + "\\." + Octet + "$"), 0));
}

void EnterBusyMode(QWidget* AWidget)
{
    AWidget->setCursor(Qt::WaitCursor);
    AWidget->repaint();
}

void QuitBusyMode(QWidget* AWidget)
{
    AWidget->setCursor(Qt::ArrowCursor);
    AWidget->repaint();
}

QString ConvertToColorFontTxt(const QString &sColor, const QString &sTxtContent)
{
    return QString("<font color=%1> %2 </font>")
            .arg(sColor).arg(sTxtContent);
}

}//namespce PUBGUI
