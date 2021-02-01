#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include "cprimecanvas.h"

class cCanvasCollection;

namespace Ui {
class MainWindow;
}

class cPrimeCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QList<cDotPage*>*  getDotPageCollection() {return &DotPageCollection;}
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *incrementButton;
    QPushButton *decrementButton;

    cPrimeCanvas *primeCanvas;
    QList<cDotPage*> DotPageCollection;

    QMenu Menu1;
    void  createMenus();
    void  maybeSaveDotPage();
    cPrimeCanvas* getPrimeCanvas() {return primeCanvas;}
    int getBase();
private slots:
    void incrementBase(int i);
    void nextBase();
    void previousBase();

};

#endif // MAINWINDOW_H
