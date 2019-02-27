#include "coordinate.h"
#include "ui_coordinate.h"

#include "t4.h"

namespace mrx_t4 {

Coordinate::Coordinate(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Coordinate)
{
    ui->setupUi(this);

    spyEdited();

    set_page_rstable();
}

Coordinate::~Coordinate()
{
    delete ui;
}

void Coordinate::updateUi()
{
    ui->coordTool->setPara( selfPara->mCoordPara[0].mParas );
    ui->coordObj->setPara( selfPara->mCoordPara[1].mParas );
    ui->coordUser->setPara( selfPara->mCoordPara[2].mParas );
}

void Coordinate::spyEdited()
{

}

}
