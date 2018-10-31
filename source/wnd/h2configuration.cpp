#include "h2configuration.h"
#include "ui_h2configuration.h"
#include <QDebug>

const QString strUserDefine = ("User defined");

H2Configuration::H2Configuration(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Configuration)
{
    ui->setupUi(this);

    setName( "config" );

    ui->sizeComboBox->addItem("10");
    ui->sizeComboBox->addItem("30");

    connect(ui->sizeComboBox,SIGNAL(activated(QString)),this,SLOT(slotSelectSize(QString)) );
    connect(ui->radioButton_b,SIGNAL(toggled(bool)),this,SLOT(slotShowConfigPicture(bool)));
    connect(ui->workSpaceStrokeXComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slotUserDefinedStrokeX(QString)));
    connect(ui->workSpaceStrokeYComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slotUserDefinedStrokeY(QString)));

    connect( ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->workSpaceStrokeXComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->workSpaceStrokeYComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->lineEdit_X, SIGNAL(textChanged(QString)), this, SLOT(slotOnModelChanged()));
    connect( ui->lineEdit_Y, SIGNAL(textChanged(QString)), this, SLOT(slotOnModelChanged()));

    connect( ui->radioButton_st, SIGNAL(toggled(bool)), this, SLOT(slotOnModelChanged()));
    connect( ui->radioButton_sb, SIGNAL(toggled(bool)), this, SLOT(slotOnModelChanged()));
    connect( ui->radioButton_b, SIGNAL(toggled(bool)), this, SLOT(slotOnModelChanged()));
    connect( ui->radioButton_t, SIGNAL(toggled(bool)), this, SLOT(slotOnModelChanged()));

    selectSize10();
    slotOnModelChanged();
}

H2Configuration::~H2Configuration()
{
    delete ui;
}

void H2Configuration::slotShowConfigPicture(bool bl)
{
    if(bl)
        ui->label_picture->setPixmap(QPixmap(":/res/image/h2configuration/excm_30_bottom.PNG"));
    else
        ui->label_picture->setPixmap(QPixmap(":/res/image/h2configuration/excm_30_top.PNG"));
}

void H2Configuration::slotOnModelChanged()
{
    QString model = QString("%1-%2")
            .arg(ui->label_family->text())
            .arg(ui->sizeComboBox->currentText());

    QString t_str = ui->workSpaceStrokeXComboBox->currentText();
    model += "-";
    if(t_str != strUserDefine)
        model += t_str.left(t_str.length() - 2);
    else
        model += ui->lineEdit_X->text();

    t_str = ui->workSpaceStrokeYComboBox->currentText();
    model += "-";
    if(t_str != strUserDefine)
        model += t_str.left(t_str.length() - 2);
    else
        model += ui->lineEdit_Y->text();


    if("10" == ui->sizeComboBox->currentText())
        model += "-GF";
    else
        model += "-KF";

    if(ui->radioButton_st->isChecked())
        model += "-ST";
    else
        model += "-SB";

    if(ui->radioButton_b->isChecked())
        model += "-B";
    else
        model += "-T";

    ui->label_model->setText(model);
}

void H2Configuration::slotSelectSize(QString text)
{
    if(text == tr("10"))
        selectSize10();
    else if(text == ("30"))
        selectSize30();
}

void H2Configuration::slotUserDefinedStrokeX(QString text)
{
    if(text == strUserDefine)
    {
        ui->lineEdit_X->show();
        ui->lineEdit_X->setEnabled(true);
    }
    else
    {
        ui->lineEdit_X->hide();
        ui->lineEdit_X->setEnabled(false);
    }
}

void H2Configuration::slotUserDefinedStrokeY(QString text)
{
    if(text == strUserDefine)
    {
        ui->lineEdit_Y->show();
        ui->lineEdit_Y->setEnabled(true);
    }
    else
    {
        ui->lineEdit_Y->hide();
        ui->lineEdit_Y->setEnabled(false);
    }
}

void H2Configuration::selectSize10()
{
    QStringList strList;
    strList << tr("150mm") << tr("260mm") << tr("300mm") << tr("360mm") << tr("700mm") << strUserDefine;
    ui->workSpaceStrokeXComboBox->clear();
    ui->workSpaceStrokeXComboBox->addItems(strList);

    strList.clear();
    strList << tr("110mm") << tr("160mm") << tr("210mm") << tr("260mm") << tr("310mm") << tr("360mm") << strUserDefine;
    ui->workSpaceStrokeYComboBox->clear();
    ui->workSpaceStrokeYComboBox->addItems(strList);


    ui->label_picture->setPixmap(QPixmap(":/res/image/h2configuration/excm_10.PNG"));

    ui->workSpaceStrokeYLabel->setEnabled(false);
    ui->workSpaceStrokeYComboBox->setEnabled(false);
    ui->radioButton_st->setEnabled(false);
    ui->radioButton_sb->setEnabled(false);
    ui->radioButton_b->setEnabled(false);
    ui->radioButton_t->setEnabled(false);

    ui->lineEdit_X->hide();
    ui->lineEdit_X->setEnabled(false);
    ui->lineEdit_Y->hide();
    ui->lineEdit_Y->setEnabled(false);
}


void H2Configuration::selectSize30()
{
    QStringList strList;
    strList.clear();
    strList << tr("100mm") << tr("150mm") << tr("200mm") << tr("300mm") << tr("400mm") << tr("500mm") << strUserDefine;
    ui->workSpaceStrokeXComboBox->clear();
    ui->workSpaceStrokeXComboBox->addItems(strList);

    strList.clear();
    strList << tr("110mm") << tr("160mm") << tr("210mm") << tr("260mm") << tr("310mm") << tr("360mm") << strUserDefine;
    ui->workSpaceStrokeYComboBox->clear();
    ui->workSpaceStrokeYComboBox->addItems(strList);


    ui->workSpaceStrokeYLabel->setEnabled(true);
    ui->workSpaceStrokeYComboBox->setEnabled(true);
//    ui->radioButton_st->setEnabled(true);
//    ui->radioButton_sb->setEnabled(true);
    ui->radioButton_b->setEnabled(true);
    ui->radioButton_t->setEnabled(true);

    ui->radioButton_st->setChecked(true);
    ui->radioButton_b->setChecked(true);
    slotShowConfigPicture(true);
}

