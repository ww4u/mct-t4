/********************************************************************************
** Form generated from reading UI file 'helppanel.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPPANEL_H
#define UI_HELPPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpPanel
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;

    void setupUi(QWidget *HelpPanel)
    {
        if (HelpPanel->objectName().isEmpty())
            HelpPanel->setObjectName(QStringLiteral("HelpPanel"));
        HelpPanel->resize(476, 212);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HelpPanel->sizePolicy().hasHeightForWidth());
        HelpPanel->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(HelpPanel);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(HelpPanel);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);


        retranslateUi(HelpPanel);

        QMetaObject::connectSlotsByName(HelpPanel);
    } // setupUi

    void retranslateUi(QWidget *HelpPanel)
    {
        HelpPanel->setWindowTitle(QApplication::translate("HelpPanel", "MEGAROBO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpPanel: public Ui_HelpPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPPANEL_H
