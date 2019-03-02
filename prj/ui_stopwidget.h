/********************************************************************************
** Form generated from reading UI file 'stopwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOPWIDGET_H
#define UI_STOPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StopWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton;

    void setupUi(QWidget *StopWidget)
    {
        if (StopWidget->objectName().isEmpty())
            StopWidget->setObjectName(QStringLiteral("StopWidget"));
        StopWidget->resize(400, 36);
        horizontalLayout = new QHBoxLayout(StopWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(349, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton = new QToolButton(StopWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy);
        toolButton->setMaximumSize(QSize(48, 36));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(48, 36));

        horizontalLayout->addWidget(toolButton);


        retranslateUi(StopWidget);

        QMetaObject::connectSlotsByName(StopWidget);
    } // setupUi

    void retranslateUi(QWidget *StopWidget)
    {
        StopWidget->setWindowTitle(QApplication::translate("StopWidget", "Form", nullptr));
        toolButton->setText(QApplication::translate("StopWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StopWidget: public Ui_StopWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOPWIDGET_H
