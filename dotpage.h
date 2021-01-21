#ifndef DOTPAGE_H
#define DOTPAGE_H
#include <QList>

class cDot;


class cDotPage
{
public:
    QList<cDot*>                        Dots;
    int									Base; // modular base
    int*								OrderPopulation; // how many members there are of each order.
    int									m_PhiOfBase;


    cDotPage();
    cDotPage(int);
    virtual                             ~cDotPage();
    //void								Serialize(CArchive&);
    //void								SendToFile (ofstream&);
    //void								ReadFromFile (ifstream&);
    //void								Display(CPaintDC* dc, QRect&, int Prime, int DotSize );
public:
    QList<cDot*>*                       GetDots();
    int									getBase();
    void								setBase(int);
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
