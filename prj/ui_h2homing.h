/********************************************************************************
** Form generated from reading UI file 'h2homing.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2HOMING_H
#define UI_H2HOMING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2Homing
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox_movement;
    QLabel *label_3;
    QComboBox *comboBox_target;
    QLabel *label;
    QLabel *label_direction;
    QLabel *label_tips;
    QLabel *label_info;
    QLabel *label_picture;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_SearchVelocity;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_ForceLimit;

    void setupUi(QWidget *H2Homing)
    {
        if (H2Homing->objectName().isEmpty())
            H2Homing->setObjectName(QStringLiteral("H2Homing"));
        H2Homing->resize(716, 382);
        gridLayout_2 = new QGridLayout(H2Homing);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox = new QGroupBox(H2Homing);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(400, 196));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(80, 20));
        label_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox_movement = new QComboBox(groupBox);
        comboBox_movement->addItem(QString());
        comboBox_movement->setObjectName(QStringLiteral("comboBox_movement"));
        sizePolicy.setHeightForWidth(comboBox_movement->sizePolicy().hasHeightForWidth());
        comboBox_movement->setSizePolicy(sizePolicy);
        comboBox_movement->setMinimumSize(QSize(240, 20));
        comboBox_movement->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(comboBox_movement, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(80, 20));
        label_3->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        comboBox_target = new QComboBox(groupBox);
        comboBox_target->addItem(QString());
        comboBox_target->setObjectName(QStringLiteral("comboBox_target"));
        sizePolicy.setHeightForWidth(comboBox_target->sizePolicy().hasHeightForWidth());
        comboBox_target->setSizePolicy(sizePolicy);
        comboBox_target->setMinimumSize(QSize(240, 20));
        comboBox_target->setMaximumSize(QSize(16777215, 16777215));
        comboBox_target->setEditable(false);
        comboBox_target->setFrame(true);

        gridLayout->addWidget(comboBox_target, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(80, 20));
        label->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_direction = new QLabel(groupBox);
        label_direction->setObjectName(QStringLiteral("label_direction"));
        sizePolicy.setHeightForWidth(label_direction->sizePolicy().hasHeightForWidth());
        label_direction->setSizePolicy(sizePolicy);
        label_direction->setMinimumSize(QSize(240, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_direction->setFont(font);
        label_direction->setText(QStringLiteral("Comer Point 1"));

        gridLayout->addWidget(label_direction, 1, 1, 1, 1);

        label_tips = new QLabel(groupBox);
        label_tips->setObjectName(QStringLiteral("label_tips"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_tips->sizePolicy().hasHeightForWidth());
        label_tips->setSizePolicy(sizePolicy1);
        label_tips->setStyleSheet(QStringLiteral(""));
        label_tips->setPixmap(QPixmap(QString::fromUtf8(":/res/image/h2homing/info.png")));
        label_tips->setScaledContents(false);
        label_tips->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_tips, 4, 0, 1, 1);

        label_info = new QLabel(groupBox);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setTextFormat(Qt::PlainText);
        label_info->setWordWrap(true);

        gridLayout->addWidget(label_info, 4, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        label_picture = new QLabel(H2Homing);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_picture->sizePolicy().hasHeightForWidth());
        label_picture->setSizePolicy(sizePolicy2);
        label_picture->setMinimumSize(QSize(100, 100));
        label_picture->setFrameShape(QFrame::Box);
        label_picture->setPixmap(QPixmap(QString::fromUtf8(":/res/image/h2homing/dir_X_Y.PNG")));

        gridLayout_2->addWidget(label_picture, 0, 1, 2, 1);

        groupBox_2 = new QGroupBox(H2Homing);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(400, 90));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(120, 20));
        label_5->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        doubleSpinBox_SearchVelocity = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_SearchVelocity->setObjectName(QStringLiteral("doubleSpinBox_SearchVelocity"));
        sizePolicy.setHeightForWidth(doubleSpinBox_SearchVelocity->sizePolicy().hasHeightForWidth());
        doubleSpinBox_SearchVelocity->setSizePolicy(sizePolicy);
        doubleSpinBox_SearchVelocity->setMinimumSize(QSize(200, 20));
        doubleSpinBox_SearchVelocity->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_SearchVelocity->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_SearchVelocity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_SearchVelocity->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_SearchVelocity->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_SearchVelocity->setPrefix(QStringLiteral(""));
        doubleSpinBox_SearchVelocity->setSuffix(QStringLiteral(" mm/s"));
        doubleSpinBox_SearchVelocity->setDecimals(2);
        doubleSpinBox_SearchVelocity->setMinimum(0.1);
        doubleSpinBox_SearchVelocity->setMaximum(10000);
        doubleSpinBox_SearchVelocity->setValue(50);

        gridLayout_3->addWidget(doubleSpinBox_SearchVelocity, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(120, 20));
        label_7->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBox_ForceLimit = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_ForceLimit->setObjectName(QStringLiteral("doubleSpinBox_ForceLimit"));
        sizePolicy.setHeightForWidth(doubleSpinBox_ForceLimit->sizePolicy().hasHeightForWidth());
        doubleSpinBox_ForceLimit->setSizePolicy(sizePolicy);
        doubleSpinBox_ForceLimit->setMinimumSize(QSize(200, 20));
        doubleSpinBox_ForceLimit->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_ForceLimit->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_ForceLimit->setFrame(true);
        doubleSpinBox_ForceLimit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_ForceLimit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_ForceLimit->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_ForceLimit->setPrefix(QStringLiteral(""));
        doubleSpinBox_ForceLimit->setSuffix(QStringLiteral(" %"));
        doubleSpinBox_ForceLimit->setDecimals(1);
        doubleSpinBox_ForceLimit->setMinimum(0.1);
        doubleSpinBox_ForceLimit->setValue(75);

        gridLayout_3->addWidget(doubleSpinBox_ForceLimit, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_2->raise();
        groupBox->raise();
        label_picture->raise();

        retranslateUi(H2Homing);

        QMetaObject::connectSlotsByName(H2Homing);
    } // setupUi

    void retranslateUi(QWidget *H2Homing)
    {
        H2Homing->setWindowTitle(QApplication::translate("H2Homing", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("H2Homing", "Homing Method", nullptr));
        label_2->setText(QApplication::translate("H2Homing", "Direction:", nullptr));
        comboBox_movement->setItemText(0, QApplication::translate("H2Homing", "First in direction of X,then Y", nullptr));

        label_3->setText(QApplication::translate("H2Homing", "Movement:", nullptr));
        comboBox_target->setItemText(0, QApplication::translate("H2Homing", "Block", nullptr));

        label->setText(QApplication::translate("H2Homing", "Target:", nullptr));
        label_tips->setText(QString());
        label_info->setText(QApplication::translate("H2Homing", "Homing is always executed in dirrection of the corner,where the Axis Zero Point is defined to be.", nullptr));
        label_picture->setText(QString());
        groupBox_2->setTitle(QApplication::translate("H2Homing", "Parameters", nullptr));
        label_5->setText(QApplication::translate("H2Homing", "Search Velocity:", nullptr));
        label_7->setText(QApplication::translate("H2Homing", "Force Limit:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2Homing: public Ui_H2Homing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2HOMING_H
