/********************************************************************************
** Form generated from reading UI file 'syslogout.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSLOGOUT_H
#define UI_SYSLOGOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "logoutwidget.h"

QT_BEGIN_NAMESPACE

class Ui_SysLogout
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    LogoutWidget *listView;

    void setupUi(QWidget *SysLogout)
    {
        if (SysLogout->objectName().isEmpty())
            SysLogout->setObjectName(QStringLiteral("SysLogout"));
        SysLogout->resize(650, 247);
        verticalLayout = new QVBoxLayout(SysLogout);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(SysLogout);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listView = new LogoutWidget(tab);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_2->addWidget(listView);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SysLogout);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SysLogout);
    } // setupUi

    void retranslateUi(QWidget *SysLogout)
    {
        SysLogout->setWindowTitle(QApplication::translate("SysLogout", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SysLogout", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SysLogout: public Ui_SysLogout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSLOGOUT_H
