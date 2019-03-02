/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LogIn
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *chkAutoLogin;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LogIn)
    {
        if (LogIn->objectName().isEmpty())
            LogIn->setObjectName(QStringLiteral("LogIn"));
        LogIn->resize(206, 73);
        verticalLayout = new QVBoxLayout(LogIn);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(LogIn);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(24, 24));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/image/icon/group.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(LogIn);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/icon/51.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon, QString());
        comboBox->addItem(icon, QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        chkAutoLogin = new QCheckBox(LogIn);
        chkAutoLogin->setObjectName(QStringLiteral("chkAutoLogin"));
        chkAutoLogin->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(chkAutoLogin);

        buttonBox = new QDialogButtonBox(LogIn);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(LogIn);
        QObject::connect(buttonBox, SIGNAL(accepted()), LogIn, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LogIn, SLOT(reject()));

        QMetaObject::connectSlotsByName(LogIn);
    } // setupUi

    void retranslateUi(QDialog *LogIn)
    {
        LogIn->setWindowTitle(QApplication::translate("LogIn", "LogIn", nullptr));
        label->setText(QString());
        comboBox->setItemText(0, QApplication::translate("LogIn", "Operator", nullptr));
        comboBox->setItemText(1, QApplication::translate("LogIn", "Administrator", nullptr));

        chkAutoLogin->setText(QApplication::translate("LogIn", "Auto login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIn: public Ui_LogIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
