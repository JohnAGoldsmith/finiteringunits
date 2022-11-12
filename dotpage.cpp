#include <QHash>
#include <algorithm>
#include <QColor>
#include <QDebug>
#include "dotpage.h"
#include "dot.h"
#include "cprimecanvas.h"
#include "mainwindow.h"



cDotPage::cDotPage (int base, cPrimeCanvas * canvas){
    m_parent = canvas;
    m_base = base;
    populate(m_base);
    //eqDebug() << "end of DotPage creation.";
    m_PhiOfBase = m_parent->getMainWindow()->euler(base);
}


void cDotPage::populate(int N)
{   m_base = N;
    cDot* pDot;
    RemoveAll();
    int inverse, order;
    for (int i = 1; i <=N; i++){
        ComputeInverseAndOrder(i, inverse, order);
        if (inverse > 0){  
            pDot = new cDot(i, inverse,order);
            pDot->setParent(this);
            m_Dots.append(pDot);
        } 
    }

   AssignColorIndexFromOrder();
}

void cDotPage::ComputeInverseAndOrder(int n, int& inverse, int& order)
{   int value = n;
    for (int m = 1; m <= m_base; m++){
       int next_value = (m * value) % m_base;
       if (next_value == 1){
          inverse = m;
          //qDebug() << 48 << "value" << value <<  "inverse" <<  m << Base  ;
          break;
       }
       if (next_value == 00){
           inverse = -1;
           order = -1;
           return;
       }
    }
    int product = n;
    for (int z = 1; z < m_base; z++){
        //qDebug() << 50 << z << product;
        if (product == 1 ){
            order = z;
            //qDebug() << 60 << "product" << product << "order" << order;
            return;
        }
        product = (  product * n ) % m_base;
    }
}

void	cDotPage::RemoveAll()
{
    for (int i = 0; i < m_Dots.size(); i++)
    {
        delete m_Dots.at(i);
    }
    m_Dots.clear();
}
cDot* cDotPage::GetAt(int n) {return m_Dots.at(n);}
int	  cDotPage::size() {return m_Dots.size();}


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
        //qDebug() << i << pDot->Number << pDot->Inverse << pDot->Order;
    }
    // count how often each Order occurs
    QList<QPair<int,int>>countList  ;
    QHashIterator<int, int> i(orderCounter);
    while (i.hasNext()) {
        i.next();
        countList.append(QPair<int,int>(i.key(),i.value())); // the "key"  is the order, the value is the count of them.

    }
    std::sort(countList.begin(), countList.end(), sortbysecond);
    /* Now they are sorted by how often each order occurs among the dots */

    QHash<int,int> order2colorcode;
    for (int i = 0; i < countList.size(); i++){
        order2colorcode[countList[i].first] = i;
    }

    for (int j = 0; j < size(); j++)
    {
        pDot = GetAt(j);
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
