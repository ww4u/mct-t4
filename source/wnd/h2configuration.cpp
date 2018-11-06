#include "h2configuration.h"
#include "ui_h2configuration.h"

H2Configuration::H2Configuration(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Configuration)
{
    ui->setupUi(this);

    setName( "config" );

    //先隐藏保留
    ui->groupBox_brake->hide();

    connect(ui->sizeComboBox,SIGNAL(activated(QString)),this,SLOT(slotSelectSize(QString)) );
    connect(ui->radioButton_b,SIGNAL(toggled(bool)),this,SLOT(slotShowConfigPicture(bool)));
    connect(ui->workSpaceStrokeXComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slotUserDefinedStrokeX(QString)));
    connect(ui->workSpaceStrokeYComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slotUserDefinedStrokeY(QString)));

    connect( ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->workSpaceStrokeXComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->workSpaceStrokeYComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->spinBox_X, SIGNAL(valueChanged(QString)), this, SLOT(slotOnModelChanged()));
    connect( ui->spinBox_Y, SIGNAL(valueChanged(QString)), this, SLOT(slotOnModelChanged()));

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
    QString strUserDefine = ui->workSpaceStrokeXComboBox->itemText( ui->workSpaceStrokeXComboBox->count() - 1);
    QString model = QString("%1-%2")
            .arg(ui->label_family->text())
            .arg(ui->sizeComboBox->currentText());

    QString t_str = ui->workSpaceStrokeXComboBox->currentText();
    model += "-";
    if(t_str != strUserDefine)
        model += t_str.left(t_str.length() - 2);
    else
        model += ui->spinBox_X->text();

    strUserDefine = ui->workSpaceStrokeYComboBox->itemText( ui->workSpaceStrokeYComboBox->count() - 1);
    t_str = ui->workSpaceStrokeYComboBox->currentText();
    model += "-";
    if(t_str != strUserDefine)
        model += t_str.left(t_str.length() - 2);
    else
        model += ui->spinBox_Y->text();


    if("10" == ui->sizeComboBox->currentText())
        model += "-GF";
    else
        model += "-KF";

//    if(ui->radioButton_st->isChecked())
//        model += "-ST";
//    else
//        model += "-SB";

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
    QString strUserDefine = ui->workSpaceStrokeXComboBox->itemText( ui->workSpaceStrokeXComboBox->count() - 1);
    if(text == strUserDefine)
    {
        ui->spinBox_X->show();
        ui->spinBox_X->setEnabled(true);
    }
    else
    {
        ui->spinBox_X->hide();
        ui->spinBox_X->setEnabled(false);
    }
}

void H2Configuration::slotUserDefinedStrokeY(QString text)
{
    QString strUserDefine = ui->workSpaceStrokeYComboBox->itemText( ui->workSpaceStrokeYComboBox->count() - 1);
    if(text == strUserDefine)
    {
        ui->spinBox_Y->show();
        ui->spinBox_Y->setEnabled(true);
    }
    else
    {
        ui->spinBox_Y->hide();
        ui->spinBox_Y->setEnabled(false);
    }
}

void H2Configuration::selectSize10()
{
    QStringList strList;
    strList << tr("150mm") << tr("260mm") << tr("300mm") << tr("360mm") << tr("700mm") << tr("User defined");
    ui->workSpaceStrokeXComboBox->clear();
    ui->workSpaceStrokeXComboBox->addItems(strList);

    strList.clear();
    strList << tr("110mm") << tr("160mm") << tr("210mm") << tr("260mm") << tr("310mm") << tr("360mm") << tr("User defined");
    ui->workSpaceStrokeYComboBox->clear();
    ui->workSpaceStrokeYComboBox->addItems(strList);


    ui->label_picture->setPixmap(QPixmap(":/res/image/h2configuration/excm_10.PNG"));

    ui->workSpaceStrokeYLabel->setEnabled(false);
    ui->workSpaceStrokeYComboBox->setEnabled(false);
    ui->radioButton_st->setEnabled(false);
    ui->radioButton_sb->setEnabled(false);
    ui->radioButton_b->setEnabled(false);
    ui->radioButton_t->setEnabled(false);

    ui->spinBox_X->hide();
    ui->spinBox_X->setEnabled(false);
    ui->spinBox_Y->hide();
    ui->spinBox_Y->setEnabled(false);
}


void H2Configuration::selectSize30()
{
    QStringList strList;
    strList.clear();
    strList << tr("100mm") << tr("150mm") << tr("200mm") << tr("300mm") << tr("400mm") << tr("500mm") << tr("User defined");
    ui->workSpaceStrokeXComboBox->clear();
    ui->workSpaceStrokeXComboBox->addItems(strList);

    strList.clear();
    strList << tr("110mm") << tr("160mm") << tr("210mm") << tr("260mm") << tr("310mm") << tr("360mm") << tr("User defined");
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

int H2Configuration::setApply(ViSession visa)
{
    qDebug() << "H2Configuration:" << visa;

#if 0
    if(visa == 0) return -1;

    int ret = -1;
    char strIDN[1024] = "";
    ret = mrhtIdn_Query(visa,strIDN,sizeof(strIDN));
    qDebug() << strIDN; //MegaRobo Technologies,MRH-T,MRHT000005187U0032,00.00.01.06
#endif
    return 0;
}
