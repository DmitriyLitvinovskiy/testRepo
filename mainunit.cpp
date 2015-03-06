#include "mainunit.h"
#include "ui_mainunit.h"

mainUnit::mainUnit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainUnit)
{
    ui->setupUi(this);

    gp = new graph();

    ui->graphicsView->setScene(gp);

    figure = Figure::line;//default figure
    color = Qt::black;//default color
    lineWidth = ui->lineWidth->value();//1 by default

    toolText = new QLabel("Current tool ",this);
    toolIcon = new QLabel(this);

    colorText = new QLabel("Current color ");
    colorIcon = new QLabel(this);

    //bounding rectangle of the scene
    gp->setSceneRect(0,0,ui->centralWidget->width(), ui->centralWidget->height());

    configureUI();

    enableConnects();
}
mainUnit::~mainUnit()
{
    delete ui;
}

void mainUnit::configureUI()
{
    QPixmap pix(32,32);
    QIcon icon;

    pix.fill(Qt::black);
    icon.addPixmap(pix);
    ui->tb_black->setIcon(icon);

    pix.fill(Qt::white);
    icon.addPixmap(pix);
    ui->tb_white->setIcon(icon);

    pix.fill(Qt::red);
    icon.addPixmap(pix);
    ui->tb_red->setIcon(icon);

    pix.fill(Qt::blue);
    icon.addPixmap(pix);
    ui->tb_blue->setIcon(icon);

    pix.fill(Qt::green);
    icon.addPixmap(pix);
    ui->tb_green->setIcon(icon);

    pix.fill(Qt::gray);
    icon.addPixmap(pix);
    ui->tb_gray->setIcon(icon);

    ui->lineWidth->setValue(1);
    ui->lineWidth->setMinimum(1);
    ui->lineWidth->setMaximum(10);

    toolIcon->setMaximumHeight(16);
    toolIcon->setMaximumWidth(16);
    toolIcon->setPixmap(QPixmap(":/buttonIcons/line.png").scaled(16,16));

    QPixmap p(16,16);
    p.fill(Qt::black);
    colorIcon->setPixmap(p);

    ui->statusBar->addWidget(toolText);
    ui->statusBar->addWidget(toolIcon);
    ui->statusBar->addWidget(colorText);
    ui->statusBar->addWidget(colorIcon);
}

void mainUnit::enableConnects()
{
    connect(ui->clear, &QToolButton::clicked, gp, &graph::clear);

    connect(ui->tb_line,&QToolButton::clicked,this, &mainUnit::addLine);
    connect(ui->tb_rect,&QToolButton::clicked,this, &mainUnit::addRect);
    connect(ui->tb_elps,&QToolButton::clicked,this, &mainUnit::addEllipse);

    connect(ui->tb_white, &QToolButton::clicked, this, &mainUnit::colorWhite);
    connect(ui->tb_black, &QToolButton::clicked, this, &mainUnit::colorBlack);
    connect(ui->tb_green, &QToolButton::clicked, this, &mainUnit::colorGreen);
    connect(ui->tb_red, &QToolButton::clicked, this, &mainUnit::colorRed);
    connect(ui->tb_gray, &QToolButton::clicked, this, &mainUnit::colorGray);
    connect(ui->tb_blue, &QToolButton::clicked, this, &mainUnit::colorBlue);

    connect(ui->lineWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &mainUnit::changeWidth);

    connect(gp, &graph::mouseRelease, this, &mainUnit::drawFigure);
    connect(this, &mainUnit::figureChanged, gp, &graph::setFigure);
    connect(this, &mainUnit::colorChanged, gp, &graph::setColor);
    connect(this, &mainUnit::lineWidthChanged, gp, &graph::setWidth);
}

void mainUnit::changeColorIcon(QColor c)
{
    QPixmap p(16,16);
    p.fill(c);
    colorIcon->setPixmap(p);
}


void mainUnit::addLine()
{
    figure = Figure::line;
    toolIcon->setPixmap(QPixmap(":/buttonIcons/line.png").scaled(16,16));
    emit figureChanged(figure);
}

void mainUnit::addRect()
{
    figure = Figure::rectangle;
    toolIcon->setPixmap(QPixmap(":/buttonIcons/rectangle.png").scaled(16,16));
    emit figureChanged(figure);
}

void mainUnit::addEllipse()
{
    figure = Figure::ellipse;
    toolIcon->setPixmap(QPixmap(":/buttonIcons/ellipse.png").scaled(16,16));
    emit figureChanged(figure);
}

void mainUnit::colorWhite()
{
    color = Qt::white;
    changeColorIcon(color);
    emit colorChanged(color);
}

void mainUnit::colorBlack()
{
    color = Qt::black;
    changeColorIcon(color);
    emit colorChanged(color);
}

void mainUnit::colorRed()
{
    color = Qt::red;
    changeColorIcon(color);
    emit colorChanged(color);
}

void mainUnit::colorBlue()
{
    color = Qt::blue;
    changeColorIcon(color);
    emit colorChanged(color);
}

void mainUnit::colorGreen()
{
    color = Qt::green;
    changeColorIcon(color);
    emit colorChanged(color);
}

void mainUnit::colorGray()
{
    color = Qt::gray;
    changeColorIcon(color);
    emit colorChanged(color);
}

void mainUnit::changeWidth(int i)
{
    lineWidth = i;
    emit lineWidthChanged(lineWidth);
}

void mainUnit::drawFigure(Point x, Point y)
{
    switch(figure)
    {
    case Figure::line:
        shape = new Line(x,y);
        emit figureChanged(Figure::line);
        break;
    case Figure::rectangle:
        shape = new Rectangle(x,y);
        emit figureChanged(Figure::rectangle);
        break;
    case Figure::ellipse:
        shape = new Ellipse(x, y.x() - x.x(), y.y() - x.y());
        emit figureChanged(Figure::ellipse);
        break;
    }
    shape->setColor(color);
    shape->setLineWidth(lineWidth);
    gp->attach(shape);
}
