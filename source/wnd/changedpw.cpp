#include "changedpw.h"
#include "ui_changedpw.h"
#include <QPushButton>
ChangedPw::ChangedPw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangedPw)
{
    ui->setupUi(this);
}

ChangedPw::~ChangedPw()
{
    delete ui;
}

QString ChangedPw::getPw()
{
    return ui->edtPw1->text();
}

void ChangedPw::updateControl()
{
    if ( ui->edtPw1->text() != ui->edtPw2->text() )
    {
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
        return;
    }

    if ( ui->edtPw1->text().trimmed().length() < 1 )
    {
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
        return;
    }

    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( true );
}

void ChangedPw::on_edtPw1_textChanged(const QString &arg1)
{
    updateControl();
}

void ChangedPw::on_edtPw2_textChanged(const QString &arg1)
{
    updateControl();
}
