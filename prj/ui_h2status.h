/********************************************************************************
** Form generated from reading UI file 'h2status.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2STATUS_H
#define UI_H2STATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2Status
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_9;
    QLabel *label;
    QRadioButton *radReady;
    QLineEdit *edtOpMode;
    QRadioButton *radEn;
    QRadioButton *radMc;
    QRadioButton *radTo;
    QLineEdit *edtError;
    QRadioButton *radWarning;
    QRadioButton *radError;
    QLineEdit *edtWarning;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkMct;
    QCheckBox *chkPwr;
    QPushButton *btnAckError;

    void setupUi(QWidget *H2Status)
    {
        if (H2Status->objectName().isEmpty())
            H2Status->setObjectName(QStringLiteral("H2Status"));
        H2Status->setWindowModality(Qt::WindowModal);
        H2Status->setEnabled(true);
        H2Status->resize(290, 253);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(H2Status->sizePolicy().hasHeightForWidth());
        H2Status->setSizePolicy(sizePolicy);
        H2Status->setMinimumSize(QSize(290, 200));
        H2Status->setMaximumSize(QSize(290, 16777215));
        gridLayout = new QGridLayout(H2Status);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_9 = new QGroupBox(H2Status);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setMinimumSize(QSize(0, 0));
        gridLayout_9 = new QGridLayout(groupBox_9);
        gridLayout_9->setSpacing(2);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(6, 2, 2, 6);
        label = new QLabel(groupBox_9);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(label, 0, 1, 1, 1);

        radReady = new QRadioButton(groupBox_9);
        radReady->setObjectName(QStringLiteral("radReady"));
        radReady->setEnabled(false);
        radReady->setChecked(true);
        radReady->setAutoExclusive(false);

        gridLayout_9->addWidget(radReady, 2, 0, 1, 1);

        edtOpMode = new QLineEdit(groupBox_9);
        edtOpMode->setObjectName(QStringLiteral("edtOpMode"));
        edtOpMode->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(edtOpMode->sizePolicy().hasHeightForWidth());
        edtOpMode->setSizePolicy(sizePolicy2);

        gridLayout_9->addWidget(edtOpMode, 0, 2, 1, 2);

        radEn = new QRadioButton(groupBox_9);
        radEn->setObjectName(QStringLiteral("radEn"));
        radEn->setEnabled(false);
        radEn->setChecked(true);
        radEn->setAutoExclusive(false);

        gridLayout_9->addWidget(radEn, 0, 0, 1, 1);

        radMc = new QRadioButton(groupBox_9);
        radMc->setObjectName(QStringLiteral("radMc"));
        radMc->setEnabled(false);
        radMc->setAutoExclusive(false);

        gridLayout_9->addWidget(radMc, 3, 0, 1, 1);

        radTo = new QRadioButton(groupBox_9);
        radTo->setObjectName(QStringLiteral("radTo"));
        radTo->setEnabled(false);
        radTo->setAutoExclusive(false);

        gridLayout_9->addWidget(radTo, 1, 0, 1, 1);

        edtError = new QLineEdit(groupBox_9);
        edtError->setObjectName(QStringLiteral("edtError"));
        edtError->setEnabled(false);
        sizePolicy2.setHeightForWidth(edtError->sizePolicy().hasHeightForWidth());
        edtError->setSizePolicy(sizePolicy2);

        gridLayout_9->addWidget(edtError, 4, 1, 1, 3);

        radWarning = new QRadioButton(groupBox_9);
        radWarning->setObjectName(QStringLiteral("radWarning"));
        radWarning->setEnabled(false);
        radWarning->setChecked(true);
        radWarning->setAutoExclusive(false);

        gridLayout_9->addWidget(radWarning, 5, 0, 1, 1);

        radError = new QRadioButton(groupBox_9);
        radError->setObjectName(QStringLiteral("radError"));
        radError->setEnabled(false);
        radError->setChecked(true);
        radError->setAutoExclusive(false);

        gridLayout_9->addWidget(radError, 4, 0, 1, 1);

        edtWarning = new QLineEdit(groupBox_9);
        edtWarning->setObjectName(QStringLiteral("edtWarning"));
        edtWarning->setEnabled(false);
        sizePolicy2.setHeightForWidth(edtWarning->sizePolicy().hasHeightForWidth());
        edtWarning->setSizePolicy(sizePolicy2);

        gridLayout_9->addWidget(edtWarning, 5, 1, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_2, 6, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chkMct = new QCheckBox(groupBox_9);
        chkMct->setObjectName(QStringLiteral("chkMct"));
        chkMct->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(chkMct->sizePolicy().hasHeightForWidth());
        chkMct->setSizePolicy(sizePolicy3);
        chkMct->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(chkMct);

        chkPwr = new QCheckBox(groupBox_9);
        chkPwr->setObjectName(QStringLiteral("chkPwr"));
        chkPwr->setEnabled(false);
        sizePolicy3.setHeightForWidth(chkPwr->sizePolicy().hasHeightForWidth());
        chkPwr->setSizePolicy(sizePolicy3);
        chkPwr->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(chkPwr);

        btnAckError = new QPushButton(groupBox_9);
        btnAckError->setObjectName(QStringLiteral("btnAckError"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(2);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnAckError->sizePolicy().hasHeightForWidth());
        btnAckError->setSizePolicy(sizePolicy4);
        btnAckError->setMinimumSize(QSize(0, 0));
        btnAckError->setFlat(false);

        horizontalLayout->addWidget(btnAckError);


        gridLayout_9->addLayout(horizontalLayout, 7, 0, 2, 4);


        gridLayout->addWidget(groupBox_9, 0, 0, 1, 1);


        retranslateUi(H2Status);

        QMetaObject::connectSlotsByName(H2Status);
    } // setupUi

    void retranslateUi(QWidget *H2Status)
    {
        H2Status->setWindowTitle(QApplication::translate("H2Status", "Form", nullptr));
        groupBox_9->setTitle(QApplication::translate("H2Status", "Device Status", nullptr));
        label->setText(QApplication::translate("H2Status", "Operation Mode", nullptr));
        radReady->setText(QApplication::translate("H2Status", "Ready", nullptr));
        radEn->setText(QApplication::translate("H2Status", "Enable", nullptr));
        radMc->setText(QApplication::translate("H2Status", "MC", nullptr));
        radTo->setText(QApplication::translate("H2Status", "TO", nullptr));
        radWarning->setText(QApplication::translate("H2Status", "Warning", nullptr));
        radError->setText(QApplication::translate("H2Status", "Error", nullptr));
        chkMct->setText(QApplication::translate("H2Status", "MCT", nullptr));
        chkPwr->setText(QApplication::translate("H2Status", "Enable", nullptr));
        btnAckError->setText(QApplication::translate("H2Status", "Acknowledge Error", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2Status: public Ui_H2Status {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2STATUS_H
