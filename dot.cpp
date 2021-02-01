#include <QColor>
#include <QDebug>
#include "dot.h"

cDot::cDot(int number, int  inverse, int order){
    Number = number;
    Inverse = inverse;
    Order = order;
    x = number;
    y = inverse;
    //qDebug() << "cDot constructor "<< 1 << display()<< 2;
}


QString cDot::display(){
    QString outstring;
    outstring = "x=" + QString::number(this->x) + " y=" + QString::number( this->y)
                             + " Number=" + QString::number(Number) + " Inverse=" + QString::number( Inverse);
    return outstring;
}
int cDot::getOrder(){
    return Order;
}

void cDot::setColorIndex(int index){
    ColorIndex = index;
}

