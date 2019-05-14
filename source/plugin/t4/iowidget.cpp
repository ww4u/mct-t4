#include "iowidget.h"
#include "ui_iowidget.h"

#define cat_widgets( wig )      mBits.append( wig ); mSpanWidgets.append( wig );

IOWidget::IOWidget(int w, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOWidget)
{
    ui->setupUi(this);

    mWidth = w;

    //! adapt to the width
    cat_widgets( ui->checkBox );
    cat_widgets( ui->checkBox_2 );
    cat_widgets( ui->checkBox_3 );
    cat_widgets( ui->checkBox_4 ); mSpanWidgets.append( ui->label );

    cat_widgets( ui->checkBox_5 );
    cat_widgets( ui->checkBox_6 );
    cat_widgets( ui->checkBox_7 );
    cat_widgets( ui->checkBox_8 );

    cat_widgets( ui->checkBox_9 );
    cat_widgets( ui->checkBox_10 );
    cat_widgets( ui->checkBox_11 );
    cat_widgets( ui->checkBox_12 ); mSpanWidgets.append( ui->label_2 );


    cat_widgets( ui->checkBox_13 );
    cat_widgets( ui->checkBox_14 );
    cat_widgets( ui->checkBox_15 );
    cat_widgets( ui->checkBox_16 );

    cat_widgets( ui->checkBox_17 );
    cat_widgets( ui->checkBox_18 );
    cat_widgets( ui->checkBox_19 );
    cat_widgets( ui->checkBox_20 ); mSpanWidgets.append( ui->label_3 );

    cat_widgets( ui->checkBox_21 );
    cat_widgets( ui->checkBox_22 );
    cat_widgets( ui->checkBox_23 );
    cat_widgets( ui->checkBox_24 );

    cat_widgets( ui->checkBox_25 );
    cat_widgets( ui->checkBox_26 );
    cat_widgets( ui->checkBox_27 );
    cat_widgets( ui->checkBox_28 ); mSpanWidgets.append( ui->label_4 );

    cat_widgets( ui->checkBox_29 );
    cat_widgets( ui->checkBox_30 );
    cat_widgets( ui->checkBox_31 );
    cat_widgets( ui->checkBox_32 );

    //! adapt the widgets
    int i = 0;
    for ( i = 0; i < w; i++ )
    {
        mBits[i]->setVisible( true );
        mBits[i]->setTristate();
        mBits[i]->setText(QString("Y[%1]").arg(i+1));
    }

    //! find the w
    int last;
    last = mSpanWidgets.indexOf( mBits.at(w-1) );
    for ( last = last + 1 ; last < mSpanWidgets.size(); last++ )
    {
        mSpanWidgets[ last ]->setVisible( false );
    }
}

IOWidget::~IOWidget()
{
    delete ui;
}

void IOWidget::setData( quint32 dat )
{
    for ( int i = 0; i < mWidth; i++ )
    {
        mBits.at(i)->setCheckState( Qt::CheckState( dat & 0x03) );

        dat >>= 2;
    }
}
quint32 IOWidget::getData( )
{
    quint32 dat = 0;
    for ( int i = 0; i < mWidth; i++ )
    {
        dat |= ( mBits.at(i)->checkState()<<(i*2));
    }

    return dat;
}
