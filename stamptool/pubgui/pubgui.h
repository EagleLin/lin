#ifndef PUBGUI_H
#define PUBGUI_H
#include <QObject>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QProgressDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>

#include <QTextEdit>
#include <QLabel>
#include <QRegExp>
#include <QRegExpValidator>

namespace PUBGUI {

/************************************************************************/
/** 弹出提示对话框
*
*   弹出信息提示对话框,仅有一个确定按钮;
*
*   @param   mess       提示信息内容
*   @param   title      对话框标题
*   @return  无
*/
/************************************************************************/
void Information(QString mess,QString title=QObject::tr("提示"),QWidget *parentWindow=0);
void Information(QString mess,QWidget *parentWindow);

/************************************************************************/
/** 弹出错误对话框
*
*   弹出错误对话框,用作提示操作错误。仅有一个确定按钮;
*
*   @param   mess       提示信息内容
*   @param   title      对话框标题
*   @return  无
*/
/************************************************************************/
void ErrorMsg(QString mess,QString title=QObject::tr("错误"),QWidget *parentWindow=0);
void ErrorMsg(QString mess,QWidget *parentWindow);


/************************************************************************/
/** 弹出询问对话框
*
*   弹出询问对话框,显示一个<是>和一个<否>按钮,必须进行选择;
*
*   @param   mess       提示信息内容
*   @param   title      对话框标题
*   @return  无
*/
/************************************************************************/
bool Question(QString mess,QString title=QObject::tr("系统询问"),QWidget *parentWindow=0);
bool Question(QString mess,QWidget *parentWindow);
enum QuestionRetType{
    Yes = 0,
    No,
    cancel
};
int  QuestionYNC(QString mess,QString title=QObject::tr("系统询问"),QWidget *parentWindow=0);

/************************************************************************/
/** 弹出警告对话框
*
*   弹出警告对话框,显示一个<是>和一个<否>按钮,必须进行选择;
*
*   @param   mess       提示信息内容
*   @param   title      对话框标题
*   @return  无
*/
/************************************************************************/
bool Warning(QString mess,QString title=QObject::tr("警告"),QWidget *parentWindow=0);
bool Warning(QString mess,QWidget *parentWindow);

QString Warning(QString mess,QStringList slButtonInfoList,QString title=QObject::tr("提示"),QWidget *parentWindow=0);


/************************************************************************/
/** 弹出文件打开对话框（单选）
*
*   弹出文件打开对话框，当需要选择单个文件路径的时候用，
*
*   @param   title      对话框标题
*   @param   FileExt    文件扩展名过滤，多个扩展名用双分号隔开；如："Images (*.png *.xpm *.jpg);;Text files (*.txt)"
*   @param   InitDir    起始路径
*   @return  如果用户选择了一个文件，则返回该文件路径；否则返回空字符串
*/
/************************************************************************/
QString ShowOpenDialog(QString title=QObject::tr("选择文件"),QString FileExt=QObject::tr("所有文件(*.*)"),QString InitDir="/home");



/************************************************************************/
/** 弹出文件打开对话框（多选）
*
*   弹出文件打开对话框，当允许选择多个文件路径的时候用，（多选）
*
*   @param   FileList       返回的多个文件路径列表；
*   @param   Title          对话框标题
*   @param   FileFilter     文件扩展名过滤，多个扩展名用双分号隔开；如："Images (*.png *.xpm *.jpg);;Text files (*.txt)"
*   @param   InitDir        起始路径
*   @return  如果用户选择了一个或多个文件后，返回所有用户选中文件的路径列表，如果未选择，则返回列表的数量为0；
*/
/************************************************************************/
int ShowOpenDialogMulti(QStringList &FileList, QString Title=QObject::tr("选择多个文件"),QString FileFilter=QObject::tr("所有文件(*.*)"),QString InitDir="/home");



/************************************************************************/
/** 弹出文件保存对话框
*
*   弹出文件保存对话框，提示用户选择保存路径，并输入文件名，返回整个目标路径；
*
*   @param   title      对话框标题
*   @param   FileExt    文件扩展名过滤，多个扩展名用双分号隔开；如："Images (*.png *.xpm *.jpg);;Text files (*.txt)"
*   @param   InitDir    起始路径
*   @return  如果用户选择了目标保存路径，并输入了文件名，则返回整个文件路径；否则返回空字符串
*/
/************************************************************************/
QString ShowSaveDialog(QString title=QObject::tr("保存为"),QString FileExt=QObject::tr("所有文件(*.*)"),QString DefaultFilter="",QString InitDir="/home");



/************************************************************************/
/** 弹出颜色选择对话框
*
*   弹出颜色选择对话框，提示用户选择一个RGB颜色。
*
*   @param   SelectedColor      最终返回的颜色值；类型为QColor
*   @param   title              对话框标题
*   @param   InitColor          默认起始选中的颜色值；
*   @return  如果用户选择了一种颜色并确定，则返回true，并将用户选择的颜色存入参数SelectedColor中；
*            如果用户未选择一个颜色，或选择的颜色无效，则返回false，并且默认的颜色值存入参数SelectedColor中
*/
/************************************************************************/
bool ShowColorDialog(QColor &SelectedColor, QString title=QObject::tr("选择颜色"),QColor InitColor=QColor("white"));




/************************************************************************/
/** 弹出字体选择对话框
*
*   弹出字体选择对话框，提示用户选择一个字体。
*
*   @param   SelectedFont      最终返回的字体；
*   @param   title             对话框标题
*   @param   InitFont          默认起始选中的字体；
*   @return  如果用户选择了一种字体并确定，则返回true，并将用户选择的字体存入参数SelectedFont中；
*            如果用户未选择一个字体，或选择的字体无效，则返回false，并且默认的字体存入参数SelectedFont中
*/
/************************************************************************/
bool ShowFontDialog(QFont &SelectedFont, QString title=QObject::tr("选择字体"),QFont InitFont=QFont("sans",10));



/************************************************************************/
/** 弹出目录选择对话框；
*
*   弹出目录选择对话框，提示用户选择一个目标目录。
*
*   @param   SelectDir         最终返回的目录路径位置；
*   @param   title             对话框标题
*   @param   InitDir           默认启动选择的路径
*   @return  如果用户选择了一个目录并确定，则返回true，并将用户选择的目录路径存入参数SelectDir中；
*            如果用户未选择一个目录，或选择的目录无效，则返回false，并且默认的路径存入参数SelectDir中
*   @note    注意：用户选择的目标路径必须已经存在。
*/
/************************************************************************/
bool SelectDirectory(QString &SelectDir, QString title=QObject::tr("选择目标目录"),QString InitDir="/home");


/************************************************************************/
/** 弹出文本输入对话框
*
*   弹出文本输入对话框，提示用户输入一段文字
*
*   @param   ResultText            最终返回的用户输入的文本内容
*   @param   PromptStr             协助用户进行输入的提示信息（如提示用户应该输入什么内容等...）
*   @param   DialogCaption         弹出输入对话框的对话框标题；
*   @param   DefaultText           默认文本内容（该内容在弹出时即自动填入,可用设置默认值）
*   @return  如果用输入文本并确定，则返回true，并将输入内容存入返回参数ResultText中；
*            否则返回false，且返回参数ResultText为空；
*   @note
*/
/************************************************************************/
bool InputText(QString &ResultText, QString PromptStr=QObject::tr("请在下列文本框中输入内容:"),
               QString DialogCaption=QObject::tr("文本输入"),QString DefaultText="",QWidget *parent=0);

bool InputPassword(QString &ResultText, QString PromptStr=QObject::tr("请输入正确口令继续:"),
                   QString DialogCaption=QObject::tr("口令验证"),QString DefaultText="",QWidget *parent=0);


/************************************************************************/
/** 设置某个部件的位置
*
*   设置某个部件的位置，（移动部件到某个新位置；）
*
*   @param   AWidget            目标部件
*   @param   LeftPos            目标位置起点的x坐标
*   @param   TopPos             目标位置起点的y坐标
*   @return  无
*/
/************************************************************************/
void SetPosition(QWidget* AWidget,int LeftPos,int TopPos);



/************************************************************************/
/** 设置某个部件的尺寸
*
*   设置某个部件的位置，（移动部件到某个新位置；）
*
*   @param   AWidget            目标部件
*   @param   NewWidth           目标部件的宽度，如果该参数<0,则宽度不改变，保留原值；
*   @param   NewHeight          目标部件的高度，如果该参数<0,则高度不改变，保留原值；
*   @return  无
*/
/************************************************************************/
void SetSize(QWidget *AWidget,int NewWidth,int NewHeight);



/************************************************************************/
/** 设置某个部件的字体颜色（前景色）；
*
*   设置某个部件的字体颜色（前景色）；
*
*   @param   AWidget            目标部件
*   @param   NewColor           字体颜色的颜色值，类型为QColor
*   @return  无
*/
/************************************************************************/
void SetFontColor(QWidget* AWidget,QColor NewColor);
void SetFontColor2(QWidget* AWidget,QColor NewColor);


/************************************************************************/
/** 设置某个部件的背景色；
*
*   设置某个部件的背景色；
*
*   @param   AWidget            目标部件
*   @param   NewColor           背景色的颜色值，类型为QColor
*   @return  无
*/
/************************************************************************/
void SetColor(QWidget* AWidget,QColor NewColor);



/************************************************************************/
/** 设置某个部件的字体
*
*   设置某个部件的字体，可以设置字体大小，字体名称，字体样式等。
*
*   @param   AWidget            目标部件
*   @param   FontSize           目标部件的字体大小；
*   @param   FontName           目标部件的字体名称；
*   @param   Bold               字体是否加粗；
*   @param   Italic               字体是否斜体显示；
*   @return  无
*/
/************************************************************************/
void SetFont(QWidget* AWidget,int FontSize=10,QString FontName="sans",bool Bold=false,bool Italic=false,bool UnderLine=false);



/************************************************************************/
/** 得到屏幕尺寸；
*
*   得到屏幕尺寸；返回屏幕的宽度和高度；
*
*   @param   ScreenWidth          返回的屏幕高度；
*   @param   ScreenHeight         返回的屏幕高度；
*   @return  无
*/
/************************************************************************/
void GetScreenSize(int &ScreenWidth,int &ScreenHeight);



/************************************************************************/
/** 将一个组件居中显示
*
*   将一个组件居中显示，这里的居中是相对于其父组件的相对居中
*
*   @param   AWidget            目标部件
*   @param   Horizonal          是否水平方向居中，默认是true
*   @param   Vertical           是否垂直方向居中，默认是true
*   @return  无
*/
/************************************************************************/
void AlignCenter(QWidget *AWidget,bool Horizonal=true,bool Vertical=true,bool Absolute=false);



/************************************************************************/
/** 显示开始等待状态
*
*   显示开始等待状态，组件的光标变为等待光标，表示正在忙碌；
*
*   @param   AWidget            目标部件，通常为this
*   @return  无
*/
/************************************************************************/
void BeginWait(QWidget* AWidget);



/************************************************************************/
/** 退出等待状态
*
*   退出等待状态，组件的光标变为正常光标，表示忙碌已经结束。
*
*   @param   AWidget            目标部件，通常为this
*   @return  无
*/
/************************************************************************/
void EndWait(QWidget* AWidget);



/************************************************************************/
/** 显示一个进度对话框；可显示进度，提示信息，是否允许取消等；
*
*   @param   ParentWidget            所属父类组件，通常为this即可；
*   @param   WaitingMessage          显示的等待信息内容；
*   @param   CanBeCanceld            进度是否可以被取消，
*   @param   TheMinValue             进度最小值，默认为0；
*   @param   TheMaxValue             进度最大值，默认为100
*   @param   FormTitle               整个显示进度对话框的标题
*   @param   CancelCaption           操作取消的文本内容；
*   @return  该操作将创建一个新的进度对话框对象，如果创建成功，则将返回该对象指针。
*   @note    注意：如果返回结果为0，则表示创建不成功。
*            返回结果应该保存，便于下面利用该返回指针进行进度对话框的更新和关闭操作；
*
*   调用例子：
* ===============================================================
    int  iTotalRunTimes=100; //总运行次数;
    bool bCanceled=false;
    QString sWaitingMessage=QObject::tr("正在搜索曲库路径下的可用歌曲文件..."); //等待标题;

    //0..创建进度条;
    QProgressDialog *progress=BeginProgress(this,sWaitingMessage);//开始进度；
    for (int i=0;i<iTotalRunTimes;i++)
    {
        //1..判断是否取消;
        if (progress->wasCanceled())
        {
            bCanceled=true;
            break;
        }
        //2..更新进度;
        if (!UpdateProgress(progress,(i*100)/iTotalRunTimes))
            break;


        //3..具体操作;(code here)
        PUBFUN::Delay(10);

    }
    //4..如果被用户取消,采取的操作;
    if (bCanceled)
    {

    }

    //5..释放;
    EndProgress(progress);
*====================================================================
*/
/************************************************************************/
QProgressDialog* BeginProgress(QWidget *ParentWidget,QString WaitingMessage, bool CanBeCanceld=false, int TheMinValue=0,int TheMaxValue=100,
                               QString FormTitle=QObject::tr("请稍候..."),QString CancelCaption=QObject::tr("取消"));



/************************************************************************/
// 以无确切进度的方式显示等对话框;(进度来回滚动,适合进度不确切可知的情况)
/************************************************************************/
QProgressDialog* BeginProgress2(QWidget *ParentWidget,QString WaitingMessage,QString FormTitle=QObject::tr("请稍候..."));


/************************************************************************/
// 关闭进度对话框
/************************************************************************/
void EndProgress(QProgressDialog *progress);



/************************************************************************/
/** 更新进度对话框的进度
*
*   @param   progress            目标进度对话框对象
*   @param   progress            目标进度对话框上的最新进度，取值（0-100）
*   @param   WaitingMessage     显示的等待信息，空字符串则不更新进度对话框的提示信息；
*   @return  操作失败，则返回false；如果整个操作被用户取消，则也返回false，可根据此进行相关操作；
*/
/************************************************************************/
bool UpdateProgress(QProgressDialog *progress, int NewPercent,QString WaitingMessage="");


void SetIPEdit(QLineEdit *ALineEdit);

void SetALabel(QLabel* aLabel, QString LabelCaption,QWidget *OwnParent,
               bool CanVisible=true,QString Hint="",int HorizonAlign=1,bool AllowWrap=false);


void SetAEdit(QLineEdit* aEdit,QString EditText,QWidget *OwnParent,
              int MaxLen=0,QString Mask="",bool ReadOnlyMode=false, bool PasswordMode=false,
              QString Hint="",int HorizonAlign=1);

void SetIP4Validator(QLineEdit *lineEdit);

void EnterBusyMode(QWidget* AWidget);
void QuitBusyMode(QWidget* AWidget);

QString ConvertToColorFontTxt(const QString &sColor, const QString &sTxtContent);

}//namespace PUBGUI

#endif //PUBGUI_H


