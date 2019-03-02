/********************************************************************************
** Form generated from reading UI file 'roboconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOCONFIG_H
#define UI_ROBOCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoboConfig
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QDialogButtonBox *buttonBox;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *RoboConfig)
    {
        if (RoboConfig->objectName().isEmpty())
            RoboConfig->setObjectName(QStringLiteral("RoboConfig"));
        RoboConfig->resize(876, 508);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RoboConfig->sizePolicy().hasHeightForWidth());
        RoboConfig->setSizePolicy(sizePolicy);
        RoboConfig->setMinimumSize(QSize(0, 0));
        RoboConfig->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(RoboConfig);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(RoboConfig);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(stackedWidget, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(RoboConfig);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy2);
        buttonBox->setStandardButtons(QDialogButtonBox::Reset);
        buttonBox->setCenterButtons(false);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

        treeWidget = new QTreeWidget(RoboConfig);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setMinimumSize(QSize(260, 0));
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget->setFrameShape(QFrame::StyledPanel);
        treeWidget->setAutoScrollMargin(10);
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setIndentation(10);
        treeWidget->header()->setVisible(false);
        treeWidget->header()->setDefaultSectionSize(80);

        gridLayout->addWidget(treeWidget, 1, 0, 2, 1);


        retranslateUi(RoboConfig);

        QMetaObject::connectSlotsByName(RoboConfig);
    } // setupUi

    void retranslateUi(QWidget *RoboConfig)
    {
        RoboConfig->setWindowTitle(QApplication::translate("RoboConfig", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoboConfig: public Ui_RoboConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOCONFIG_H
