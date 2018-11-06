#include "h2product.h"
#include "ui_h2product.h"

H2Product::H2Product(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Product)
{
    ui->setupUi(this);

    setName( "product" );

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
