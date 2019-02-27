#include "syspref.h"
#include "ui_syspref.h"

SysPref::SysPref(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysPref)
{
    ui->setupUi(this);
}

SysPref::SysPref( const SysPara &para, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::SysPref)
{
    ui->setupUi(this);

    //! copy
    mbAutoExpand = para.mbAutoExpand;
    mbAutoLoad = para.mbAutoLoad;
    mbAutoSearch = para.mbAutoSearch;

    mIntfIndex = para.mIntfIndex;
    mStyleIndex = para.mStyleIndex;

    mPlugins = para.mPlugins;

}

SysPref::~SysPref()
{
    delete ui;
}

int SysPref::exec()
{
    updateUi();

    int ret = QDialog::exec();

    updateData();

    return ret;
}

void SysPref::updateUi()
{
    ui->chkAutoExpand->setChecked( mbAutoExpand );
    ui->chkAutoLoad->setChecked( mbAutoLoad );
    ui->chkAutoSearch->setChecked( mbAutoSearch );
}
void SysPref::updateData()
{
    mbAutoExpand = ui->chkAutoExpand->isChecked();
    mbAutoLoad = ui->chkAutoLoad->isChecked();
    mbAutoSearch = ui->chkAutoSearch->isChecked();
}

void SysPref::on_buttonBox_clicked(QAbstractButton *button)
{
    //! reset
    if ( ui->buttonBox->buttonRole( button ) ==  QDialogButtonBox::ResetRole )
    {qDebug()<<__FUNCTION__;
        init();

        updateUi();
    }
}
