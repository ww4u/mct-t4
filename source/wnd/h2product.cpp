#include "h2product.h"
#include "ui_h2product.h"

#include <QThread>

H2Product::H2Product(QString strDevInfo, QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Product)
{
    ui->setupUi(this);

    setName( "product" );

    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);
    this->m_IP      = strListDev.at(0);
    this->m_Type    = strListDev.at(2);
    this->m_SN      = strListDev.at(3);
    this->m_Version = strListDev.at(4);

    ui->label_ip->setText(this->m_IP);
    ui->label_sn->setText(this->m_SN);
    ui->label_type->setText(this->m_Type);
    ui->label_version->setText(this->m_Version);

    change_online_status(false);
}

H2Product::~H2Product()
{
    delete ui;
}

int H2Product::setApply()
{
//    int ret = -1;
//    char strIDN[1024] = "";
//    ret = mrhtIdn_Query(mViHandle,strIDN,sizeof(strIDN));
//    qDebug() << "H2Product" << m_IP << mViHandle << strIDN;
    return 0;
}

void H2Product::loadXmlConfig()
{

}

void H2Product::change_online_status(bool bl)
{
    if(bl)
    {
        ui->toolButton_status->setIcon(QIcon(":/res/image/h2product/online.png"));
        ui->toolButton_status->setText(tr("online"));
        ui->toolButton_status->setToolTip(tr("click here to close device"));
    }
    else
    {
        ui->toolButton_status->setIcon(QIcon(":/res/image/h2product/offline.png"));
        ui->toolButton_status->setText(tr("offline"));
        ui->toolButton_status->setToolTip(tr("click here to open device"));
    }
}

void H2Product::on_toolButton_status_clicked()
{
    emit signal_online_clicked(m_IP);
}
