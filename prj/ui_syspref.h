/********************************************************************************
** Form generated from reading UI file 'syspref.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSPREF_H
#define UI_SYSPREF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SysPref
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QCheckBox *chkAutoExpand;
    QCheckBox *chkAutoLoad;
    QSpacerItem *verticalSpacer;
    QCheckBox *chkAutoSearch;
    QCheckBox *chkAutoLogin;
    QLabel *label;
    QComboBox *cmbRefresh;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SysPref)
    {
        if (SysPref->objectName().isEmpty())
            SysPref->setObjectName(QStringLiteral("SysPref"));
        SysPref->resize(291, 235);
        SysPref->setModal(true);
        verticalLayout = new QVBoxLayout(SysPref);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(SysPref);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        chkAutoExpand = new QCheckBox(tab);
        chkAutoExpand->setObjectName(QStringLiteral("chkAutoExpand"));
        chkAutoExpand->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(chkAutoExpand, 0, 0, 1, 2);

        chkAutoLoad = new QCheckBox(tab);
        chkAutoLoad->setObjectName(QStringLiteral("chkAutoLoad"));

        gridLayout->addWidget(chkAutoLoad, 1, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        chkAutoSearch = new QCheckBox(tab);
        chkAutoSearch->setObjectName(QStringLiteral("chkAutoSearch"));

        gridLayout->addWidget(chkAutoSearch, 2, 0, 1, 2);

        chkAutoLogin = new QCheckBox(tab);
        chkAutoLogin->setObjectName(QStringLiteral("chkAutoLogin"));

        gridLayout->addWidget(chkAutoLogin, 3, 0, 1, 2);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        cmbRefresh = new QComboBox(tab);
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->addItem(QString());
        cmbRefresh->setObjectName(QStringLiteral("cmbRefresh"));

        gridLayout->addWidget(cmbRefresh, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 2, 1, 1);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(SysPref);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Reset);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SysPref);
        QObject::connect(buttonBox, SIGNAL(accepted()), SysPref, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SysPref, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SysPref);
    } // setupUi

    void retranslateUi(QDialog *SysPref)
    {
        SysPref->setWindowTitle(QApplication::translate("SysPref", "Pref", nullptr));
        chkAutoExpand->setText(QApplication::translate("SysPref", "Auto Expand", nullptr));
        chkAutoLoad->setText(QApplication::translate("SysPref", "Auto Load last", nullptr));
        chkAutoSearch->setText(QApplication::translate("SysPref", "Auto search on startup", nullptr));
        chkAutoLogin->setText(QApplication::translate("SysPref", "Auto Login", nullptr));
        label->setText(QApplication::translate("SysPref", "Data Refresh rate", nullptr));
        cmbRefresh->setItemText(0, QApplication::translate("SysPref", "0.1Hz", nullptr));
        cmbRefresh->setItemText(1, QApplication::translate("SysPref", "0.2Hz", nullptr));
        cmbRefresh->setItemText(2, QApplication::translate("SysPref", "0.5Hz", nullptr));
        cmbRefresh->setItemText(3, QApplication::translate("SysPref", "1Hz", nullptr));
        cmbRefresh->setItemText(4, QApplication::translate("SysPref", "2Hz", nullptr));
        cmbRefresh->setItemText(5, QApplication::translate("SysPref", "5Hz", nullptr));
        cmbRefresh->setItemText(6, QApplication::translate("SysPref", "10Hz", nullptr));
        cmbRefresh->setItemText(7, QApplication::translate("SysPref", "20Hz", nullptr));
        cmbRefresh->setItemText(8, QApplication::translate("SysPref", "50Hz", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SysPref", "Pref", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SysPref: public Ui_SysPref {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSPREF_H
