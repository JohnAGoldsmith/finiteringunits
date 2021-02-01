#ifndef CPRIMECANVAS_H
#define CPRIMECANVAS_H
#include <QColor>
#include <QWidget>
#include <QMouseEvent>

#include "dotpage.h"

class MainWindow;

class cPrimeCanvas : public QWidget
{
    Q_OBJECT

    cDotPage*   dotPage;
    int         margin;
    int         diameter; // size of dots themselves
    int         xunit;
    int         yunit;
    MainWindow* myMainWindow;

public:
    cPrimeCanvas(QWidget * parent = 0);
    int Base() {return dotPage->getBase();}

    cDotPage*   getDotPage() {return dotPage;}
    int         getBase() {return dotPage->getBase();}
    void        changeBase(int base);
    void        setMainWindow (MainWindow* mainwindow) {myMainWindow = mainwindow;} //this should be in the constructor.
    MainWindow* getMainWindow(){return myMainWindow;}


    protected:
    virtual void paintEvent (QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event ) override;
    void mouseReleaseEvent(QMouseEvent *event ) override;



    int abs2localX(int x);
    int abs2localY(int y);
    int local2absX(int x);
    int local2absY(int y);
    void calculateXunit();
    void calculateYunit();
    int getXunit(){return xunit;}
    int getYunit(){return yunit;}
    void setXunit(int d){xunit = d;}
    void setYunit(int d){yunit = d;}


};



#endif // CPRIMECANVAS_H
