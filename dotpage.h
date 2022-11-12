#ifndef DOTPAGE_H
#define DOTPAGE_H
#include <QList>
#include <QObject>
class cDot;

class cPrimeCanvas;

class cDotPage: QObject
{ Q_OBJECT

public:
    QList<cDot*>                        m_Dots;
    int									m_base; // modular base
    //int*								OrderPopulation; // how many members there are of each order.
    QString									m_PhiOfBase;


    cDotPage();
    cDotPage(int, cPrimeCanvas * parent = nullptr);
    virtual ~cDotPage() {};
private:
    cPrimeCanvas*                       m_parent;
public:

    QList<cDot*>*                       GetDots() {return &m_Dots;}
    int									get_base() {return m_base;}
    cPrimeCanvas*                           get_parent() {return m_parent;}
    void                                increment_base(int n = 1) {m_base += n;}
    void								populate(int);
    void								RemoveAll();
    int									size();
    cDot*								GetAt(int);
    void								populatePage(int N);
    void								AssignColorIndexFromOrder();
    void								ComputeInverseAndOrder (int n, int & inverse, int & order);
    int									GetEulerPhi();
    void								SetEulerPhi(int);

};



#endif // DOTPAGE_H
