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

    QSplineSeries *series() const;
    QValueAxis *axis() const;

public slots:
    void handleTimeout();

private:
    QTimer m_timer;
    QSplineSeries *m_series;
    QValueAxis *m_axis;
    qreal m_x;
    qreal m_y;
    qreal m_step;
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

public:
    virtual QSize sizeHint() const;

signals:

public slots:


private:
    QChartView *m_chartView;
    QGridLayout *m_layout;
    Chart *m_chart;
};

#endif // MEGASPLINECHART_H
