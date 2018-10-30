#include "megasplinechart.h"

#include <QTime>
#include <QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(new QSplineSeries(this)),
    m_axis(new QValueAxis),
    m_x(0),
    m_y(0),
    m_step(1)
{
    setAnimationOptions(QChart::SeriesAnimations);
    setMargins(QMargins(0,0,0,0));

    m_series->setName("%");
    //    legend()->hide();

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);

    m_axis->setTickCount(6);
    axisX()->setRange(-10.0, 0);
    axisY()->setRange(0, 100.0);

    axisX()->setTitleText("[min]");

    m_series->append(m_x, m_y);

    qsrand((uint) QTime::currentTime().msec());
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_timer.setInterval(1000 * 60); //轮询时间周期
    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    m_x += m_step;

    //FIXME:在此处替换为实际的查询函数
    m_y = qrand() % 101;

    m_x += m_step;
    m_series->append(m_x, m_y);
    m_series->setName( QString::number(m_y,'f',2) + " %");

    if(qAbs(m_axis->min()-0) < 0.000001)
        axisX()->setRange(0, m_axis->max() + m_step);
    else
        axisX()->setRange(m_axis->min() + m_step, m_axis->max() + m_step);
}

QValueAxis *Chart::axis() const
{
    return m_axis;
}

QSplineSeries *Chart::series() const
{
    return m_series;
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
