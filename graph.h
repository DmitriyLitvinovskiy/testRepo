#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

//figure enum
class Figure{
public:
    enum figureType{
        line,
        rectangle,
        ellipse
    };
};

//point
class Point
{
public:
    Point(int x, int y):mX(x), mY(y){}
    Point():mX(0),mY(0){}

    int x() const{return mX;}
    int y() const{return mY;}

    void setX(int x){mX = x;}
    void setY(int y){mY = y;}

    friend bool operator ==(Point left, Point righr);
    friend bool operator !=(Point left, Point right);
private:
    int mX;
    int mY;
};

//GraphLib
namespace GraphLib
{
//Shape
    class Shape
    {
    public:
        void draw();
        virtual void move(int dx, int dy);//move all items
        QGraphicsItem *at(int i);//return item from items[i]

        int size() const;//items.size()
        void setColor(QColor color);
        void setLineWidth(int i);

        virtual ~Shape();
    protected:
        Shape();
        virtual void drawLines() = 0;//derevative figures are drawn differently

        QVector<QGraphicsItem*> items;
        QPen pen;//contain line width and line color
    private:
        Shape(const Shape&);//prevent copy
        Shape& operator=(const Shape&);

        QColor lineColor;
        int lineWidth;
    };

//Line
    class Line : public Shape
    {
    public:
        Line(Point x, Point y) : mP1(x),mP2(y){}
        void drawLines();
    private:
        Point mP1;
        Point mP2;
    };

//Rectangle
    class Rectangle : public Shape
    {
    public:
        Rectangle(Point xy, int ww, int hh);
        Rectangle(Point x, Point y);

        int height() const { return h; }
        int width() const { return w; }
    private:
        void drawLines();
        int h;    // height
        int w;    // width
        Point mXY;
    };

//Ellipse
    class Ellipse : public Shape
    {
    public:
        Ellipse(Point p, int w, int h):mP(p), mW(w), mH(h){}
    private:
        void drawLines();

        Point mP;
        int mW;
        int mH;
    };
}//of namespace GraphLib

class graph : public QGraphicsScene
{
    Q_OBJECT
public:
    graph();
    ~graph();

    void attach(GraphLib::Shape *s);//attach to scene
    void detach(GraphLib::Shape *s);//detach from shcene
private:
    Point start;
    Point end;
    Figure::figureType figure;
    QColor lineColor;
    int lineWidth;
    GraphLib::Shape *temp;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QVector<GraphLib::Shape *> shapes;//contains pointers on all created shapes
public slots:
    void setFigure(Figure::figureType type);
    void setColor(QColor color);
    void setWidth(int i);
signals:
    void mouseRelease(Point x, Point y);
};
#endif // GRAPH_H
