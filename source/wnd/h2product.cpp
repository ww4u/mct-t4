#include "h2product.h"
#include "ui_h2product.h"

H2Product::H2Product(QString strDevInfo, QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Product)
{
    ui->setupUi(this);

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
