#include "bode_plot.h"
#include "ui_bode_plot.h"
#include <QVector>
#include <QMessageBox>
#include <cmath>
#include <complex>
#include <QFileDialog>
#include <QPixmap>
#include <QSvgGenerator>
#include <Eigen/Dense>
#include <unsupported/Eigen/Polynomials>

bode_plot::bode_plot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bode_plot)
{
    ui->setupUi(this);

    // custom_plot   ---> Amplitude
    // custom_plot_2 ---> Phase
    ui->custom_plot->addGraph();
    ui->custom_plot_2->addGraph();

    // default text and style for stabilityLabel(output for stability.)
    ui->stabilityLabel->setText("No analysis performed.");
    ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;      \
                                                border: 1px solid black; \
                                                padding: 5px;            \
                                                color: black;            \
                                                background-color:        \
                                                lightgray; }");

    // stylesheet for numerator input
    ui->numerator_input->setStyleSheet("QLineEdit { border-radius: 2px;     \
                                                    border: 1px solid grey; \
                                                    padding: 1px;           \
                                                    color: green;           \
                                                    background-color:       \
                                                    lightyellow;            \
                                                    font-size: 13px; }");
    ui->numerator_input->setPlaceholderText("Coeffs larger to smaller");

    // stylesheet for denominator input
    ui->denominator_input->setStyleSheet("QLineEdit { border-radius: 2px;            \
                                                      border: 1px solid grey;        \
                                                      padding: 1px;                  \
                                                      color: green;                  \
                                                      background-color: lightyellow; \
                                                      font-size: 13px; }");
    ui->denominator_input->setPlaceholderText("Coeffs larger to smaller");
}

bode_plot::~bode_plot()
{
    delete ui;
}

// pushButton ---> plot(button on layout)
void bode_plot::on_pushButton_clicked()
{
    // Setting the numerator and denominator from the input fields
    QString numeratorStr   = ui->numerator_input->text();
    QString denominatorStr = ui->denominator_input->text();

    // Converting the input strings to QVector<double>
    QVector<double> numerator;
    QVector<double> denominator;

    bool ok = true;

    // Checking for empty input fields
    if (numeratorStr.trimmed().isEmpty() || denominatorStr.trimmed().isEmpty()) {
        ui->stabilityLabel->setText("Error: Numerator or Denominator input is empty.");
        ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;          \
                                                    border: 2px solid red;       \
                                                    padding: 5px;                \
                                                    color: red;                  \
                                                    background-color: lightgray; }");
        return;
    }

    // Checking for valid numerator
    for (const QString &num : numeratorStr.split(' ', Qt::SkipEmptyParts)) {
        numerator.append(num.toDouble(&ok));
        if (!ok) {
            ui->stabilityLabel->setText("Error: Invalid numerator coefficients.");
            ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;          \
                                                        border: 1px solid red;       \
                                                        padding: 5px;                \
                                                        color: red;                  \
                                                        background-color: lightgray; }");
            return;
        }
    }

    // checking for valid denominator
    for (const QString &den : denominatorStr.split(' ', Qt::SkipEmptyParts)) {
        double denCoeff = den.toDouble(&ok);
        if (!ok || denCoeff == 0) {
            ui->stabilityLabel->setText("Error: Invalid or zero denominator coefficients.");
            ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;          \
                                                        border: 1px solid red;       \
                                                        padding: 5px;                \
                                                        color: red;                  \
                                                        background-color: lightgray; }");
            return;
        }
        denominator.append(denCoeff);
    }

    // Plot the Bode plot
    plotBode(numerator, denominator);

    // updating the status of stability
    updateStabilityStatus(denominator);
}

// pushButton_2 ---> Clear(button on the layout)
void bode_plot::on_pushButton_2_clicked()
{
    // need to clear plots after clear button is clicked
    clearPlots();

    // Clear and reset the stability status as well
    ui->stabilityLabel->setText("No analysis performed.");
    ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;      \
                                                border: 1px solid black; \
                                                padding: 5px;            \
                                                color: black;            \
                                                background-color: lightgray; }");
}

// to plot the ampitude and phase plots
void bode_plot::plotBode(const QVector<double> &numerator, const QVector<double> &denominator)
{
    // Frequency range for Bode plot
    QVector<double> frequencies;
    const double minFreq    = 1e0; // starting of X-axis
    const double maxFreq    = 1e5; // ending of X-axis
    const double stepFactor = 1.2;

    int numSteps = std::log10(maxFreq / minFreq) / std::log10(stepFactor) + 1;
    for (int i = 0; i < numSteps; ++i) {
        double w = minFreq * std::pow(stepFactor, i);
        frequencies.append(w);
    }

    // amplitude and phase Calculation
    QVector<double> amplitude(frequencies.size());
    QVector<double> phase(frequencies.size());

    for (int i = 0; i < frequencies.size(); ++i) {
        std::complex<double> jw(0, frequencies[i]);

        // Calculation of numerator and denominator as polynomials of jw
        std::complex<double> num(0, 0);
        std::complex<double> den(0, 0);

        for (int j = 0; j < numerator.size(); ++j) {
            num += numerator[j] * std::pow(jw, numerator.size() - j - 1);
        }

        for (int j = 0; j < denominator.size(); ++j) {
            den += denominator[j] * std::pow(jw, denominator.size() - j - 1);
        }

        std::complex<double> H = num / den;

        amplitude[i] = 20 * std::log10(std::abs(H));
        phase[i]     = std::arg(H) * 180 / M_PI;
    }

    // Plot the amplitude and phase
    ui->custom_plot->graph(0)->setData(frequencies, amplitude);
    ui->custom_plot_2->graph(0)->setData(frequencies, phase);

    // axis ranges and other plot properties
    // for amplitude plot
    ui->custom_plot->yAxis->setLabel("Magnitude (dB)");
    ui->custom_plot->xAxis->setLabel("Frequency (w)");
    ui->custom_plot->xAxis->setRange(1e0, 1e5);  // X-axis range {1 to 100000}
    ui->custom_plot->yAxis->setRange(-100, 100); // Y-axis range
    ui->custom_plot->xAxis->setLabelColor(Qt::blue);
    ui->custom_plot->yAxis->setLabelColor(Qt::blue);
    ui->custom_plot->xAxis->grid()->setPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
    ui->custom_plot->yAxis->grid()->setPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
    ui->custom_plot->xAxis->grid()->setSubGridPen(QPen(QColor(220, 220, 220), 0, Qt::DotLine));
    ui->custom_plot->yAxis->grid()->setSubGridPen(QPen(QColor(220, 220, 220), 0, Qt::DotLine));

    // for phase plot
    ui->custom_plot_2->yAxis->setLabel("Phase (deg)");
    ui->custom_plot_2->xAxis->setLabel("Frequency (w)");
    ui->custom_plot_2->xAxis->setRange(1e0, 1e5); // X-axis range
    ui->custom_plot_2->yAxis->setRange(-180, 180); // Y-axis range
    ui->custom_plot_2->xAxis->setLabelColor(Qt::blue);
    ui->custom_plot_2->yAxis->setLabelColor(Qt::blue);
    ui->custom_plot_2->xAxis->grid()->setPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
    ui->custom_plot_2->yAxis->grid()->setPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
    ui->custom_plot_2->xAxis->grid()->setSubGridPen(QPen(QColor(220, 220, 220), 0, Qt::DotLine));
    ui->custom_plot_2->yAxis->grid()->setSubGridPen(QPen(QColor(220, 220, 220), 0, Qt::DotLine));

    ui->custom_plot->rescaleAxes();
    ui->custom_plot_2->rescaleAxes();

    ui->custom_plot->replot();
    ui->custom_plot_2->replot();
}

// to save the plots(remember to add .jpg or .svg with the output file name)
void bode_plot::savePlot(QCustomPlot *plot, const QString &filename)
{
    QPixmap pixmap(plot->size());
    plot->render(&pixmap);

    pixmap.save(filename);
}

// first save burron for saving amplitude plot
void bode_plot::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Images (*.jpg *.svg);;All Files (*)");
    if (fileName.isEmpty()) return;

    if (fileName.endsWith(".jpg") || fileName.endsWith(".jpeg")) {
        savePlot(ui->custom_plot, fileName);
    } else if (fileName.endsWith(".svg")) {
        QSvgGenerator generator;
        generator.setFileName(fileName);
        generator.setSize(QSize(ui->custom_plot->width(), ui->custom_plot->height()));
        generator.setViewBox(QRect(0, 0, ui->custom_plot->width(), ui->custom_plot->height()));
        generator.setTitle("Bode Plot");

        QPainter painter;
        painter.begin(&generator);

        ui->custom_plot->render(&painter);

        painter.end();
    } else {
        QMessageBox::warning(this, "Save Error", "Unsupported file format");
    }
}

// second save button for saving phase plot
void bode_plot::on_saveButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Images (*.jpg *.svg);;All Files (*)");
    if (fileName.isEmpty()) return;

    if (fileName.endsWith(".jpg") || fileName.endsWith(".jpeg")) {
        savePlot(ui->custom_plot_2, fileName);
    } else if (fileName.endsWith(".svg")) {
        QSvgGenerator generator;
        generator.setFileName(fileName);
        generator.setSize(QSize(ui->custom_plot_2->width(), ui->custom_plot_2->height()));
        generator.setViewBox(QRect(0, 0, ui->custom_plot_2->width(), ui->custom_plot_2->height()));
        generator.setTitle("Bode Plot");

        QPainter painter;
        painter.begin(&generator);

        ui->custom_plot_2->render(&painter);

        painter.end();
    } else {
        QMessageBox::warning(this, "Save Error", "Unsupported file format");
    }
}

// after clicking on clear button
void bode_plot::clearPlots()
{
    ui->custom_plot->graph(0)->data()->clear();
    ui->custom_plot_2->graph(0)->data()->clear();

    ui->custom_plot->replot();
    ui->custom_plot_2->replot();
}

// finding polynomial roots using Eigen's PolynomialSolver
Eigen::VectorXcd polyroots(const Eigen::VectorXd &coefficients) {
    Eigen::PolynomialSolver<double, Eigen::Dynamic> solver;
    solver.compute(coefficients);
    return solver.roots();
}

// checking stability of the T(s)
bool bode_plot::isStable(const QVector<double> &denominator)
{
    Eigen::VectorXd denom(denominator.size());
    for (int i = 0; i < denominator.size(); ++i) {
        denom[i] = denominator[i];
    }

    // Finding the roots of the denominator polynomial
    Eigen::VectorXcd roots = polyroots(denom);

    for (int i = 0; i < roots.size(); ++i) {
        if (roots[i].real() >= 0) {
            return false; // At least one root has a non-negative real part
        }
    }

    // If all roots have negative real parts, the system is stable
    return true;
}

// part for the output of stability
void bode_plot::updateStabilityStatus(const QVector<double> &denominator)
{
    if (isStable(denominator)) {
        ui->stabilityLabel->setText("The transfer function is stable.");
        ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;      \
                                                    border: 1px solid green; \
                                                    padding: 5px;            \
                                                    color: green;            \
                                                    background-color: lightgray; }");

    } else {
        ui->stabilityLabel->setText("The transfer function is unstable.");
        ui->stabilityLabel->setStyleSheet("QLabel { border-radius: 5px;    \
                                                    border: 1px solid red; \
                                                    padding: 5px;          \
                                                    color: red;            \
                                                    background-color: lightgray; }");
    }
}
