#include <QtWidgets>
#include <QDebug>
#include <QPen>
#include "math.h"
#include "cprimecanvas.h"
#include "dot.h"


cPrimeCanvas::cPrimeCanvas(QWidget * parent ):QWidget(parent)
{
    // Roots the widget to the top left even if resized
    qDebug() << "Starting PrimeCanvas";
    setAttribute(Qt::WA_StaticContents);
    dotPage.setBase(19);
    margin = 5;
    diameter = 10;
    qDebug()  << "Ending PrimeCanvas " <<dotPage.Dots.size() ;


};

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

    qDebug() << "Widget height" << height();

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
    for (int i = 0; i < dotPage.GetDots()->size(); i++){
            pDot = dotPage.GetDots()->at(i);
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
    int bestNumber, bestInverse;
    for (int i = 0; i < dotPage.GetDots()->size(); i++){
            cDot* pDot = dotPage.GetDots()->at(i);
            distance = pow(pDot->Number - xMouse,2) + pow(pDot->Inverse - yMouse,2);
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

