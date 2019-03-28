/********************************************************************************
** Form generated from reading UI file 'welcomepage.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEPAGE_H
#define UI_WELCOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomePage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *WelcomePage)
    {
        if (WelcomePage->objectName().isEmpty())
            WelcomePage->setObjectName(QStringLiteral("WelcomePage"));
        WelcomePage->resize(400, 300);
        verticalLayout = new QVBoxLayout(WelcomePage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(WelcomePage);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/image/m.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(10);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(WelcomePage);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);


        retranslateUi(WelcomePage);

        QMetaObject::connectSlotsByName(WelcomePage);
    } // setupUi

    void retranslateUi(QWidget *WelcomePage)
    {
        WelcomePage->setWindowTitle(QApplication::translate("WelcomePage", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("WelcomePage", "www.megarobo.tech", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomePage: public Ui_WelcomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEPAGE_H
