#include<QPointF>
#include<QVector>
#include<QBrush>
#include<QTimer>
#include<QDebug>

#include"myview.h"
#include"battlescene.h"
#include"square.h"

extern Myview* view;
Square::Square()
{
    square_Color=QColor(210,250,250);
    setRect(0,0,75,75);
    timer1 = new Mytimer();
    setAcceptHoverEvents(true);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(square_Color);
    setBrush(brush);
}

void Square::changeColorMode()
{
    if(getS_shining()){return;}
    timer1->settimes(0);
    timer1->setInterval(50);
    timer1->start();   
    connect(timer1,SIGNAL(timeout()),this,SLOT(setChangeColor()));
}

void Square::setChangeColor()
{
    timer1->addtimes(20);
    int t = (timer1->gettimes()*50);
    int light=50;
    qreal a = static_cast<double>(light)*4/static_cast<double>(1000*1000);
    int rgb = -a*(t-500)*(t-500)+light;
    Square_brush.setStyle(Qt::SolidPattern);
    Square_brush.setColor(QColor(square_Color.red()+rgb>255?255:square_Color.red()+rgb,square_Color.green()+rgb>255?255:square_Color.green()+rgb
                                                                                      ,square_Color.blue()+rgb>255?255:square_Color.blue()+rgb));
    setBrush(Square_brush);

}

void Square::setSquareColor()
{
    Square_brush.setStyle(Qt::SolidPattern);
    Square_brush.setColor(square_Color);
    setBrush(Square_brush);
}

bool Square::getS_shining() const
{
    return S_shining;
}

void Square::setS_shining(bool value)
{
    S_shining = value;
}

void Square::backToNormal()
{
    setSquareColor();
    timer1->stop();
    timer1->disconnect();

}

void Square::lighter()
{
    QColor lighterColor;
    int light=50;
    int red = square_Color.red()+light>255?255: square_Color.red()+light;
    int green = square_Color.green()+light>255?255: square_Color.green()+light;
    int blue = square_Color.blue()+light>255?255: square_Color.blue()+light;
    lighterColor=QColor(red,green,blue);
    QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(lighterColor);
        setBrush(brush);
}

//void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    if(collidingItems().size()==2)
//    {
//        emit ToBS_changeColorMode(x(),y());
//    }
//}

void Square::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
   lighter();
}

void Square::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(square_Color);
        setBrush(brush);
}

