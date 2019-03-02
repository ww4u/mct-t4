/********************************************************************************
** Form generated from reading UI file 'h2action.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2ACTION_H
#define UI_H2ACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2Action
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;

    void setupUi(QWidget *H2Action)
    {
        if (H2Action->objectName().isEmpty())
            H2Action->setObjectName(QStringLiteral("H2Action"));
        H2Action->resize(746, 324);
        verticalLayout = new QVBoxLayout(H2Action);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tableView = new QTableView(H2Action);
        tableView->setObjectName(QStringLiteral("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);
        tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setShowGrid(true);
        tableView->setCornerButtonEnabled(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(tableView);


        retranslateUi(H2Action);

        QMetaObject::connectSlotsByName(H2Action);
    } // setupUi

    void retranslateUi(QWidget *H2Action)
    {
        H2Action->setWindowTitle(QApplication::translate("H2Action", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2Action: public Ui_H2Action {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2ACTION_H
