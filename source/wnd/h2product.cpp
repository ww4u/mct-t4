#include "h2product.h"
#include "ui_h2product.h"

H2Product::H2Product(QString strDevInfo, QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Product)
{
    ui->setupUi(this);

    setFocusName( "Product" );

    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);

    QString strIP;
    QString strID = strListDev.at(0);
    if(strID.left(3) == "USB")
    {
        QStringList lst = strID.split('_', QString::SkipEmptyParts);
        strIP = lst.at(1) + "_" + lst.at(2);
    }
    else{
        strIP = strID;
    }

    this->m_IP      = strIP;
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
        ui->pushButton_status->setIcon(QIcon(":/res/image/h2product/connect.png"));
    }else{
        ui->pushButton_status->setIcon(QIcon(":/res/image/h2product/disconnect.png"));
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
