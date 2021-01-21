#include <QHash>
#include <algorithm>
#include <QColor>
#include <QDebug>
#include "dotpage.h"
#include "dot.h"

cDotPage::cDotPage()
{
}

cDotPage::cDotPage (int base){
    Base = base;
    //populatePage(Base);
    qDebug() << "end of DotPage creation.";
}

cDotPage::~cDotPage()
{
    RemoveAll();
    //if (OrderPopulation) delete OrderPopulation;
}

void cDotPage::setBase(int N)
{   Base = N;
    qDebug() << "Enter DotPage::setBase" ;
    cDot* pDot;
    RemoveAll();
    int inverse, order;
    for (int i = 1; i <=N; i++){

        ComputeInverseAndOrder(i, inverse, order);
        if (inverse > 0){
            //qDebug() << 96 << "number "<<i << "inverse "<< inverse;
            pDot = new cDot(i, inverse,order);
            qDebug() << pDot->display();
            Dots.append(pDot);
        }
    }
   qDebug() << "End of SetBase, with this many dots" << this->Dots.size();
}
void cDotPage::ComputeInverseAndOrder(int n, int& inverse, int& order)
{
    for (int m = 1; m <= Base; m++){
       int z = n * m;
       int remainder = z % Base;
       if (remainder == 1){
          inverse = m;
          order = int (z / Base);
          qDebug() << "inverse: " << inverse << " order: " << order;
          return;
       }
       if (remainder == 00){
           inverse = -1;
           order = -1;
           return;
       }
    }
    inverse = -1;
    order = -1;
}

QList<cDot*>*	cDotPage::GetDots()
{ return &Dots;
}

int cDotPage::getBase() {return Base;}

void	cDotPage::RemoveAll()
{
    for (int i = 0; i < Dots.size(); i++)
    {
        delete Dots.at(i);
    }
    Dots.clear();
}
cDot* cDotPage::GetAt(int n) {return Dots.at(n);}
int	  cDotPage::size() {return Dots.size();}
/*void cDotPage::Serialize(CArchive& ar)
{
    Dots.Serialize(ar);

    if (ar.IsStoring())
    {
        ar << Base;
        for (int i = 0; i < Dots.GetSize(); i++)
        {
            Dots.GetAt(i)->Serialize(ar);
        }
    }
    else
    {
        ar >> Base;
        for (int i = 0; i < Dots.GetSize(); i++)
        {
            Dots.GetAt(i)->Serialize(ar);
        }
    }
}

void cDotPage::SendToFile(ofstream& out)
{


    out << "\n\n" << Base<<'\t'<<m_PhiOfBase<< "\n";
    for (int i = 0; i < Dots.GetSize(); i++)
    {
        Dots.GetAt(i)->SendToFile(out);
        out << "\t" ;
    }

}
void cDotPage::ReadFromFile(ifstream& in)
{
    cDot* pDot;
    in  >> m_PhiOfBase;
    for (int i = 0; i < m_PhiOfBase; i++)
    {
        pDot = new cDot();

        Dots.SetAtGrow(i, pDot);
        Dots.GetAt(i)->ReadFromFile(in);
    }

}
*/

/*
void cDotPage::Display(CPaintDC* dc, QRect& r, int Prime, int DotSize)
{
    cDot* pDot;
    int x,y;
    int Width = r.height() ; // !!!!!!!!!!
    float prop = (float)1.4;
    float xscale = float ( Width / (prop * Prime) );
    float yscale = float ( r.height() / (prop * Prime) );
    int x0 = Width/6;
    int y0 = int ( r.height()*.85 );
    QBrush*		qBrush;

    for (int i = 0; i < Dots.size(); i++)
    {
                pDot = Dots.at(i);
                x = int ( x0 + pDot->Number   * xscale );
                y = int ( y0 - pDot->Inverse * yscale );
                qBrush = new QBrush ( *pDot->GetColor() );
                dc->SelectObject(qBrush);
                dc->Ellipse( x - DotSize, y - DotSize , x+ DotSize , y + DotSize );
                pDot->x = x;
                pDot->y = y;
                if (qBrush) {	delete qBrush; qBrush = NULL;}
    }


}
*/
int compare (const void *x, const void *y)
{

    int *X = (int*) x,
        *Y = (int*) y;
    return (*X-*Y);
}

bool sortbysecond (const QPair<int, int> &a,
                   const QPair<int, int> &b)
{
  return (a.second < b.second);
}
void cDotPage::AssignColorIndexFromOrder()
{
    QHash<int, int> orderCounter;
    cDot*   pDot;
    int		order;
    int		Number;

    for (int i = 0; i < size(); i++)
    {
        pDot = GetAt(i);
        if ( ! orderCounter.contains(pDot->getOrder()))
        {
            orderCounter[pDot->Order] = 0;
        }
        orderCounter[pDot->Order] += 1;
    }
    // count how often each Order occurs
    QVector<int> countVector  ;
    QHashIterator<int, int> i(orderCounter);
    while (i.hasNext()) {
        i.next();
        countVector.append(i.key()); // the "key"  is the order, the value is the count of them.
    }

    // invert these, to sort Orders by their frequency
    QVector<QPair<int, int>> inverted;

    // Populate the inverted list
    for (auto k : orderCounter.keys()) {
      inverted.append(QPair<int, int>(countVector[k], k));
    }

    std::sort(inverted.begin(), inverted.end(), sortbysecond);

    for (int j = 0; j < size(); j++)
    {
        pDot = GetAt(j);
        pDot->setColorIndex(inverted[0].second);
    }
/*        switch (MyOrder)
        {
        case 0:  {
            pDot->SetColor(QColor(0,0,0)); break;} // black
        case 1: {
            *pColor = RGB(0, 255, 0); break;}	//green
        case 2: {
            *pColor = RGB(0, 0, 255); break;}	// blue
        case 3: {
            *pColor = RGB(255, 255, 0); break;}	// yellow
        case 4: {
            *pColor = RGB(127, 255, 255); break;}	// light blue
        case 5: {
            *pColor = RGB(255, 127, 255); break;}	// violet
        case 6: {
            *pColor = RGB(255, 255, 127); break;}	//
        case 7: {
            *pColor = RGB(175, 175, 175); break;}	// gray
        case 8: {
            *pColor = RGB(100, 240, 240); break;}	// aqua
        case 9: {
            *pColor = RGB(240, 100, 240); break;}	// purple
        case 10: {
            *pColor = RGB(240, 240, 100); break;}	// sick yellow
        case 11: {
            *pColor = RGB(255, 175, 10); break;}	//
        case 12: {
            *pColor = RGB(255, 10, 175); break;}	//
        case 13: {
            *pColor = RGB(175, 10, 255); break;}	//
        case 14: {
            *pColor = RGB(175, 175, 10); break;}	//
        case 15: {
            *pColor = RGB(10, 175, 255); break;}	//
        case 16: {
            *pColor = RGB(10, 255, 175); break;}	//

        default: {
            *pColor = RGB(255, 255, 255); break;} // default is white
        }
*/




}


/*
void cDotPage::SetEulerPhi(int n)
{	m_PhiOfBase = n; }
int cDotPage::GetEulerPhi()
{ return m_PhiOfBase; }
*/
