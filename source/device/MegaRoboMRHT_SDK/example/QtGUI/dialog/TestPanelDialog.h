#ifndef TESTPANELDIALOG_H
#define TESTPANELDIALOG_H

#include <QDialog>
#include <MegaGateway.h>
#include "xthread.h"

namespace Ui {
class TestPanelDialog;
}

class TestPanelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestPanelDialog(ViSession vi,int robot,int device, QWidget *parent = 0);
    ~TestPanelDialog();

private slots:
    void on_pushButton_updateFirmware_clicked();
    void updateFirmwareEndTips(int ret);

    void on_pushButton_ScanMotionFile_clicked();

    void on_pushButton_ImportMotionFile_clicked();

    void on_pushButton_RunStop_clicked();

    void on_pushButton_ReadMotionFile_clicked();

    void on_pushButton_test_clicked();

private:
    Ui::TestPanelDialog *ui;
    ViSession m_vi;
    int     m_robotID;
    int     m_deviceID;

    bool m_isDebugRunFlag;
    XThread *m_threadOpsDebug;
};

#endif // TESTPANELDIALOG_H
