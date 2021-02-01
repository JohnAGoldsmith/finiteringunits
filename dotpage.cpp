#include <QHash>
#include <algorithm>
#include <QColor>
#include <QDebug>
#include "dotpage.h"
#include "dot.h"


cDotPage::cDotPage (int base){
    Base = base;
    populate(Base);
    qDebug() << "end of DotPage creation.";
}




void cDotPage::populate(int N)
{   Base = N;
    cDot* pDot;
    RemoveAll();
    int inverse, order;
    for (int i = 1; i <=N; i++){
        ComputeInverseAndOrder(i, inverse, order);
        if (inverse > 0){  
            pDot = new cDot(i, inverse,order);
            pDot->setParent(this);
            Dots.append(pDot);
        } 
    }
   AssignColorIndexFromOrder();
}

void cDotPage::ComputeInverseAndOrder(int n, int& inverse, int& order)
{
    for (int m = 1; m <= Base; m++){
       int z = n * m;
       int remainder = z % Base;
       if (remainder == 1){
          inverse = m;
          order = int (z / Base);
          //qDebug() << "inverse: " << inverse << " order: " << order;
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
bool sortbyfirst (const QPair<int, int> &a,
                   const QPair<int, int> &b)
{
  return (a.first < b.first);
}
bool sortbysecond (const QPair<int, int> &a,
                   const QPair<int, int> &b)
{
  return (a.second > b.second);
}
void cDotPage::AssignColorIndexFromOrder()
{
    QHash<int, int> orderCounter;
    cDot*   pDot;

    for (int i = 0; i < size(); i++)
    {
        pDot = GetAt(i);
        if ( ! orderCounter.contains(pDot->getOrder()))
        {
            orderCounter[pDot->Order] = 0;
        }
        orderCounter[pDot->Order] += 1;
        qDebug() << i << pDot->Number << pDot->Inverse << pDot->Order;
    }
    // count how often each Order occurs
    QList<QPair<int,int>>countList  ;
    QHashIterator<int, int> i(orderCounter);
    while (i.hasNext()) {
        i.next();
        countList.append(QPair<int,int>(i.key(),i.value())); // the "key"  is the order, the value is the count of them.
        //qDebug() << i.key() << "count " << i.value();
    }
    std::sort(countList.begin(), countList.end(), sortbysecond);
    /* Now they are sorted by how often each order occurs among the dots */

    QHash<int,int> order2colorcode;
    for (int i = 0; i < countList.size(); i++){
        //qDebug() << "A"<< i << "order"<< countList[i].first << "count"<< countList[i].second;
        //countList[i].second = i;
        //qDebug() << "A"<< i << "order"<< countList[i].first << "color index"<< countList[i].second;
        order2colorcode[countList[i].first] = i;
    }

    for (int j = 0; j < size(); j++)
    {
        pDot = GetAt(j);
        //qDebug() << j << pDot->Number << "order" << pDot->Order << "color index" << pDot->ColorIndex;
        if (pDot->getOrder() >= 0){
          pDot->setColorIndex(order2colorcode[pDot->getOrder()]);
          //qDebug() << "B" << "dot number" << pDot->Number << "order"<< pDot->Order << "color index" << pDot->ColorIndex;
        }
    }




}


/*
void cDotPage::SetEulerPhi(int n)
{	m_PhiOfBase = n; }
int cDotPage::GetEulerPhi()
{ return m_PhiOfBase; }
*/
