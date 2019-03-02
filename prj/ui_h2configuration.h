/********************************************************************************
** Form generated from reading UI file 'h2configuration.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2CONFIGURATION_H
#define UI_H2CONFIGURATION_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2Configuration
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_picture;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *workSpaceStrokeXLabel;
    QLabel *label_family;
    QLabel *workSpaceStrokeYLabel;
    QLabel *sizeLabel;
    QLabel *label_2;
    QLabel *label_model;
    QComboBox *sizeComboBox;
    QSpacerItem *verticalSpacer_2;
    QDoubleSpinBox *doubleSpinBox_X;
    QDoubleSpinBox *doubleSpinBox_Y;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_motorPos;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_b;
    QRadioButton *radioButton_t;

    void setupUi(QWidget *H2Configuration)
    {
        if (H2Configuration->objectName().isEmpty())
            H2Configuration->setObjectName(QStringLiteral("H2Configuration"));
        H2Configuration->resize(609, 383);
        H2Configuration->setBaseSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(H2Configuration);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        label_picture = new QLabel(H2Configuration);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_picture->sizePolicy().hasHeightForWidth());
        label_picture->setSizePolicy(sizePolicy);
        label_picture->setMinimumSize(QSize(100, 100));
        label_picture->setStyleSheet(QStringLiteral(""));
        label_picture->setFrameShape(QFrame::Box);
        label_picture->setPixmap(QPixmap(QString::fromUtf8(":/res/image/h2configuration/size_bottom.png")));
        label_picture->setScaledContents(false);

        gridLayout_2->addWidget(label_picture, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        groupBox_3 = new QGroupBox(H2Configuration);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(304, 200));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(6);
        workSpaceStrokeXLabel = new QLabel(groupBox_3);
        workSpaceStrokeXLabel->setObjectName(QStringLiteral("workSpaceStrokeXLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(workSpaceStrokeXLabel->sizePolicy().hasHeightForWidth());
        workSpaceStrokeXLabel->setSizePolicy(sizePolicy1);
        workSpaceStrokeXLabel->setMinimumSize(QSize(140, 20));

        gridLayout_3->addWidget(workSpaceStrokeXLabel, 4, 0, 1, 1);

        label_family = new QLabel(groupBox_3);
        label_family->setObjectName(QStringLiteral("label_family"));
        sizePolicy1.setHeightForWidth(label_family->sizePolicy().hasHeightForWidth());
        label_family->setSizePolicy(sizePolicy1);
        label_family->setMinimumSize(QSize(120, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_family->setFont(font);
        label_family->setText(QStringLiteral("label"));

        gridLayout_3->addWidget(label_family, 2, 1, 1, 1);

        workSpaceStrokeYLabel = new QLabel(groupBox_3);
        workSpaceStrokeYLabel->setObjectName(QStringLiteral("workSpaceStrokeYLabel"));
        sizePolicy1.setHeightForWidth(workSpaceStrokeYLabel->sizePolicy().hasHeightForWidth());
        workSpaceStrokeYLabel->setSizePolicy(sizePolicy1);
        workSpaceStrokeYLabel->setMinimumSize(QSize(140, 20));

        gridLayout_3->addWidget(workSpaceStrokeYLabel, 5, 0, 1, 1);

        sizeLabel = new QLabel(groupBox_3);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));
        sizePolicy1.setHeightForWidth(sizeLabel->sizePolicy().hasHeightForWidth());
        sizeLabel->setSizePolicy(sizePolicy1);
        sizeLabel->setMinimumSize(QSize(140, 20));

        gridLayout_3->addWidget(sizeLabel, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(140, 20));

        gridLayout_3->addWidget(label_2, 2, 0, 1, 1);

        label_model = new QLabel(groupBox_3);
        label_model->setObjectName(QStringLiteral("label_model"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_model->sizePolicy().hasHeightForWidth());
        label_model->setSizePolicy(sizePolicy2);
        label_model->setMinimumSize(QSize(0, 24));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_model->setFont(font1);
        label_model->setText(QStringLiteral("MRX-H2-M"));
        label_model->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_model, 0, 0, 1, 2);

        sizeComboBox = new QComboBox(groupBox_3);
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->setObjectName(QStringLiteral("sizeComboBox"));
        sizePolicy1.setHeightForWidth(sizeComboBox->sizePolicy().hasHeightForWidth());
        sizeComboBox->setSizePolicy(sizePolicy1);
        sizeComboBox->setMinimumSize(QSize(120, 20));
        sizeComboBox->setMaximumSize(QSize(16777215, 16777215));
        sizeComboBox->setFocusPolicy(Qt::ClickFocus);
        sizeComboBox->setEditable(false);
        sizeComboBox->setIconSize(QSize(16, 16));

        gridLayout_3->addWidget(sizeComboBox, 3, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 6, 0, 1, 2);

        doubleSpinBox_X = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_X->setObjectName(QStringLiteral("doubleSpinBox_X"));
        sizePolicy1.setHeightForWidth(doubleSpinBox_X->sizePolicy().hasHeightForWidth());
        doubleSpinBox_X->setSizePolicy(sizePolicy1);
        doubleSpinBox_X->setMinimumSize(QSize(120, 20));
        doubleSpinBox_X->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_X->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_X->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_X->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        doubleSpinBox_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_X->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_X->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_X->setMaximum(100000);

        gridLayout_3->addWidget(doubleSpinBox_X, 4, 1, 1, 2);

        doubleSpinBox_Y = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_Y->setObjectName(QStringLiteral("doubleSpinBox_Y"));
        sizePolicy1.setHeightForWidth(doubleSpinBox_Y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Y->setSizePolicy(sizePolicy1);
        doubleSpinBox_Y->setMinimumSize(QSize(120, 20));
        doubleSpinBox_Y->setMaximumSize(QSize(16777215, 16777215));
        doubleSpinBox_Y->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_Y->setFocusPolicy(Qt::ClickFocus);
        doubleSpinBox_Y->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        doubleSpinBox_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_Y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_Y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_Y->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_Y->setMaximum(100000);

        gridLayout_3->addWidget(doubleSpinBox_Y, 5, 1, 1, 2);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        groupBox_motorPos = new QGroupBox(H2Configuration);
        groupBox_motorPos->setObjectName(QStringLiteral("groupBox_motorPos"));
        groupBox_motorPos->setMinimumSize(QSize(302, 80));
        verticalLayout_3 = new QVBoxLayout(groupBox_motorPos);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton_b = new QRadioButton(groupBox_motorPos);
        radioButton_b->setObjectName(QStringLiteral("radioButton_b"));
        sizePolicy2.setHeightForWidth(radioButton_b->sizePolicy().hasHeightForWidth());
        radioButton_b->setSizePolicy(sizePolicy2);
        radioButton_b->setMinimumSize(QSize(0, 20));
        radioButton_b->setChecked(true);

        verticalLayout_3->addWidget(radioButton_b);

        radioButton_t = new QRadioButton(groupBox_motorPos);
        radioButton_t->setObjectName(QStringLiteral("radioButton_t"));
        sizePolicy2.setHeightForWidth(radioButton_t->sizePolicy().hasHeightForWidth());
        radioButton_t->setSizePolicy(sizePolicy2);
        radioButton_t->setMinimumSize(QSize(0, 20));

        verticalLayout_3->addWidget(radioButton_t);


        gridLayout_2->addWidget(groupBox_motorPos, 1, 0, 1, 1);


        retranslateUi(H2Configuration);

        QMetaObject::connectSlotsByName(H2Configuration);
    } // setupUi

    void retranslateUi(QWidget *H2Configuration)
    {
        H2Configuration->setWindowTitle(QApplication::translate("H2Configuration", "Form", nullptr));
        label_picture->setText(QString());
        groupBox_3->setTitle(QApplication::translate("H2Configuration", "Mechanics", nullptr));
        workSpaceStrokeXLabel->setText(QApplication::translate("H2Configuration", "WorkSpace X-Stroke:", nullptr));
        workSpaceStrokeYLabel->setText(QApplication::translate("H2Configuration", "WorkSpace Y-Stroke:", nullptr));
        sizeLabel->setText(QApplication::translate("H2Configuration", "Size:", nullptr));
        label_2->setText(QApplication::translate("H2Configuration", "Family:", nullptr));
        sizeComboBox->setItemText(0, QApplication::translate("H2Configuration", "Small", nullptr));
        sizeComboBox->setItemText(1, QApplication::translate("H2Configuration", "Big", nullptr));

        doubleSpinBox_X->setSuffix(QApplication::translate("H2Configuration", " mm", nullptr));
        doubleSpinBox_Y->setSuffix(QApplication::translate("H2Configuration", " mm", nullptr));
        groupBox_motorPos->setTitle(QApplication::translate("H2Configuration", "Motor Position", nullptr));
        radioButton_b->setText(QApplication::translate("H2Configuration", "Bottom(B)", nullptr));
        radioButton_t->setText(QApplication::translate("H2Configuration", "Top(T)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2Configuration: public Ui_H2Configuration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2CONFIGURATION_H
