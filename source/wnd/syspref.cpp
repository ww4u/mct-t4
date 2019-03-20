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
    mbAutoLogin = para.mbAutoLogin;

    mIntfIndex = para.mIntfIndex;
    mRefreshIndex = para.mRefreshIndex;
    mStyleIndex = para.mStyleIndex;
    mSysMode = para.mSysMode;

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
    ui->chkAutoLogin->setChecked( mbAutoLogin );

    ui->cmbRefresh->setCurrentIndex( mRefreshIndex );
}
void SysPref::updateData()
{
    mbAutoExpand = ui->chkAutoExpand->isChecked();
    mbAutoLoad = ui->chkAutoLoad->isChecked();
    mbAutoSearch = ui->chkAutoSearch->isChecked();
    mbAutoLogin = ui->chkAutoLogin->isChecked();

    mRefreshIndex = ui->cmbRefresh->currentIndex();
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