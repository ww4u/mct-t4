/********************************************************************************
** Form generated from reading UI file 'h2jogmode.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2JOGMODE_H
#define UI_H2JOGMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2JogMode
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_222;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *doubleSpinBox_CrawlingVelocity;
    QLabel *label_111;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_CrawlingTime;
    QDoubleSpinBox *doubleSpinBox_MaximumVelocity;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_picture;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *H2JogMode)
    {
        if (H2JogMode->objectName().isEmpty())
            H2JogMode->setObjectName(QStringLiteral("H2JogMode"));
        H2JogMode->resize(679, 382);
        gridLayout = new QGridLayout(H2JogMode);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        groupBox_222 = new QGroupBox(H2JogMode);
        groupBox_222->setObjectName(QStringLiteral("groupBox_222"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_222->sizePolicy().hasHeightForWidth());
        groupBox_222->setSizePolicy(sizePolicy);
        groupBox_222->setMinimumSize(QSize(290, 200));
        groupBox_222->setMaximumSize(QSize(16777215, 300));
        gridLayout_3 = new QGridLayout(groupBox_222);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        doubleSpinBox_CrawlingVelocity = new QDoubleSpinBox(groupBox_222);
        doubleSpinBox_CrawlingVelocity->setObjectName(QStringLiteral("doubleSpinBox_CrawlingVelocity"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox_CrawlingVelocity->sizePolicy().hasHeightForWidth());
        doubleSpinBox_CrawlingVelocity->setSizePolicy(sizePolicy1);
        doubleSpinBox_CrawlingVelocity->setMinimumSize(QSize(130, 20));
        doubleSpinBox_CrawlingVelocity->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_CrawlingVelocity->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_CrawlingVelocity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_CrawlingVelocity->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_CrawlingVelocity->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_CrawlingVelocity->setSuffix(QStringLiteral(" mm/s"));
        doubleSpinBox_CrawlingVelocity->setMinimum(0.1);
        doubleSpinBox_CrawlingVelocity->setMaximum(10000);
        doubleSpinBox_CrawlingVelocity->setValue(10);

        gridLayout_3->addWidget(doubleSpinBox_CrawlingVelocity, 1, 1, 1, 1);

        label_111 = new QLabel(groupBox_222);
        label_111->setObjectName(QStringLiteral("label_111"));
        sizePolicy1.setHeightForWidth(label_111->sizePolicy().hasHeightForWidth());
        label_111->setSizePolicy(sizePolicy1);
        label_111->setMinimumSize(QSize(130, 20));

        gridLayout_3->addWidget(label_111, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox_222);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(130, 20));

        gridLayout_3->addWidget(label_2, 3, 0, 1, 1);

        doubleSpinBox_CrawlingTime = new QDoubleSpinBox(groupBox_222);
        doubleSpinBox_CrawlingTime->setObjectName(QStringLiteral("doubleSpinBox_CrawlingTime"));
        sizePolicy1.setHeightForWidth(doubleSpinBox_CrawlingTime->sizePolicy().hasHeightForWidth());
        doubleSpinBox_CrawlingTime->setSizePolicy(sizePolicy1);
        doubleSpinBox_CrawlingTime->setMinimumSize(QSize(130, 20));
        doubleSpinBox_CrawlingTime->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_CrawlingTime->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_CrawlingTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_CrawlingTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_CrawlingTime->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_CrawlingTime->setSuffix(QStringLiteral(" ms"));
        doubleSpinBox_CrawlingTime->setDecimals(0);
        doubleSpinBox_CrawlingTime->setMinimum(1);
        doubleSpinBox_CrawlingTime->setMaximum(10000);
        doubleSpinBox_CrawlingTime->setValue(1000);

        gridLayout_3->addWidget(doubleSpinBox_CrawlingTime, 3, 1, 1, 1);

        doubleSpinBox_MaximumVelocity = new QDoubleSpinBox(groupBox_222);
        doubleSpinBox_MaximumVelocity->setObjectName(QStringLiteral("doubleSpinBox_MaximumVelocity"));
        sizePolicy1.setHeightForWidth(doubleSpinBox_MaximumVelocity->sizePolicy().hasHeightForWidth());
        doubleSpinBox_MaximumVelocity->setSizePolicy(sizePolicy1);
        doubleSpinBox_MaximumVelocity->setMinimumSize(QSize(130, 20));
        doubleSpinBox_MaximumVelocity->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_MaximumVelocity->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_MaximumVelocity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_MaximumVelocity->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_MaximumVelocity->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_MaximumVelocity->setSuffix(QStringLiteral(" mm/s"));
        doubleSpinBox_MaximumVelocity->setMinimum(0.1);
        doubleSpinBox_MaximumVelocity->setMaximum(10000);
        doubleSpinBox_MaximumVelocity->setValue(100);

        gridLayout_3->addWidget(doubleSpinBox_MaximumVelocity, 5, 1, 1, 1);

        label_3 = new QLabel(groupBox_222);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(130, 20));

        gridLayout_3->addWidget(label_3, 5, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 6, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 4, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 2, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 0, 1, 2);


        gridLayout->addWidget(groupBox_222, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        label_picture = new QLabel(H2JogMode);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setMinimumSize(QSize(100, 100));
        label_picture->setFrameShape(QFrame::Box);
        label_picture->setPixmap(QPixmap(QString::fromUtf8(":/res/image/icon/jogmode.PNG")));

        gridLayout->addWidget(label_picture, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 183, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 2);


        retranslateUi(H2JogMode);

        QMetaObject::connectSlotsByName(H2JogMode);
    } // setupUi

    void retranslateUi(QWidget *H2JogMode)
    {
        H2JogMode->setWindowTitle(QApplication::translate("H2JogMode", "Form", nullptr));
        groupBox_222->setTitle(QApplication::translate("H2JogMode", "Jog Mode", nullptr));
        label_111->setText(QApplication::translate("H2JogMode", "Crawling Velocity:", nullptr));
        label_2->setText(QApplication::translate("H2JogMode", "Crawling Time:", nullptr));
        label_3->setText(QApplication::translate("H2JogMode", "Maximum Velocity:", nullptr));
        label_picture->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class H2JogMode: public Ui_H2JogMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2JOGMODE_H
