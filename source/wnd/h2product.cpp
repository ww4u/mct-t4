#include "h2product.h"
#include "ui_h2product.h"

#include <QThread>

H2Product::H2Product(QString strDevInfo, QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Product)
{
    ui->setupUi(this);
    m_visa = 0;

    setName( "product" );

    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);
    if(strListDev.count() == 0)
    {   return;     }
    if(strListDev.count() > 0)
    {   this->m_IP = strListDev.at(0);    }
    if(strListDev.count() > 2)
    {   this->m_Type = strListDev.at(2);    }
    if(strListDev.count() > 3)
    {   this->m_SN = strListDev.at(3);    }
    if(strListDev.count() > 4)
    {   this->m_Version = strListDev.at(4);    }

    ui->label_ip->setText(this->m_IP);
    ui->label_sn->setText(this->m_SN);
    ui->label_type->setText(this->m_Type);
    ui->label_version->setText(this->m_Version);
    m_online = false;
    ui->toolButton_status->setText(tr("offline"));
    ui->toolButton_status->setToolTip(tr("click here to open device"));
}

H2Product::~H2Product()
{
    delete ui;
}

int H2Product::setApply(ViSession visa)
{
    qDebug() << "H2Product:" << visa;

    if(visa == 0) return -1;

    int ret = -1;
    char strIDN[1024] = "";
    ret = mrhtIdn_Query(visa,strIDN,sizeof(strIDN));
    qDebug() << strIDN; //MegaRobo Technologies,MRH-T,MRHT000005187U0032,00.00.01.06

}

void H2Product::on_toolButton_status_clicked()
{
    if(!m_online)
    {
        m_visa = 0;
        int ret = deviceOpen();
        if(ret != 0)
            return;

        emit signal_device_open(m_visa);
        m_online = true;
        ui->toolButton_status->setText(tr("online"));
        ui->toolButton_status->setToolTip(tr("click here to close device"));
    }
    else
    {
        deviceClose();
        emit signal_device_close();

        m_online = false;
        ui->toolButton_status->setText(tr("offline"));
        ui->toolButton_status->setToolTip(tr("click here to open device"));
    }
}

int H2Product::deviceOpen()
{
    int visa = mrhtOpenDevice(this->m_IP.toLatin1().data(), 2000);
    qDebug() << "device open:" << visa;
    if(visa <= 0)
        return -1;

    m_visa = visa;

    mrhtSystemIdentify(m_visa, 1);
    return 0;
}

int H2Product::deviceClose()
{
    int ret = -1;
    if(m_visa != 0)
    {
        mrhtSystemIdentify(m_visa, 0);
        ret = mrhtCloseDevice(m_visa);
        qDebug() << "device close:" << ret;
        m_visa = 0;
    }

    return 0;
}

