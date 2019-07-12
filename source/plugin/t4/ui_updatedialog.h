/********************************************************************************
** Form generated from reading UI file 'updatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDIALOG_H
#define UI_UPDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QToolButton *toolButton;
    QProgressBar *progressBar;
    QLineEdit *desLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnShow;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;
    QLabel *labelStatus;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(517, 302);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(300, 150));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(false);

        horizontalLayout->addWidget(lineEdit);

        toolButton = new QToolButton(Widget);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);

        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(progressBar);

        desLineEdit = new QLineEdit(Widget);
        desLineEdit->setObjectName(QStringLiteral("desLineEdit"));
        desLineEdit->setReadOnly(true);

        verticalLayout->addWidget(desLineEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnShow = new QPushButton(Widget);
        btnShow->setObjectName(QStringLiteral("btnShow"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnShow->sizePolicy().hasHeightForWidth());
        btnShow->setSizePolicy(sizePolicy2);
        btnShow->setMinimumSize(QSize(50, 0));
        btnShow->setCheckable(true);
        btnShow->setChecked(true);

        horizontalLayout_3->addWidget(btnShow);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy3);
        textBrowser->setMinimumSize(QSize(100, 50));
        textBrowser->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(Widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        sizePolicy2.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy2);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);

        labelStatus = new QLabel(Widget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        sizePolicy.setHeightForWidth(labelStatus->sizePolicy().hasHeightForWidth());
        labelStatus->setSizePolicy(sizePolicy);
        labelStatus->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(labelStatus);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QDialog *Widget)
    {
        label_2->setText(QApplication::translate("Widget", "FilePath", nullptr));
        toolButton->setText(QApplication::translate("Widget", "...", nullptr));
        btnShow->setText(QApplication::translate("Widget", "Show detail", nullptr));
        labelStatus->setText(QString());
        Q_UNUSED(Widget);
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDIALOG_H
