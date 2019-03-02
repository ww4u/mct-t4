/********************************************************************************
** Form generated from reading UI file 'h2measurement.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2MEASUREMENT_H
#define UI_H2MEASUREMENT_H

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

class Ui_H2Measurement
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label_picture;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_Coordinate;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox_AxesZeroPoint;
    QGroupBox *groupBox_Zero_End_point;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_swlp_Y;
    QDoubleSpinBox *doubleSpinBox_swln_X;
    QDoubleSpinBox *doubleSpinBox_pzpX;
    QDoubleSpinBox *doubleSpinBox_pzpY;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_swlp_X;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_swln_Y;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *H2Measurement)
    {
        if (H2Measurement->objectName().isEmpty())
            H2Measurement->setObjectName(QStringLiteral("H2Measurement"));
        H2Measurement->resize(873, 425);
        H2Measurement->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        gridLayout_3 = new QGridLayout(H2Measurement);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        label_picture = new QLabel(H2Measurement);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setMinimumSize(QSize(100, 100));
        label_picture->setFrameShape(QFrame::Box);
        label_picture->setPixmap(QPixmap(QString::fromUtf8(":/res/image/h2measurement/CornerPoint1.PNG")));
        label_picture->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_picture, 0, 1, 2, 1);

        verticalSpacer = new QSpacerItem(20, 280, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox_Coordinate = new QGroupBox(H2Measurement);
        groupBox_Coordinate->setObjectName(QStringLiteral("groupBox_Coordinate"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_Coordinate->sizePolicy().hasHeightForWidth());
        groupBox_Coordinate->setSizePolicy(sizePolicy);
        groupBox_Coordinate->setMinimumSize(QSize(390, 70));
        groupBox_Coordinate->setMaximumSize(QSize(400, 90));
        gridLayout = new QGridLayout(groupBox_Coordinate);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox_Coordinate);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(120, 20));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox_AxesZeroPoint = new QComboBox(groupBox_Coordinate);
        comboBox_AxesZeroPoint->addItem(QString());
        comboBox_AxesZeroPoint->addItem(QString());
        comboBox_AxesZeroPoint->addItem(QString());
        comboBox_AxesZeroPoint->addItem(QString());
        comboBox_AxesZeroPoint->setObjectName(QStringLiteral("comboBox_AxesZeroPoint"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_AxesZeroPoint->sizePolicy().hasHeightForWidth());
        comboBox_AxesZeroPoint->setSizePolicy(sizePolicy2);
        comboBox_AxesZeroPoint->setMinimumSize(QSize(240, 20));
        comboBox_AxesZeroPoint->setFocusPolicy(Qt::ClickFocus);
        comboBox_AxesZeroPoint->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(comboBox_AxesZeroPoint, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_Coordinate, 0, 0, 1, 1);

        groupBox_Zero_End_point = new QGroupBox(H2Measurement);
        groupBox_Zero_End_point->setObjectName(QStringLiteral("groupBox_Zero_End_point"));
        groupBox_Zero_End_point->setMinimumSize(QSize(390, 160));
        groupBox_Zero_End_point->setMaximumSize(QSize(400, 180));
        gridLayout_4 = new QGridLayout(groupBox_Zero_End_point);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_7 = new QLabel(groupBox_Zero_End_point);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);
        label_7->setMinimumSize(QSize(120, 20));

        gridLayout_4->addWidget(label_7, 4, 0, 1, 1);

        doubleSpinBox_swlp_Y = new QDoubleSpinBox(groupBox_Zero_End_point);
        doubleSpinBox_swlp_Y->setObjectName(QStringLiteral("doubleSpinBox_swlp_Y"));
        sizePolicy3.setHeightForWidth(doubleSpinBox_swlp_Y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_swlp_Y->setSizePolicy(sizePolicy3);
        doubleSpinBox_swlp_Y->setMinimumSize(QSize(120, 20));
        doubleSpinBox_swlp_Y->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_swlp_Y->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_swlp_Y->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_swlp_Y->setStyleSheet(QStringLiteral(""));
        doubleSpinBox_swlp_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_swlp_Y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_swlp_Y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_swlp_Y->setAccelerated(false);
        doubleSpinBox_swlp_Y->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_swlp_Y->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_swlp_Y->setMaximum(10000);

        gridLayout_4->addWidget(doubleSpinBox_swlp_Y, 4, 3, 1, 1);

        doubleSpinBox_swln_X = new QDoubleSpinBox(groupBox_Zero_End_point);
        doubleSpinBox_swln_X->setObjectName(QStringLiteral("doubleSpinBox_swln_X"));
        sizePolicy3.setHeightForWidth(doubleSpinBox_swln_X->sizePolicy().hasHeightForWidth());
        doubleSpinBox_swln_X->setSizePolicy(sizePolicy3);
        doubleSpinBox_swln_X->setMinimumSize(QSize(120, 20));
        doubleSpinBox_swln_X->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_swln_X->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_swln_X->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_swln_X->setStyleSheet(QStringLiteral(""));
        doubleSpinBox_swln_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_swln_X->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_swln_X->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_swln_X->setAccelerated(false);
        doubleSpinBox_swln_X->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_swln_X->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_swln_X->setMaximum(10000);

        gridLayout_4->addWidget(doubleSpinBox_swln_X, 5, 2, 1, 1);

        doubleSpinBox_pzpX = new QDoubleSpinBox(groupBox_Zero_End_point);
        doubleSpinBox_pzpX->setObjectName(QStringLiteral("doubleSpinBox_pzpX"));
        sizePolicy3.setHeightForWidth(doubleSpinBox_pzpX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_pzpX->setSizePolicy(sizePolicy3);
        doubleSpinBox_pzpX->setMinimumSize(QSize(120, 20));
        doubleSpinBox_pzpX->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_pzpX->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_pzpX->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_pzpX->setStyleSheet(QStringLiteral(""));
        doubleSpinBox_pzpX->setInputMethodHints(Qt::ImhNone);
        doubleSpinBox_pzpX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_pzpX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_pzpX->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_pzpX->setAccelerated(false);
        doubleSpinBox_pzpX->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_pzpX->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_pzpX->setMaximum(10000);

        gridLayout_4->addWidget(doubleSpinBox_pzpX, 2, 2, 1, 1);

        doubleSpinBox_pzpY = new QDoubleSpinBox(groupBox_Zero_End_point);
        doubleSpinBox_pzpY->setObjectName(QStringLiteral("doubleSpinBox_pzpY"));
        sizePolicy3.setHeightForWidth(doubleSpinBox_pzpY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_pzpY->setSizePolicy(sizePolicy3);
        doubleSpinBox_pzpY->setMinimumSize(QSize(120, 20));
        doubleSpinBox_pzpY->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_pzpY->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_pzpY->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_pzpY->setStyleSheet(QStringLiteral(""));
        doubleSpinBox_pzpY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_pzpY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_pzpY->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_pzpY->setAccelerated(false);
        doubleSpinBox_pzpY->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_pzpY->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_pzpY->setMaximum(10000);

        gridLayout_4->addWidget(doubleSpinBox_pzpY, 2, 3, 1, 1);

        label_9 = new QLabel(groupBox_Zero_End_point);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setMinimumSize(QSize(120, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_9, 0, 1, 1, 2);

        label_6 = new QLabel(groupBox_Zero_End_point);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setMinimumSize(QSize(120, 20));

        gridLayout_4->addWidget(label_6, 2, 0, 1, 2);

        label_8 = new QLabel(groupBox_Zero_End_point);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);
        label_8->setMinimumSize(QSize(120, 20));

        gridLayout_4->addWidget(label_8, 5, 0, 1, 1);

        doubleSpinBox_swlp_X = new QDoubleSpinBox(groupBox_Zero_End_point);
        doubleSpinBox_swlp_X->setObjectName(QStringLiteral("doubleSpinBox_swlp_X"));
        sizePolicy3.setHeightForWidth(doubleSpinBox_swlp_X->sizePolicy().hasHeightForWidth());
        doubleSpinBox_swlp_X->setSizePolicy(sizePolicy3);
        doubleSpinBox_swlp_X->setMinimumSize(QSize(120, 20));
        doubleSpinBox_swlp_X->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_swlp_X->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_swlp_X->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_swlp_X->setStyleSheet(QStringLiteral(""));
        doubleSpinBox_swlp_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_swlp_X->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_swlp_X->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_swlp_X->setAccelerated(false);
        doubleSpinBox_swlp_X->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_swlp_X->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_swlp_X->setMaximum(10000);

        gridLayout_4->addWidget(doubleSpinBox_swlp_X, 4, 2, 1, 1);

        label_10 = new QLabel(groupBox_Zero_End_point);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);
        label_10->setMinimumSize(QSize(120, 20));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_10, 0, 3, 1, 1);

        doubleSpinBox_swln_Y = new QDoubleSpinBox(groupBox_Zero_End_point);
        doubleSpinBox_swln_Y->setObjectName(QStringLiteral("doubleSpinBox_swln_Y"));
        sizePolicy3.setHeightForWidth(doubleSpinBox_swln_Y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_swln_Y->setSizePolicy(sizePolicy3);
        doubleSpinBox_swln_Y->setMinimumSize(QSize(120, 20));
        doubleSpinBox_swln_Y->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_swln_Y->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_swln_Y->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_swln_Y->setStyleSheet(QStringLiteral(""));
        doubleSpinBox_swln_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_swln_Y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_swln_Y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_swln_Y->setAccelerated(false);
        doubleSpinBox_swln_Y->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_swln_Y->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_swln_Y->setMaximum(10000);

        gridLayout_4->addWidget(doubleSpinBox_swln_Y, 5, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_7->raise();
        doubleSpinBox_swlp_Y->raise();
        doubleSpinBox_pzpY->raise();
        label_9->raise();
        label_6->raise();
        label_8->raise();
        doubleSpinBox_swlp_X->raise();
        label_10->raise();
        doubleSpinBox_swln_Y->raise();
        doubleSpinBox_swln_X->raise();
        doubleSpinBox_pzpX->raise();

        gridLayout_3->addWidget(groupBox_Zero_End_point, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 2, 2, 1);


        retranslateUi(H2Measurement);

        QMetaObject::connectSlotsByName(H2Measurement);
    } // setupUi

    void retranslateUi(QWidget *H2Measurement)
    {
        H2Measurement->setWindowTitle(QApplication::translate("H2Measurement", "Form", nullptr));
        groupBox_Coordinate->setTitle(QApplication::translate("H2Measurement", "Coordinate System", nullptr));
        label->setText(QApplication::translate("H2Measurement", "Axes Zero Point:", nullptr));
        comboBox_AxesZeroPoint->setItemText(0, QApplication::translate("H2Measurement", "Corner Point 1", nullptr));
        comboBox_AxesZeroPoint->setItemText(1, QApplication::translate("H2Measurement", "Corner Point 2", nullptr));
        comboBox_AxesZeroPoint->setItemText(2, QApplication::translate("H2Measurement", "Corner Point 3", nullptr));
        comboBox_AxesZeroPoint->setItemText(3, QApplication::translate("H2Measurement", "Corner Point 4", nullptr));

        groupBox_Zero_End_point->setTitle(QApplication::translate("H2Measurement", "Zero Points and End Positions", nullptr));
        label_7->setText(QApplication::translate("H2Measurement", "SW Limit Positive:", nullptr));
        label_9->setText(QApplication::translate("H2Measurement", "X-Axis", nullptr));
        label_6->setText(QApplication::translate("H2Measurement", "Project Zero Point:", nullptr));
        label_8->setText(QApplication::translate("H2Measurement", "SW Limit Negative:", nullptr));
        label_10->setText(QApplication::translate("H2Measurement", "Y-Axis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2Measurement: public Ui_H2Measurement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2MEASUREMENT_H
