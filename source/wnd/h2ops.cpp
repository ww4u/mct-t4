#include "h2ops.h"
#include "ui_h2ops.h"

#include "megasplinechart.h"

H2Ops::H2Ops(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Ops)
{
    ui->setupUi(this);

    MegaSplineChart *m_splineChart1 = new MegaSplineChart("spline1 [%]");
    MegaSplineChart *m_splineChart2 = new MegaSplineChart("spline2 [%]");

    m_splineChart1->chart()->series()->setPen(QPen(Qt::blue));
    m_splineChart2->chart()->series()->setPen(QPen(Qt::red));

    ui->horizontalLayout_2->setMargin(0);
    ui->horizontalLayout_2->setSpacing(1);

    ui->horizontalLayout_2->addWidget(m_splineChart1);
    ui->horizontalLayout_2->addWidget(m_splineChart2);
    ui->horizontalLayout_2->addStretch();

}

H2Ops::~H2Ops()
{
    delete ui;
}
