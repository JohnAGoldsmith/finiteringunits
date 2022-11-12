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

    cDotPage*               m_dotPage;
    int                     margin;
    int                     diameter; // size of dots themselves
    int                     xunit;
    int                     yunit;
    MainWindow*             m_main_window;
    //QList<int>              m_primes;
    QVector<QList<int>*>    m_factors;
    int                     m_largest_integer_factored;


public:
    cPrimeCanvas(MainWindow* main_window, QWidget * parent = nullptr); // when the second argument is absent, it should be freefloating widget.
    int         get_base() {return m_dotPage->get_base();}
    void        increment_base();
    void        decrement_base();

    cDotPage*   getDotPage() {return m_dotPage;}
    void        change_base(int base);
    void        setMainWindow (MainWindow* mainwindow) {m_main_window = mainwindow;} //this should be in the constructor.
    MainWindow* getMainWindow(){return m_main_window;}
    void        compute_primes_and_factors(int upto_N);
    QList<int> * get_factors(int n) {return m_factors[n]; }
    int         get_largest_integer_factored();
    //int         get_largest_prime() {return m_primes.back();}

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
