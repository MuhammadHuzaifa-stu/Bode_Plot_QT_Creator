#ifndef BODE_PLOT_H
#define BODE_PLOT_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class bode_plot;
}
QT_END_NAMESPACE

class bode_plot : public QMainWindow
{
    Q_OBJECT

public:
    bode_plot(QWidget *parent = nullptr);
    ~bode_plot();

private slots:
    void on_pushButton_clicked();   // plot (button)
    void on_pushButton_2_clicked(); // clear (button)
    void on_saveButton_clicked();   // 1st save (button) for saving amplitude
    void on_saveButton_2_clicked(); // 2nd save (button) for saving phase
    void updateStabilityStatus(const QVector<double> &denominator); // for updating stability status

private:
    Ui::bode_plot *ui;
    void plotBode(const QVector<double> &numerator, const QVector<double> &denominator);
    void clearPlots();
    void savePlot(QCustomPlot *plot, const QString &filename);
    bool isStable(const QVector<double> &denominator);
};
#endif // BODE_PLOT_H
