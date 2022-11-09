#include <QtWidgets>
#include <QDebug>
#include <QPen>
#include <QVector>
#include "math.h"
#include "cprimecanvas.h"
#include "dotpage.h"
#include "mainwindow.h"
#include "dot.h"

QColor colorCode2qcolor (int colorcode);


cPrimeCanvas::cPrimeCanvas(QWidget * parent ):QWidget(parent)
{
    // Roots the widget to the top left even if resized
    //qDebug() << "Starting PrimeCanvas";
    setAttribute(Qt::WA_StaticContents);

    margin       = 5;
    diameter     = 20;
    m_factors.reserve(2000);
    m_factors.append( new QList<int> );
    m_factors.append( new QList<int> );
    m_factors.append( new QList<int> );
    m_factors[1]->append(1);
    m_factors[2]->append(2);
    m_primes.append(2);
    m_dotPage      = new cDotPage(3); //setBase(323);
};




void cPrimeCanvas::changeBase(int newbase){
    /*
    for (int i = 0; i < myMainWindow->getDotPageCollection()->size();i++){
        if (myMainWindow->getDotPageCollection()->at(i)->getBase() == newbase){
            dotPage = myMainWindow->getDotPageCollection()->at(i);
            return;
        }
    }
   */
    qDebug() << "ChangeBase in primecanvas; base: "<<getBase();
    computeFactors(newbase);
    m_dotPage = new cDotPage(newbase);
    myMainWindow->m_line_edit_base->setText(QString::number(newbase));
    update();

}


int cPrimeCanvas::abs2localX(int x){
   return (x - margin)/xunit;
}
int cPrimeCanvas::abs2localY(int y){
   return (y - margin)/yunit;
}
int cPrimeCanvas::local2absX(int x){
     return margin + xunit * x;
}
int cPrimeCanvas::local2absY(int y){
     return margin + yunit * y;
}
void cPrimeCanvas::calculateXunit(){
    xunit = (width()-2*margin) / Base();
}
void cPrimeCanvas::calculateYunit(){
    yunit = (height()-2*margin) / Base();
}
void cPrimeCanvas::paintEvent(QPaintEvent *event){
    calculateXunit();
    calculateYunit();
    if (xunit > yunit)
        setXunit(yunit);
    else {
        if (yunit > xunit)
            setYunit( xunit );
    }

    QPainter Painter(this);
    QPen pen(Qt::black);
    pen.setWidth(2);
    Painter.setPen(pen);

    QRect rect;
    rect.setRect(local2absX(1), local2absY(1), local2absX(Base()-1), local2absY(Base()-1));
    Painter.drawRect(rect);

    Painter.setBrush(QBrush("#c56c00"));
    cDot * pDot;
    //qDebug() << "PrimeCanvas: painting...number of dots" << dotPage.Dots.size();
    QList<cDot*>::iterator i;
    for (int i = 0; i < m_dotPage->GetDots()->size(); i++){
            pDot = m_dotPage->GetDots()->at(i);
            Painter.setBrush(QBrush(colorCode2qcolor(pDot->getColorIndex())));
            Painter.drawEllipse(local2absX(pDot->x ), local2absY (pDot->y),diameter,diameter);
            //qDebug() << "x" << local2absX(pDot->x) << "y" << local2absY(pDot->y) << "xunit" << xunit << "yunit"<<yunit;
    }
}
void cPrimeCanvas::mousePressEvent(QMouseEvent *event )
{
    int bestdistance = 64000;
    int distance;
    int xMouse = abs2localX(event->x());
    int yMouse = abs2localY(event->y());
    int bestNumber = -1;
    int bestInverse = -1;
    for (int i = 0; i < m_dotPage->GetDots()->size(); i++){
            cDot* pDot = m_dotPage->GetDots()->at(i);
            distance = int(pow(pDot->Number - xMouse,2) + pow(pDot->Inverse - yMouse,2));
            if (distance < bestdistance) {
                bestdistance = distance;
                bestNumber = pDot->Number;
                bestInverse = pDot->Inverse;
            }
    }
    qDebug() << bestNumber << bestInverse;
};
void cPrimeCanvas::mouseReleaseEvent(QMouseEvent *event )
{};

QColor colorCode2qcolor (int colorcode)
{
        switch(colorcode)
        {
        case 0:  {
             return QColor(0,0,0);}  // black
        case 1: {
            return QColor(0, 255, 0);}	//green
        case 2: {
            return QColor(0, 0, 255);}	// blue
        case 3: {
            return QColor(255, 255, 0);}	// yellow
        case 4: {
            return QColor(127, 255, 255);}	// light blue
        case 5: {
            return QColor(255, 127, 255);}	// violet
        case 6: {
            return QColor(255, 255, 127);}	//
        case 7: {
            return QColor(175, 175, 175);}	// gray
        case 8: {
            return QColor(100, 240, 240);}	// aqua
        case 9: {
            return QColor(240, 100, 240);}	// purple
        case 10: {
            return QColor(240, 240, 100);}	// sick yellow
        case 11: {
            return QColor(255, 175, 10);}	//
        case 12: {
            return QColor(255, 10, 175); }	//
        case 13: {
            return QColor(175, 10, 255); }	//
        case 14: {
            return QColor(175, 175, 10); }	//
        case 15: {
            return QColor(10, 175, 255); }	//
        case 16: {
            return QColor(10, 255, 175); }	//

        default: {
            return QColor(255, 255, 255);} // default is white
        }
}

void cPrimeCanvas::computeFactors(int upto_N){
    if ( upto_N < 2){
        return;
    }
    for (int  n = m_factors.size(); n <= upto_N; n++){
        foreach (int p, m_primes){
            if ( n < p * p ){               
                m_primes.append(n);
                QList<int> * newlist = new QList<int>;
                newlist->append(n);
                m_factors.append(newlist);
                break;
            }
            if (n % p == 0){
                QList<int> * newlist = new QList<int>;
                newlist ->append (p);
                newlist->append(*m_factors[n /  p] );
                m_factors.append(newlist);
                break;
            }
        }
    }



}
