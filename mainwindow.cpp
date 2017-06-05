#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QTime>
#include "nodeitem.h"
#include "astar.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(400,460);
    QPushButton *btn=new QPushButton(this);
    btn->setText(tr("Reset"));
    btn->move(170,15);
    btn->resize(60,20);
    connect(btn,SIGNAL(clicked()),this,SLOT(resetAstarPath()));
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            int rand;
            NodeItem* ni=new NodeItem(i,j,false);
            rand=qrand()%100;
            QPushButton *btn=new QPushButton(this);
            btn->setStyleSheet("background-color:white");
            btn->setText(tr(""));
            btn->move(20*i,20*j+40);
            btn->resize(20,20);
            ni->Button=btn;
            Map[i][j]=ni;
        }
    }
    resetAstarPath();
}

void MainWindow:: resetAstarPath()
{
    StarNode=NULL;
    EndNode=NULL;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            int rand;
            NodeItem* ni=Map[i][j];
            ni->isWall=false;
            rand=qrand()%100;
            QPushButton *btn=ni->Button;
            btn->setStyleSheet("background-color:white");
            btn->setText(tr(""));
            if(rand>88)
            {
                ni->isWall=true;
                btn->setStyleSheet("background-color:green");
            }
        }
    }

    while (1)
    {
        int StarRandX=qrand()%20;
        int StarRandY=qrand()%20;
        int EndRandX=qrand()%20;
        int EndRandY=qrand()%20;
        if(Map[StarRandX][StarRandY]->isWall==false&&StarNode==NULL)
            StarNode=Map[StarRandX][StarRandY];
        if(Map[EndRandX][EndRandY]->isWall==false&&EndNode==NULL&&Map[EndRandX][EndRandY]!=StarNode)
            EndNode=Map[EndRandX][EndRandY];
        if(StarNode!=NULL&&EndNode!=NULL)
        {
            StarNode->Button->setStyleSheet("background-color:blue");
            StarNode->Button->setText(tr("S"));
            EndNode->Button->setStyleSheet("background-color:yellow");
            EndNode->Button->setText(tr("E"));
            break;
        }
    }

    Astar *A=new Astar(StarNode,EndNode,Map);
    pathList=A->AStarPath();
    for(int i=0;i<pathList->length();i++)
    {
        pathList->value(i)->Button->setStyleSheet("background-color:gray");
        pathList->value(i)->Button->setText(tr("x"));
    }
    delete A;
}



MainWindow::~MainWindow()
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            delete Map[i][j];
            Map[i][j]=NULL;
        }
    }
    StarNode=NULL;
    EndNode=NULL;
    delete ui;
}


