#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include <QWizard>
#include <QProgressBar>
#include "roboconfig.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QButtonGroup;
class QLabel;
class QLineEdit;
class QRadioButton;
class XProgressBar;
class QTextBrowser;
QT_END_NAMESPACE

#define MEGA_UPDATE_TOOL    "/MRQ_Update/MegaRobo_Update.exe"

class ClassWizard : public QWizard
{
    Q_OBJECT
public:
    ClassWizard(QWidget *parent = 0);
    void accept() override;

    RoboConfig *m_roboConfig;
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class ClassInfoPage : public QWizardPage
{
    Q_OBJECT

public:
    ClassInfoPage(QWidget *parent = 0);

    QString getFile(){ return file; }

private:

    QLabel *fileLable;
    QLineEdit *fileLineEdit;
    QPushButton *openPushButton;

    QGroupBox *groupBox;
    QCheckBox *mrqCheckButton;
    QCheckBox *mrhCheckButton;

    QString file;

private slots:
    void slot_openFile();

};

class UpdatePage : public QWizardPage
{
    Q_OBJECT
public:
    UpdatePage(QWidget *parent = 0);
    virtual bool isComplete();

protected:
    void initializePage() override;
private:
    QString fileName;
    QString addr;
    QString recvID;
    int iCheckValue;
    XProgressBar *m_processBar;
    QTextBrowser *m_textBrowser;
    QProcess *p;
    bool bFinished;

private slots:
    void slot_doStartWork();
    void slot_finish();
};

class XProgressBar : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(bool ready READ isReady NOTIFY emit_endWork)

public:
    XProgressBar(QWidget *parent = 0);

    bool isReady(){ return m_ready; }
    void setReady(bool b){ m_ready = b; }

signals:
    void emit_endWork();
private:
    bool m_ready;
};

#endif // CLASSWIZARD_H
