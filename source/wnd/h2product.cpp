#include "h2product.h"
#include "ui_h2product.h"

#include <QThread>

H2Product::H2Product(QString strDevInfo, QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Product)
{
    ui->setupUi(this);

    setFocusName( "Product" );

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

void H2Product::on_pushButton_status_clicked()
{
    emit signal_online_clicked(m_IP);
}

void H2Product::change_online_status(bool bl)
{

    if(bl){
//        ui->pushButton_status->setStyleSheet("border-image: url(:/res/image/h2product/offline.png);");
        ui->pushButton_status->setIcon(QIcon(":/res/image/h2product/online.png"));
//        ui->pushButton_status->setText(tr("    online    "));
        ui->pushButton_status->setToolTip(tr("click here to close device"));
    }else{
//        ui->pushButton_status->setStyleSheet("border-image: url(:/res/image/h2product/offline.png);");
        ui->pushButton_status->setIcon(QIcon(":/res/image/h2product/offline.png"));
//        ui->pushButton_status->setText(tr("    offline    "));
        ui->pushButton_status->setToolTip(tr("click here to open device"));
    }
}

int H2Product::readDeviceConfig()
{
    return 0;
}

int H2Product::writeDeviceConfig()
{

    return 0;
}

int H2Product::loadConfig()
{

    return 0;
}

int H2Product::saveConfig()
{

    return 0;
}

void H2Product::updateShow()
{

}

void H2Product::translateUI()
{
    ui->retranslateUi(this);
}
