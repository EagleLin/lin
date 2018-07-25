#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include "mainwidget.h"
#include "pubfun.h"
#include "libxl.h"
#include <iostream>
using namespace std;
#include <QDebug>
using namespace libxl;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void initObject();
    ~MainWindow();
    void readFromUsrdata();
    void readXls(QString fileName);
private:
    QString getCellString(Sheet * sheet,int row,int col);
public slots:
    void slotLoadUsrData(QString sFilePath);
private:
    MainWidget *m_mainWidget;
    QList<srt_stampuserInfo> m_stampUsrInfoList;
};

#endif // MAINWINDOW_H
