#include "megasplinechart.h"

#include <QTime>
#include <QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series1(new QSplineSeries(this)),
    m_series2(new QSplineSeries(this)),
    m_axis(new QValueAxis),
    m_x(0),
    m_y1(0),
    m_y2(0),
    m_step(1)
{
    setAnimationOptions(QChart::SeriesAnimations);
    setMargins(QMargins(0,0,0,0));

    m_series1->setName("%");
    m_series2->setName("%");
    //    legend()->hide();

    addSeries(m_series1);
    addSeries(m_series2);

    createDefaultAxes();

    setAxisX(m_axis, m_series1);
    setAxisX(m_axis, m_series2);

    m_axis->setTickCount(6);
    axisX()->setRange(-10.0, 0);
    axisY()->setRange(0, 120.0);

    axisX()->setTitleText("[s]");

    m_series1->append(m_x, m_y1);
    m_series1->append(m_x, m_y2);
}

Chart::~Chart()
{

}

void Chart::dataAppend(double v1, double v2)
{
    m_x += m_step;
    m_y1 = v1;
    m_y2 = v2;

    m_x += m_step;
    m_series1->append(m_x, m_y1);
    m_series1->setName( QString::number(m_y1,'f',2) + " %");

    m_series2->append(m_x, m_y2);
    m_series2->setName( QString::number(m_y2,'f',2) + " %");

    if(qAbs(m_axis->min()-0) < 0.000001)
        axisX()->setRange(0, m_axis->max() + m_step);
    else
        axisX()->setRange(m_axis->min() + m_step, m_axis->max() + m_step);
}

QSplineSeries *Chart::series1() const
{
    return m_series1;
}

QSplineSeries *Chart::series2() const
{
    return m_series2;
}

QValueAxis *Chart::axis() const
{
    return m_axis;
}



//////////////////////////////////////////////////////////
MegaSplineChart::MegaSplineChart(const QString &tittle, QWidget *parent) : QWidget(parent),
    m_chartView(new QChartView),
    m_layout(new QGridLayout(this)),
    m_chart(new Chart)
{
    m_chartView->setChart(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_layout->addWidget(m_chartView);
    m_layout->setMargin(0);

    setLayout(m_layout);

    m_chart->setTitle(tittle);
}

MegaSplineChart::~MegaSplineChart()
{
    delete m_chart;
    delete m_chartView;
    delete m_layout;
}

Chart *MegaSplineChart::chart()
{
    return m_chart;
}

QChartView *MegaSplineChart::chartView()
{
    return m_chartView;
}

QSize MegaSplineChart::sizeHint() const
{ return QSize(200,50); }

void MegaSplineChart::dataAppend(double v1, double v2)
{
    m_chart->dataAppend(v1, v2);
}
