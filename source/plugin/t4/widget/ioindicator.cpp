#include "ioindicator.h"
#include "ui_ioindicator.h"

IoIndicator::IoIndicator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IoIndicator)
{
    ui->setupUi(this);

    mIOIndiction<<"L"<<"H";
}

IoIndicator::~IoIndicator()
{
    delete ui;
}

void IoIndicator::setIndication( const QStringList &indi )
{
    mIOIndiction = indi;
}

void IoIndicator::setChecked( bool b )
{
    ui->radioButton->setChecked(b);

    ui->radioButton->setText( mIOIndiction.at( (int)b ));
}
bool IoIndicator::isChecked( )
{ return ui->radioButton->isChecked(); }

void IoIndicator::setText( const QString &text )
{ ui->label->setText( text ); }
QString IoIndicator::text()
{ return ui->label->text(); }
