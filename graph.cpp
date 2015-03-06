#include "graph.h"

using namespace GraphLib;

graph::graph()
{
    figure = Figure::line;
    lineColor = Qt::black;
    lineWidth = 1;

    temp = nullptr;
}

void graph::attach(Shape *s)
{
    s->draw();
    for(int i = 0; i < s->size(); i++)
        addItem(s->at(i));

    shapes.append(s);
}

void graph::detach(Shape *s)
{
    for(int i = 0; i < s->size(); i++)
        removeItem(s->at(i));
}

graph::~graph()
{
    delete temp;

    //delete all items

    if(!shapes.empty())
        for(auto i : shapes)
            delete i;

}

void graph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    start.setX(event->scenePos().x());
    start.setY(event->scenePos().y());
}

void graph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     end.setX(event->scenePos().x());
     end.setY(event->scenePos().y());
     emit mouseRelease(start, end);
}

void graph::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (temp != nullptr)
        detach(temp);

    switch(figure)
    {
    case Figure::line:
        temp = new Line(Point(start.x(),start.y()),Point(event->scenePos().x(),event->scenePos().y()));
        break;
    case Figure::rectangle:
        temp = new Rectangle(Point(start.x(),start.y()),Point(event->scenePos().x(),event->scenePos().y()));
        break;
    case Figure::ellipse:
        temp = new Ellipse(Point(start.x(),start.y()),
                           event->scenePos().x() - start.x(), event->scenePos().y() - start.y());
        break;
    }
    temp->setColor(lineColor);
    temp->setLineWidth(lineWidth);
    attach(temp);
}

void graph::setFigure(Figure::figureType type)
{
    figure = type;
}

void graph::setColor(QColor color)
{
    lineColor = color;
}

void graph::setWidth(int i)
{
    lineWidth = i;
}

//Point
bool operator ==(Point left, Point righr)
{
    return ((left.x() == righr.x()) && (left.y() == righr.y()));
}

bool operator !=(Point left, Point right)
{
    return !(left == right);
}

//Shape
Shape::Shape()
{
    lineWidth = 1;
    lineColor = Qt::black;

    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
}

Shape::~Shape()
{
    if(!items.empty())
        for(auto i : items)
            delete i;
}

void Shape::draw()
{
    pen.setColor(lineColor);
    pen.setWidth(lineWidth);
    drawLines();
}

void Shape::move(int dx, int dy)
{
    for(auto i : items)
        i->moveBy(dx,dy);
}

QGraphicsItem *Shape::at(int i){return items.at(i);}

int Shape::size() const {return items.size();}

void Shape::setColor(QColor color)
{
    lineColor = color;
}

void Shape::setLineWidth(int i)
{
    lineWidth = i;
}

//Line
void Line::drawLines()
{
    QGraphicsLineItem *it = new QGraphicsLineItem(mP1.x(), mP1.y(), mP2.x(), mP2.y());
    it->setPen(pen);
    items.append(it);
}

//Rectangle
Rectangle::Rectangle(Point xy, int ww, int hh) : h(hh),w(ww),mXY(xy)
{
//    if (h<=0 || w<=0)
//        qDebug()<<"Bad rectangle: non-positive side";
}

Rectangle::Rectangle(Point x, Point y) : h(y.x()-x.x()), w(y.y()-x.y()), mXY(x)
{
//    if (h<=0 || w<=0)
//        qDebug()<<"Bad rectangle: non-positive width or height";
}

void Rectangle::drawLines()
{
    QGraphicsRectItem *it = new QGraphicsRectItem(mXY.x(), mXY.y(), h, w);
    it->setPen(pen);
    items.append(it);
}

//Ellipse
void Ellipse::drawLines()
{
    QGraphicsEllipseItem *it = new QGraphicsEllipseItem(mP.x(), mP.y(), mW, mH);
    it->setPen(pen);
    items.append(it);
}
