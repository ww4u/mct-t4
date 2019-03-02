/********************************************************************************
** Form generated from reading UI file 'h2errmgr.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2ERRMGR_H
#define UI_H2ERRMGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2ErrMgr
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tvErr;

    void setupUi(QWidget *H2ErrMgr)
    {
        if (H2ErrMgr->objectName().isEmpty())
            H2ErrMgr->setObjectName(QStringLiteral("H2ErrMgr"));
        H2ErrMgr->resize(453, 299);
        verticalLayout = new QVBoxLayout(H2ErrMgr);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tvErr = new QTableView(H2ErrMgr);
        tvErr->setObjectName(QStringLiteral("tvErr"));
        tvErr->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tvErr->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tvErr->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
        tvErr->setAlternatingRowColors(true);
        tvErr->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tvErr->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tvErr->setWordWrap(false);
        tvErr->setCornerButtonEnabled(false);
        tvErr->horizontalHeader()->setMinimumSectionSize(30);
        tvErr->horizontalHeader()->setStretchLastSection(true);
        tvErr->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tvErr);


        retranslateUi(H2ErrMgr);

        QMetaObject::connectSlotsByName(H2ErrMgr);
    } // setupUi

    void retranslateUi(QWidget *H2ErrMgr)
    {
        H2ErrMgr->setWindowTitle(QApplication::translate("H2ErrMgr", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2ErrMgr: public Ui_H2ErrMgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2ERRMGR_H
