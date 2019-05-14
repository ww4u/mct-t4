#include "classwizard.h"

ClassWizard::ClassWizard(QWidget *parent)
    : QWizard(parent)
{
    Q_ASSERT( parent != NULL );
    m_roboConfig = (RoboConfig*)(parent);

    addPage(new IntroPage);
    addPage(new ClassInfoPage);
    addPage(new UpdatePage);

    setPixmap(QWizard::BannerPixmap, QPixmap(":/res/images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/res/images/background.png"));
    setWindowTitle(tr("Update Wizard"));
}
void ClassWizard::accept()
{
   QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/res/images/watermark1.png"));

    label = new QLabel(tr("This wizard will update the softion version of MRH and MRQ "
                          "You only need to decide which one to upgrade."
                          "You can chose one or both to upgrade"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

ClassInfoPage::ClassInfoPage(QWidget *parent)
    :QWizardPage(parent)
{
    setTitle(tr("Update Information"));
    setSubTitle(tr("Specify one or both about the item for which you "
                   "want to upgrade."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));

    mrqCheckButton = new QCheckBox(tr("&MRQ"));
    mrhCheckButton = new QCheckBox(tr("&MRH"));
    groupBox = new QGroupBox();
    fileLable = new QLabel(tr("file:"));
    fileLineEdit = new QLineEdit();
    openPushButton = new QPushButton(tr("Open"));
    connect(openPushButton, SIGNAL(clicked(bool)), this, SLOT(slot_openFile()));

    mrqCheckButton->setChecked(true);
    mrhCheckButton->setChecked(true);

    registerField("filePath*", fileLineEdit);
    registerField("MRQ", mrqCheckButton);
    registerField("MRH", mrhCheckButton);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;

    groupBoxLayout->addWidget(mrqCheckButton);
    groupBoxLayout->addWidget(mrhCheckButton);

    groupBox->setLayout(groupBoxLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(fileLable, 0, 0);
    layout->addWidget(fileLineEdit, 0, 1);
    layout->addWidget(openPushButton, 0, 2);
    layout->addWidget(groupBox, 1, 0, 1, 2);
    setLayout(layout);
}

void ClassInfoPage::slot_openFile()
{
    file = QFileDialog::getOpenFileName(this, tr("Open"),NULL, tr("All Files(*.package)"));
    fileLineEdit->setText(file);
}


UpdatePage::UpdatePage(QWidget *parent)
    :QWizardPage(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_processBar = new XProgressBar);
    m_processBar->setMaximum(0);
    layout->addWidget(m_textBrowser = new QTextBrowser);
    setLayout(layout);
    iCheckValue = 0;
    bFinished = 0;
    p = NULL;
}
void UpdatePage::initializePage()
{
    fileName = field("filePath").toString();
    iCheckValue |= (field("MRQ").toInt() & 0x01);
    iCheckValue = iCheckValue << 1;
    iCheckValue |= (field("MRH").toInt() & 0x01);

    addr = ((((ClassWizard*)(this->wizard()))->m_roboConfig)->currentXPlugin())->addr();
    recvID = QString("384");

    QTimer::singleShot(2000, this, SLOT(slot_doStartWork()));
}
void UpdatePage::slot_doStartWork()
{
    //! close
    ((((ClassWizard*)(this->wizard()))->m_roboConfig)->currentXPlugin())->close();

    //! \todo start exe
    switch (iCheckValue) {
    case 0:
    case 1:
    case 2:
    case 3:
        if(p)
            delete p;
        p = new QProcess;
        connect(p, &QProcess::readyRead, this, [=](){
            m_textBrowser->append(p->readAll());
        });
        connect(p, SIGNAL(finished(int)), this, SLOT(slot_finish()));
        QStringList arguments;
        arguments << fileName << addr << recvID;
        QString exePath = qApp->applicationFilePath() + MEGA_UPDATE_TOOL;
        p->start(exePath, arguments);
    }
}
bool UpdatePage::isComplete()
{
    return bFinished;
}

void UpdatePage::slot_finish()
{
    bFinished = false;
    emit completeChanged();
}

XProgressBar::XProgressBar(QWidget *parent)
    :QProgressBar(parent)
{
    //setStyleSheet("QProgressBar::chunk {background-color:#CD96CD;width:10px;margin:0.5px;}");
    setStyleSheet("QProgressBar{border:2px solid grey;border-radius:5px;}");
}
