#include "lidar_gui.h"
#include "ui_lidar_gui.h"

Lidar_GUI::Lidar_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lidar_GUI)
{
    ui->setupUi(this);
}

Lidar_GUI::~Lidar_GUI()
{
    delete ui;
}

void Lidar_GUI::run(double phase){

    QVector<double> x(100),y(100);
    for(int i=0; i<x.size(); i++){
        x[i] = 7. * static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        y[i] = sin(x[i] + phase);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x,y);
    ui->widget->xAxis->setRange(0,7);
    ui->widget->yAxis->setRange(0,1);

    phase+=0.1;
    ui->widget->replot();
}
