/********************************************************************************
** Form generated from reading UI file 'aboutdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDLG_H
#define UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_aboutDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *aboutDlg)
    {
        if (aboutDlg->objectName().isEmpty())
            aboutDlg->setObjectName(QStringLiteral("aboutDlg"));
        aboutDlg->resize(377, 149);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        aboutDlg->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/icon/feedback.png"), QSize(), QIcon::Normal, QIcon::Off);
        aboutDlg->setWindowIcon(icon);
        aboutDlg->setAutoFillBackground(false);
        aboutDlg->setStyleSheet(QStringLiteral(""));
        aboutDlg->setModal(true);
        horizontalLayout = new QHBoxLayout(aboutDlg);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(aboutDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(64, 64));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/image/m.png")));
        label->setScaledContents(true);

        verticalLayout_2->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(aboutDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(aboutDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_5 = new QLabel(aboutDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_4 = new QLabel(aboutDlg);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setText(QStringLiteral("www.megarobo.tech"));

        verticalLayout->addWidget(label_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(aboutDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(aboutDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), aboutDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), aboutDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(aboutDlg);
    } // setupUi

    void retranslateUi(QDialog *aboutDlg)
    {
        aboutDlg->setWindowTitle(QApplication::translate("aboutDlg", "About", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("aboutDlg", "MEGAROBO Config Tool", nullptr));
        label_3->setText(QApplication::translate("aboutDlg", "0.0.2", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class aboutDlg: public Ui_aboutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDLG_H
