#include <QPushButton>
#include <QDebug>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QWidgetAction>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cprimecanvas.h"

class cPrimeCanvas;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Muliplicative inverses in Z/N");


    this->primeCanvas = new cPrimeCanvas(this);
    primeCanvas->setMainWindow(this); // this should be in the previous line, the constructor;
    //qDebug() <<"MainWindow; made primecanvas" <<
    //primeCanvas->getDotPage()->Dots.size();
    setCentralWidget(primeCanvas);


    QToolBar *toolbar = addToolBar("main toolbar");
    QAction * incrementBase = toolbar->addAction("++");
    incrementBase->setShortcut(tr("+"));
    connect(incrementBase, &QAction::triggered,this,&MainWindow::nextBase);
    QAction * decrementBase = toolbar->addAction("--");
    decrementBase->setShortcut(tr("-"));
    connect(decrementBase, &QAction::triggered,this,&MainWindow::previousBase);



}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->primeCanvas;
}
void MainWindow::incrementBase(int i){
    //maybeSaveDotPage();
    getPrimeCanvas()->changeBase( i + primeCanvas->getBase());
}
int MainWindow::getBase(){
    return primeCanvas->getBase();
}
void MainWindow::nextBase(){
    incrementBase(1);
}
void MainWindow::previousBase(){
    if (getBase() > 3){
       incrementBase(-1);
    }
}
void MainWindow::maybeSaveDotPage(){
    for (int i=0;i<DotPageCollection.size(); i++){
        if (primeCanvas->getDotPage()->getBase() == DotPageCollection[i]->getBase()){
            return;
        }
    }
    DotPageCollection.append(primeCanvas->getDotPage());
}
/*
void MainWindow::createMenus()
{
    Menu1 = menuBar()->addMenu(tr("&Change base"));
    Menu1.addAction(incrementBase);
    Menu1.addAction(decrementBase);
}
*/
