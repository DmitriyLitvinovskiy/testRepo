#ifndef MAINUNIT_H
#define MAINUNIT_H

#include <QMainWindow>

#include "graph.h"

#include <QLabel>

namespace Ui
{
    class mainUnit;
}

using namespace GraphLib;

class mainUnit : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainUnit(QWidget *parent = 0);
    ~mainUnit();
private:
    graph *gp;
    Ui::mainUnit *ui;

    Shape *shape;
    Figure::figureType figure;


    QColor color;
    int lineWidth;

    QLabel *toolText;
    QLabel *toolIcon;
    QLabel *colorText;
    QLabel *colorIcon;

    void changeColorIcon(QColor c);
    void configureUI();
    void enableConnects();
private slots:
    void addLine();
    void addRect();
    void addEllipse();

    void colorWhite();
    void colorBlack();
    void colorRed();
    void colorBlue();
    void colorGreen();
    void colorGray();

    void changeWidth(int i);

    void drawFigure(Point x, Point y);
signals:
    void figureChanged(Figure::figureType type);
    void colorChanged(QColor color);
    void lineWidthChanged(int width);
};

#endif // MAINUNIT_H
