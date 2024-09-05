#include "lidar_gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lidar_GUI w;
    w.show();

    double phase = 0;

    while(1){
        w.run(phase);
        phase+=0.01;
        w.update();
    }
    //return a.exec();
}
