#ifndef CPRIMECANVAS_H
#define CPRIMECANVAS_H
#include <QColor>
#include <QWidget>
#include <QMouseEvent>

#include "dotpage.h"

class cPrimeCanvas : public QWidget
{
    Q_OBJECT

    cDotPage dotPage;
    int margin;
    int diameter; // size of dots themselves
    int xunit;
    int yunit;

public:
    cPrimeCanvas(QWidget * parent = 0);
    int Base() {return dotPage.getBase();}
    void displayDotPage(cDotPage& dotPage); // remove this, not to be used.
    cDotPage*   getDotPage() {return &dotPage;}
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
