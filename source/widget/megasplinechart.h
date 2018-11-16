#ifndef MEGASPLINECHART_H
#define MEGASPLINECHART_H

#include <QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~Chart();
    void dataAppend(double value);

    QSplineSeries *series() const;
    QValueAxis *axis() const;

private:
    QSplineSeries *m_series;
    QValueAxis *m_axis;
    double m_x;
    double m_y;
    double m_step;
};


#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QtCharts/QChartView>

class MegaSplineChart : public QWidget
{
    Q_OBJECT
public:
    explicit MegaSplineChart(const QString &tittle = "", QWidget *parent = nullptr);

    ~MegaSplineChart();

    Chart* chart();
    QChartView* chartView();

    void dataAppend(double value);

public:
    virtual QSize sizeHint() const;

private:
    QChartView *m_chartView;
    QGridLayout *m_layout;
    Chart *m_chart;
};

#endif // MEGASPLINECHART_H
