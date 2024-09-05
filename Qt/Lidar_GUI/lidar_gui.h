#ifndef LIDAR_GUI_H
#define LIDAR_GUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Lidar_GUI;
}
QT_END_NAMESPACE

class Lidar_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Lidar_GUI(QWidget *parent = nullptr);

    void run(double phase);

    ~Lidar_GUI();

private:
    Ui::Lidar_GUI *ui;
};
#endif // LIDAR_GUI_H
