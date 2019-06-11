#include "login.h"
#include "ui_login.h"
#include <QPushButton>
#include <QMessageBox>
#include "../include/mydebug.h"
LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);

    setWindowFlags( (Qt::WindowFlags)(~Qt::WindowCloseButtonHint) & windowFlags() );

    //! post setting
//    on_comboBox_currentIndexChanged( ui->comboBox->currentIndex() );
}

LogIn::~LogIn()
{
    delete ui;
}

//void LogIn::accept()
//{
//    //! no need to check the pw
//    if ( ui->edtPw->isVisible() )
//    {
//    }
//    else
//    {
//        QDialog::accept();
//        return;
//    }

//    QString localPw = qUncompress( mPw );
//    if ( ui->edtPw->text().compare( localPw, Qt::CaseSensitive) == 0 )
//    {
//        QDialog::accept();
//    }
//    //! invalid
//    else
//    {
//        ui->edtPw->clear();
//        QMessageBox::critical( this, tr("Error"), tr("Invalid password"), QMessageBox::Ok );
//    }
//}

//void LogIn::setPw( const QByteArray &ary )
//{
//    mPw = ary;
//}

QString LogIn::getPw()
{ return ui->edtPw->text(); }

int LogIn::getUserRole()
{
    return ui->comboBox->currentIndex();
}

//void LogIn::on_comboBox_currentIndexChanged(int index)
//{
//    bool bV;

//    bV = ui->comboBox->currentIndex() == 1;

//    ui->labPw->setVisible( bV );
//    ui->edtPw->setVisible( bV );

//    if ( ui->comboBox->currentIndex() == 1 )
//    {
//        on_edtPw_textChanged( ui->edtPw->text() );
//    }
//    else
//    {
//        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( true );
//    }
//}

void LogIn::on_edtPw_textChanged(const QString &arg1)
{
    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( arg1.length() > 0 );
}
