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


cPrimeCanvas::cPrimeCanvas(MainWindow* main_window , QWidget* parent ):QWidget(parent)
{

    const int BASE = 2;
    setAttribute(Qt::WA_StaticContents);
    m_main_window = main_window;
    m_main_window->set_UI_base(BASE);

    margin       = 5;
    diameter     = 20;
    m_dotPage      = new cDotPage(BASE, this); //setBase(323);

    setStyleSheet("background-color:yellow;");


 };




void cPrimeCanvas::change_base(int newbase){
    m_main_window->compute_primes_and_factors(newbase+1);
    m_dotPage = new cDotPage(newbase, this);
    m_main_window->set_UI_base(newbase);
    // to do : either delete the old cDotPage, or keep it for later use.
    update();
}
void cPrimeCanvas::increment_base( ){
    change_base(m_dotPage->get_base() + 1);
}
void cPrimeCanvas::decrement_base( ){
    if ( m_dotPage->get_base() > 3){
        change_base(m_dotPage->get_base() - 1);
    }
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
    xunit = (width()-2*margin) / get_base();
}
void cPrimeCanvas::calculateYunit(){
    yunit = (height()-2*margin) / get_base();
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
    rect.setRect(local2absX(1), local2absY(1), local2absX(get_base()-1), local2absY(get_base()-1));
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
    int xMouse = abs2localX(event->position().x());
    int yMouse = abs2localY(event->position().y());
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
