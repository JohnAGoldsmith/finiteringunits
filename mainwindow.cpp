#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cprimecanvas.h"

//class cPrimeCanvas;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() <<  "In mainwindow, just starting";

    this->primeCanvas = new cPrimeCanvas;
    qDebug() <<"MainWindow; made primecanvas" << primeCanvas->getDotPage()->Dots.size();
    setCentralWidget(primeCanvas);

    qDebug() << 19 << " set widget in larger window";
    qDebug() << "End of main window; Number of elements: " << primeCanvas->getDotPage()->Dots.size();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->primeCanvas;
}
