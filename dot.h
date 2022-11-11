#ifndef DOT_H
#define DOT_H


#include <QObject>
#include <QColor>

class cDot : public QObject
{    Q_OBJECT

public:
    int		Number;
    int		Inverse;
    int		Block;
    int		ClosestCornerBlock;
    int		Order;
    int		x;
    int		y;
    QColor  Color;
    int     ColorIndex; //this is an int, and is used to determine the color; all dots of the same Order have the same ColorIndex

public:
    cDot();
    cDot(int Number, int Inverse, int Order);
    //cDot(int Number, int Inverse, int Block, int ClosestCB);
    void SetClosestCornerBlock (int i );
     virtual  ~cDot();
    QString display();
/*    void	Serialize(CArchive&);
    void	SendToFile(ofstream&);
    void	ReadFromFile(ifstream&);
*/
    int		getOrder();
    int	    getColorIndex( ) {return ColorIndex;}
    void    setColorIndex(int );
};

#endif // DOT_H

