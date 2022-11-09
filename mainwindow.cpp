#include <QPushButton>
#include <QDebug>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QLabel>
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
    setCentralWidget(primeCanvas);


    QToolBar *toolbar = addToolBar("main toolbar");
    QAction * incrementBase = toolbar->addAction("++");
    incrementBase->setShortcut(tr("="));
    connect(incrementBase, &QAction::triggered,this,&MainWindow::nextBase);
    QAction * decrementBase = toolbar->addAction("--");
    decrementBase->setShortcut(tr("-"));
    connect(decrementBase, &QAction::triggered,this,&MainWindow::previousBase);

    m_line_edit_base = new QLineEdit();
    m_line_edit_base->setText(QString::number(3));
    QLabel * label1 = new QLabel(QString("Base"));
    toolbar->addWidget(label1);
    toolbar->addWidget(m_line_edit_base);
    QLabel * label2 = new QLabel("Base factors");
    m_line_edit_base_factors.setText("2");
    toolbar->addWidget(label2);
    toolbar->addWidget(&m_line_edit_base_factors);


    QLabel * label3 = new QLabel("Base totient");
    toolbar->addWidget(label3);
    m_line_edit_base_totient.setText("1");


    connect(m_line_edit_base, &QLineEdit::editingFinished, this, &MainWindow::set_new_base_from_line_edit);

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
void MainWindow::set_new_base(const QString & base){
    primeCanvas->changeBase(base.toInt());
}
void MainWindow::set_new_base(int n){
    primeCanvas->changeBase(n);
}
void MainWindow::set_new_base_from_line_edit( ){
    primeCanvas->changeBase(m_line_edit_base->text().toInt());
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
