#include "mainwindow.h"
#include "pushdataobject.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initObject();

}

void MainWindow::initObject()
{
    m_mainWidget= new MainWidget(this);
    setCentralWidget(m_mainWidget);
    connect(m_mainWidget,SIGNAL(sigLoadUsrData(QString)),this,SLOT(slotLoadUsrData(QString)));
    pushDataObject *remoteDataObject=new pushDataObject(this);
    remoteDataObject->getGoodDeatail();
}

MainWindow::~MainWindow()
{

}
QString MainWindow::getCellString(Sheet * sheet,int row,int col){
    QString returnStr="";
    CellType cellType = sheet->cellType(row, col);
    if(sheet->isFormula(row, col))
    {
        returnStr = sheet->readFormula(row, col);
          qDebug() << returnStr << " [formula]";
    }
    else
    {
        switch(cellType)
        {
        case CELLTYPE_EMPTY: std::wcout << "[empty]"; break;
        case CELLTYPE_NUMBER:
        {
            double d = sheet->readNum(row, col);
            returnStr= QString("%1").arg(d, 0, 'f', 0);
            qDebug() << returnStr << " [number]";
            break;
        }
        case CELLTYPE_STRING:
        {
           returnStr = sheet->readStr(row, col);
           qDebug() << returnStr << " [string]";
            break;
        }
        case CELLTYPE_BOOLEAN:
        {
            bool b = sheet->readBool(row, col);
            if(b)
                returnStr="true";
            else
                returnStr="false";
            qDebug() << returnStr << " [boolean]";
            break;
        }
        case CELLTYPE_BLANK: std::wcout << "[blank]"; break;
        case CELLTYPE_ERROR: std::wcout << "[error]"; break;
        }
    }
    return returnStr;
}

//解析xls
void MainWindow::readXls(QString fileName)
{
    m_stampUsrInfoList.clear();
    Book* book = xlCreateBook();
    if(book->load(fileName.toUtf8().constData())){
        Sheet * sheet = book->getSheet(0);
        if(sheet){

            for(int i = 0;i<sheet->lastRow();i++){
                srt_stampuserInfo stampUsrInfo;
                stampUsrInfo.clear();
                stampUsrInfo.usrName=getCellString(sheet,i,0);
                stampUsrInfo.usrPassword=getCellString(sheet,i,1);
                stampUsrInfo.usrPhone=getCellString(sheet,i,2);
                stampUsrInfo.usrCode=getCellString(sheet,i,3);
                m_stampUsrInfoList.append(stampUsrInfo);
            }
            m_mainWidget->refreshTable(m_stampUsrInfoList);

        }
    }else{
        QString sError=  book->errorMessage();
        qDebug()<<"dd"<<sError;
    }
    book->release();
}

void MainWindow::slotLoadUsrData(QString sFilePath)
{
    if(!sFilePath.contains(".xls"))
        return;
    readXls(sFilePath);
}
