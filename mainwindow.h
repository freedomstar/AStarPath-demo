#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "nodeitem.h"
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QList<NodeItem*>* pathList;
    NodeItem *StarNode;
    NodeItem *EndNode;
    NodeItem *Map[20][20];
    Ui::MainWindow *ui;

public slots:
    void resetAstarPath();
};

#endif // MAINWINDOW_H
