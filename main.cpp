#include "bode_plot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bode_plot w;
    w.show();
    return a.exec();
}
