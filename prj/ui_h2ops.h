/********************************************************************************
** Form generated from reading UI file 'h2ops.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2OPS_H
#define UI_H2OPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "h2status.h"
#include "xconfig.h"

QT_BEGIN_NAMESPACE

class Ui_H2Ops
{
public:
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_4;
    H2Status *h2Status;
    QTabWidget *tabWidget;
    XConfig *tab_LogOut;
    QVBoxLayout *verticalLayout_3;
    QListWidget *lstLogout;
    XConfig *tab_Operate;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_11;
    QDoubleSpinBox *doubleSpinBox_target_position_y;
    QDoubleSpinBox *doubleSpinBox_Mileage_x;
    QLabel *label_17;
    QLabel *label_13;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_target_position_x;
    QDoubleSpinBox *doubleSpinBox_actual_position_y;
    QLabel *label_16;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBox_Mileage_y;
    QLabel *label_15;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_actual_position_x;
    QDoubleSpinBox *doubleSpinBox_RecordNumber;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_12;
    QRadioButton *radES;
    QRadioButton *radHome;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    XConfig *tab_DigitalIO;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_11;
    QRadioButton *radioButton_12;
    QRadioButton *radioButton_10;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QLabel *label_4;
    QLabel *label_recordNumber;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton_moiton_complete;
    QRadioButton *radioButton_load_voltage;
    QRadioButton *radioButton_acknowledge_start;
    QRadioButton *radioButton_fault;
    QRadioButton *radioButton_ready;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    XConfig *tab_Homing;
    QGridLayout *gridLayout_13;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_14;
    QRadioButton *radioButton_homing_valid;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBox_homing_actual_pos_x;
    QLabel *label_20;
    QDoubleSpinBox *doubleSpinBox_homing_actual_pos_y;
    QLabel *label_22;
    QPushButton *pushButton_starting_home;
    QLabel *label_21;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_homing_direction;
    QLabel *label_homing_target;
    QPushButton *pushButton_go_prjZero;
    XConfig *tab_Manual;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QToolButton *toolButton_singlestep_x_inc;
    QToolButton *toolButton_singlestep_y_dec;
    QLabel *label_5;
    QLabel *label_3;
    QToolButton *toolButton_singlestep_x_dec;
    QToolButton *toolButton_jogmode_y_dec;
    QLabel *label_8;
    QToolButton *toolButton_jogmode_x_dec;
    QToolButton *toolButton_singlestep_y_inc;
    QToolButton *toolButton_jogmode_x_inc;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_Velocity;
    QDoubleSpinBox *doubleSpinBox_Increament;
    QToolButton *toolButton_jogmode_y_inc;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_apply;
    QLabel *label_6;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_currentPos_y;
    QDoubleSpinBox *doubleSpinBox_currentPos_x;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    XConfig *tab_Monitor;
    QHBoxLayout *horizontalLayout_3;
    XConfig *tab_Debug;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_5;
    QLabel *label_9;
    QTableView *tvDebug;
    QToolButton *toolButton_debugRun;
    QToolButton *btnImport;
    QSpacerItem *horizontalSpacer_6;
    QToolButton *btnDown;
    QToolButton *btnUp;
    QToolButton *btnExport;
    QCheckBox *chkCyclic;
    QDoubleSpinBox *spinDly;
    QToolButton *btnClr;
    QToolButton *btnDel;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *btnAdd;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_23;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *doubleSpinBox_debugRecord;
    QDoubleSpinBox *doubleSpinBox_debug_posX;
    QDoubleSpinBox *doubleSpinBox_debug_posY;
    XConfig *tab_Diagnosis;
    QGridLayout *gridLayout_10;
    QToolButton *btnRead;
    QToolButton *btnDelete;
    QTableView *tvDiagnosis;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *btnExport_2;

    void setupUi(QWidget *H2Ops)
    {
        if (H2Ops->objectName().isEmpty())
            H2Ops->setObjectName(QStringLiteral("H2Ops"));
        H2Ops->resize(905, 270);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(H2Ops->sizePolicy().hasHeightForWidth());
        H2Ops->setSizePolicy(sizePolicy);
        H2Ops->setMinimumSize(QSize(0, 270));
        H2Ops->setMaximumSize(QSize(16777215, 600));
        H2Ops->setFocusPolicy(Qt::StrongFocus);
        horizontalLayout_2 = new QHBoxLayout(H2Ops);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 6, 9, 6);
        scrollArea = new QScrollArea(H2Ops);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 257));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 887, 258));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 240));
        horizontalLayout_4 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        h2Status = new H2Status(scrollAreaWidgetContents);
        h2Status->setObjectName(QStringLiteral("h2Status"));
        h2Status->setMinimumSize(QSize(0, 240));

        horizontalLayout_4->addWidget(h2Status);

        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 240));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setMovable(false);
        tab_LogOut = new XConfig();
        tab_LogOut->setObjectName(QStringLiteral("tab_LogOut"));
        verticalLayout_3 = new QVBoxLayout(tab_LogOut);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lstLogout = new QListWidget(tab_LogOut);
        lstLogout->setObjectName(QStringLiteral("lstLogout"));
        sizePolicy.setHeightForWidth(lstLogout->sizePolicy().hasHeightForWidth());
        lstLogout->setSizePolicy(sizePolicy);
        lstLogout->setContextMenuPolicy(Qt::ActionsContextMenu);
#ifndef QT_NO_ACCESSIBILITY
        lstLogout->setAccessibleName(QStringLiteral(""));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        lstLogout->setAccessibleDescription(QStringLiteral(""));
#endif // QT_NO_ACCESSIBILITY
        lstLogout->setFrameShape(QFrame::NoFrame);
        lstLogout->setSelectionMode(QAbstractItemView::MultiSelection);
        lstLogout->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_3->addWidget(lstLogout);

        tabWidget->addTab(tab_LogOut, QString());
        tab_Operate = new XConfig();
        tab_Operate->setObjectName(QStringLiteral("tab_Operate"));
        gridLayout_9 = new QGridLayout(tab_Operate);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        groupBox_9 = new QGroupBox(tab_Operate);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        gridLayout_11 = new QGridLayout(groupBox_9);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        doubleSpinBox_target_position_y = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_target_position_y->setObjectName(QStringLiteral("doubleSpinBox_target_position_y"));
        doubleSpinBox_target_position_y->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox_target_position_y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_target_position_y->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        doubleSpinBox_target_position_y->setFont(font);
        doubleSpinBox_target_position_y->setFrame(false);
        doubleSpinBox_target_position_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_target_position_y->setReadOnly(true);
        doubleSpinBox_target_position_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_target_position_y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_target_position_y->setPrefix(QStringLiteral(""));
        doubleSpinBox_target_position_y->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_target_position_y->setMinimum(-1e+11);
        doubleSpinBox_target_position_y->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_target_position_y, 2, 1, 1, 1);

        doubleSpinBox_Mileage_x = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_Mileage_x->setObjectName(QStringLiteral("doubleSpinBox_Mileage_x"));
        doubleSpinBox_Mileage_x->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_Mileage_x->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Mileage_x->setSizePolicy(sizePolicy1);
        doubleSpinBox_Mileage_x->setFont(font);
        doubleSpinBox_Mileage_x->setFrame(false);
        doubleSpinBox_Mileage_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_Mileage_x->setReadOnly(true);
        doubleSpinBox_Mileage_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_Mileage_x->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_Mileage_x->setPrefix(QStringLiteral(""));
        doubleSpinBox_Mileage_x->setSuffix(QStringLiteral(" m"));
        doubleSpinBox_Mileage_x->setDecimals(3);
        doubleSpinBox_Mileage_x->setMinimum(-1e+11);
        doubleSpinBox_Mileage_x->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_Mileage_x, 5, 1, 1, 1);

        label_17 = new QLabel(groupBox_9);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setEnabled(false);

        gridLayout_11->addWidget(label_17, 5, 0, 1, 1);

        label_13 = new QLabel(groupBox_9);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setEnabled(false);

        gridLayout_11->addWidget(label_13, 1, 0, 1, 1);

        label_12 = new QLabel(groupBox_9);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setEnabled(false);

        gridLayout_11->addWidget(label_12, 0, 0, 1, 1);

        doubleSpinBox_target_position_x = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_target_position_x->setObjectName(QStringLiteral("doubleSpinBox_target_position_x"));
        doubleSpinBox_target_position_x->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_target_position_x->sizePolicy().hasHeightForWidth());
        doubleSpinBox_target_position_x->setSizePolicy(sizePolicy1);
        doubleSpinBox_target_position_x->setFont(font);
        doubleSpinBox_target_position_x->setFrame(false);
        doubleSpinBox_target_position_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_target_position_x->setReadOnly(true);
        doubleSpinBox_target_position_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_target_position_x->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_target_position_x->setPrefix(QStringLiteral(""));
        doubleSpinBox_target_position_x->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_target_position_x->setMinimum(-1e+11);
        doubleSpinBox_target_position_x->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_target_position_x, 1, 1, 1, 1);

        doubleSpinBox_actual_position_y = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_actual_position_y->setObjectName(QStringLiteral("doubleSpinBox_actual_position_y"));
        doubleSpinBox_actual_position_y->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_actual_position_y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_actual_position_y->setSizePolicy(sizePolicy1);
        doubleSpinBox_actual_position_y->setFont(font);
        doubleSpinBox_actual_position_y->setFrame(false);
        doubleSpinBox_actual_position_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_actual_position_y->setReadOnly(true);
        doubleSpinBox_actual_position_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_actual_position_y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_actual_position_y->setPrefix(QStringLiteral(""));
        doubleSpinBox_actual_position_y->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_actual_position_y->setMinimum(-1e+11);
        doubleSpinBox_actual_position_y->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_actual_position_y, 4, 1, 1, 1);

        label_16 = new QLabel(groupBox_9);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setEnabled(false);

        gridLayout_11->addWidget(label_16, 4, 0, 1, 1);

        label_18 = new QLabel(groupBox_9);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setEnabled(false);

        gridLayout_11->addWidget(label_18, 6, 0, 1, 1);

        doubleSpinBox_Mileage_y = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_Mileage_y->setObjectName(QStringLiteral("doubleSpinBox_Mileage_y"));
        doubleSpinBox_Mileage_y->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_Mileage_y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Mileage_y->setSizePolicy(sizePolicy1);
        doubleSpinBox_Mileage_y->setFont(font);
        doubleSpinBox_Mileage_y->setFrame(false);
        doubleSpinBox_Mileage_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_Mileage_y->setReadOnly(true);
        doubleSpinBox_Mileage_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_Mileage_y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_Mileage_y->setPrefix(QStringLiteral(""));
        doubleSpinBox_Mileage_y->setSuffix(QStringLiteral(" m"));
        doubleSpinBox_Mileage_y->setDecimals(3);
        doubleSpinBox_Mileage_y->setMinimum(-1e+11);
        doubleSpinBox_Mileage_y->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_Mileage_y, 6, 1, 1, 1);

        label_15 = new QLabel(groupBox_9);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setEnabled(false);

        gridLayout_11->addWidget(label_15, 3, 0, 1, 1);

        label_14 = new QLabel(groupBox_9);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setEnabled(false);

        gridLayout_11->addWidget(label_14, 2, 0, 1, 1);

        doubleSpinBox_actual_position_x = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_actual_position_x->setObjectName(QStringLiteral("doubleSpinBox_actual_position_x"));
        doubleSpinBox_actual_position_x->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_actual_position_x->sizePolicy().hasHeightForWidth());
        doubleSpinBox_actual_position_x->setSizePolicy(sizePolicy1);
        doubleSpinBox_actual_position_x->setFont(font);
        doubleSpinBox_actual_position_x->setFrame(false);
        doubleSpinBox_actual_position_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_actual_position_x->setReadOnly(true);
        doubleSpinBox_actual_position_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_actual_position_x->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_actual_position_x->setPrefix(QStringLiteral(""));
        doubleSpinBox_actual_position_x->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_actual_position_x->setMinimum(-1e+11);
        doubleSpinBox_actual_position_x->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_actual_position_x, 3, 1, 1, 1);

        doubleSpinBox_RecordNumber = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_RecordNumber->setObjectName(QStringLiteral("doubleSpinBox_RecordNumber"));
        doubleSpinBox_RecordNumber->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_RecordNumber->sizePolicy().hasHeightForWidth());
        doubleSpinBox_RecordNumber->setSizePolicy(sizePolicy1);
        doubleSpinBox_RecordNumber->setFont(font);
        doubleSpinBox_RecordNumber->setFrame(false);
        doubleSpinBox_RecordNumber->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_RecordNumber->setReadOnly(true);
        doubleSpinBox_RecordNumber->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_RecordNumber->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_RecordNumber->setPrefix(QStringLiteral(""));
        doubleSpinBox_RecordNumber->setSuffix(QStringLiteral(""));
        doubleSpinBox_RecordNumber->setDecimals(0);
        doubleSpinBox_RecordNumber->setMinimum(-1e+11);
        doubleSpinBox_RecordNumber->setMaximum(1e+11);

        gridLayout_11->addWidget(doubleSpinBox_RecordNumber, 0, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_11->addItem(verticalSpacer_7, 7, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_9, 0, 1, 1, 1);

        groupBox_10 = new QGroupBox(tab_Operate);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        gridLayout_12 = new QGridLayout(groupBox_10);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        radES = new QRadioButton(groupBox_10);
        radES->setObjectName(QStringLiteral("radES"));
        radES->setEnabled(false);
        sizePolicy1.setHeightForWidth(radES->sizePolicy().hasHeightForWidth());
        radES->setSizePolicy(sizePolicy1);
        radES->setAutoExclusive(false);

        gridLayout_12->addWidget(radES, 1, 0, 1, 1);

        radHome = new QRadioButton(groupBox_10);
        radHome->setObjectName(QStringLiteral("radHome"));
        radHome->setEnabled(false);
        sizePolicy1.setHeightForWidth(radHome->sizePolicy().hasHeightForWidth());
        radHome->setSizePolicy(sizePolicy1);
        radHome->setAutoExclusive(false);

        gridLayout_12->addWidget(radHome, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_10, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer, 0, 3, 1, 1);

        tabWidget->addTab(tab_Operate, QString());
        tab_DigitalIO = new XConfig();
        tab_DigitalIO->setObjectName(QStringLiteral("tab_DigitalIO"));
        horizontalLayout = new QHBoxLayout(tab_DigitalIO);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(tab_DigitalIO);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_11 = new QRadioButton(groupBox);
        radioButton_11->setObjectName(QStringLiteral("radioButton_11"));
        sizePolicy1.setHeightForWidth(radioButton_11->sizePolicy().hasHeightForWidth());
        radioButton_11->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(radioButton_11, 2, 1, 1, 1);

        radioButton_12 = new QRadioButton(groupBox);
        radioButton_12->setObjectName(QStringLiteral("radioButton_12"));
        sizePolicy1.setHeightForWidth(radioButton_12->sizePolicy().hasHeightForWidth());
        radioButton_12->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(radioButton_12, 3, 1, 1, 1);

        radioButton_10 = new QRadioButton(groupBox);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
        sizePolicy1.setHeightForWidth(radioButton_10->sizePolicy().hasHeightForWidth());
        radioButton_10->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(radioButton_10, 0, 1, 1, 1);

        radioButton_8 = new QRadioButton(groupBox);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        sizePolicy1.setHeightForWidth(radioButton_8->sizePolicy().hasHeightForWidth());
        radioButton_8->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(radioButton_8, 5, 0, 1, 1);

        radioButton_9 = new QRadioButton(groupBox);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));
        sizePolicy1.setHeightForWidth(radioButton_9->sizePolicy().hasHeightForWidth());
        radioButton_9->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(radioButton_9, 6, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        label_recordNumber = new QLabel(groupBox);
        label_recordNumber->setObjectName(QStringLiteral("label_recordNumber"));
        label_recordNumber->setFont(font);
        label_recordNumber->setText(QStringLiteral("0"));

        gridLayout->addWidget(label_recordNumber, 7, 1, 1, 1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        sizePolicy1.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy1);
        radioButton_2->setAutoExclusive(false);

        gridLayout->addWidget(radioButton_2, 2, 0, 1, 1);

        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        sizePolicy1.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy1);
        radioButton->setAutoExclusive(false);

        gridLayout->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        sizePolicy1.setHeightForWidth(radioButton_4->sizePolicy().hasHeightForWidth());
        radioButton_4->setSizePolicy(sizePolicy1);
        radioButton_4->setAutoExclusive(false);

        gridLayout->addWidget(radioButton_4, 4, 0, 1, 1);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        sizePolicy1.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy1);
        radioButton_3->setAutoExclusive(false);

        gridLayout->addWidget(radioButton_3, 3, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 8, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_DigitalIO);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButton_moiton_complete = new QRadioButton(groupBox_2);
        radioButton_moiton_complete->setObjectName(QStringLiteral("radioButton_moiton_complete"));
        sizePolicy1.setHeightForWidth(radioButton_moiton_complete->sizePolicy().hasHeightForWidth());
        radioButton_moiton_complete->setSizePolicy(sizePolicy1);
        radioButton_moiton_complete->setAutoExclusive(false);

        gridLayout_2->addWidget(radioButton_moiton_complete, 3, 0, 1, 1);

        radioButton_load_voltage = new QRadioButton(groupBox_2);
        radioButton_load_voltage->setObjectName(QStringLiteral("radioButton_load_voltage"));
        sizePolicy1.setHeightForWidth(radioButton_load_voltage->sizePolicy().hasHeightForWidth());
        radioButton_load_voltage->setSizePolicy(sizePolicy1);
        radioButton_load_voltage->setAutoExclusive(false);

        gridLayout_2->addWidget(radioButton_load_voltage, 4, 0, 1, 1);

        radioButton_acknowledge_start = new QRadioButton(groupBox_2);
        radioButton_acknowledge_start->setObjectName(QStringLiteral("radioButton_acknowledge_start"));
        sizePolicy1.setHeightForWidth(radioButton_acknowledge_start->sizePolicy().hasHeightForWidth());
        radioButton_acknowledge_start->setSizePolicy(sizePolicy1);
        radioButton_acknowledge_start->setAutoExclusive(false);

        gridLayout_2->addWidget(radioButton_acknowledge_start, 2, 0, 1, 1);

        radioButton_fault = new QRadioButton(groupBox_2);
        radioButton_fault->setObjectName(QStringLiteral("radioButton_fault"));
        sizePolicy1.setHeightForWidth(radioButton_fault->sizePolicy().hasHeightForWidth());
        radioButton_fault->setSizePolicy(sizePolicy1);
        radioButton_fault->setAutoExclusive(false);

        gridLayout_2->addWidget(radioButton_fault, 1, 0, 1, 1);

        radioButton_ready = new QRadioButton(groupBox_2);
        radioButton_ready->setObjectName(QStringLiteral("radioButton_ready"));
        sizePolicy1.setHeightForWidth(radioButton_ready->sizePolicy().hasHeightForWidth());
        radioButton_ready->setSizePolicy(sizePolicy1);
        radioButton_ready->setAutoExclusive(false);

        gridLayout_2->addWidget(radioButton_ready, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 5, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        tabWidget->addTab(tab_DigitalIO, QString());
        tab_Homing = new XConfig();
        tab_Homing->setObjectName(QStringLiteral("tab_Homing"));
        gridLayout_13 = new QGridLayout(tab_Homing);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        groupBox_11 = new QGroupBox(tab_Homing);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        gridLayout_14 = new QGridLayout(groupBox_11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        radioButton_homing_valid = new QRadioButton(groupBox_11);
        radioButton_homing_valid->setObjectName(QStringLiteral("radioButton_homing_valid"));
        radioButton_homing_valid->setEnabled(false);
        sizePolicy1.setHeightForWidth(radioButton_homing_valid->sizePolicy().hasHeightForWidth());
        radioButton_homing_valid->setSizePolicy(sizePolicy1);
        radioButton_homing_valid->setLayoutDirection(Qt::RightToLeft);
        radioButton_homing_valid->setAutoExclusive(false);

        gridLayout_14->addWidget(radioButton_homing_valid, 2, 0, 1, 2);

        label_19 = new QLabel(groupBox_11);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setEnabled(false);
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(label_19, 0, 0, 1, 1);

        doubleSpinBox_homing_actual_pos_x = new QDoubleSpinBox(groupBox_11);
        doubleSpinBox_homing_actual_pos_x->setObjectName(QStringLiteral("doubleSpinBox_homing_actual_pos_x"));
        doubleSpinBox_homing_actual_pos_x->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_homing_actual_pos_x->sizePolicy().hasHeightForWidth());
        doubleSpinBox_homing_actual_pos_x->setSizePolicy(sizePolicy1);
        doubleSpinBox_homing_actual_pos_x->setFont(font);
        doubleSpinBox_homing_actual_pos_x->setFrame(false);
        doubleSpinBox_homing_actual_pos_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_homing_actual_pos_x->setReadOnly(true);
        doubleSpinBox_homing_actual_pos_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_homing_actual_pos_x->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_homing_actual_pos_x->setPrefix(QStringLiteral(""));
        doubleSpinBox_homing_actual_pos_x->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_homing_actual_pos_x->setMinimum(-10000);
        doubleSpinBox_homing_actual_pos_x->setMaximum(10000);

        gridLayout_14->addWidget(doubleSpinBox_homing_actual_pos_x, 3, 1, 1, 2);

        label_20 = new QLabel(groupBox_11);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setEnabled(false);
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(label_20, 1, 0, 1, 1);

        doubleSpinBox_homing_actual_pos_y = new QDoubleSpinBox(groupBox_11);
        doubleSpinBox_homing_actual_pos_y->setObjectName(QStringLiteral("doubleSpinBox_homing_actual_pos_y"));
        doubleSpinBox_homing_actual_pos_y->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_homing_actual_pos_y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_homing_actual_pos_y->setSizePolicy(sizePolicy1);
        doubleSpinBox_homing_actual_pos_y->setFont(font);
        doubleSpinBox_homing_actual_pos_y->setFrame(false);
        doubleSpinBox_homing_actual_pos_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_homing_actual_pos_y->setReadOnly(true);
        doubleSpinBox_homing_actual_pos_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_homing_actual_pos_y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_homing_actual_pos_y->setPrefix(QStringLiteral(""));
        doubleSpinBox_homing_actual_pos_y->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_homing_actual_pos_y->setMinimum(-10000);
        doubleSpinBox_homing_actual_pos_y->setMaximum(10000);

        gridLayout_14->addWidget(doubleSpinBox_homing_actual_pos_y, 4, 1, 1, 2);

        label_22 = new QLabel(groupBox_11);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setEnabled(false);

        gridLayout_14->addWidget(label_22, 4, 0, 1, 1);

        pushButton_starting_home = new QPushButton(groupBox_11);
        pushButton_starting_home->setObjectName(QStringLiteral("pushButton_starting_home"));
        sizePolicy1.setHeightForWidth(pushButton_starting_home->sizePolicy().hasHeightForWidth());
        pushButton_starting_home->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/icon/address.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_starting_home->setIcon(icon);

        gridLayout_14->addWidget(pushButton_starting_home, 5, 0, 1, 3);

        label_21 = new QLabel(groupBox_11);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setEnabled(false);

        gridLayout_14->addWidget(label_21, 3, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_14->addItem(verticalSpacer_5, 7, 0, 1, 1);

        label_homing_direction = new QLabel(groupBox_11);
        label_homing_direction->setObjectName(QStringLiteral("label_homing_direction"));
        label_homing_direction->setEnabled(false);

        gridLayout_14->addWidget(label_homing_direction, 1, 1, 1, 2);

        label_homing_target = new QLabel(groupBox_11);
        label_homing_target->setObjectName(QStringLiteral("label_homing_target"));
        label_homing_target->setEnabled(false);

        gridLayout_14->addWidget(label_homing_target, 0, 1, 1, 2);

        pushButton_go_prjZero = new QPushButton(groupBox_11);
        pushButton_go_prjZero->setObjectName(QStringLiteral("pushButton_go_prjZero"));

        gridLayout_14->addWidget(pushButton_go_prjZero, 6, 0, 1, 3);


        gridLayout_13->addWidget(groupBox_11, 0, 0, 1, 1);

        tabWidget->addTab(tab_Homing, QString());
        tab_Manual = new XConfig();
        tab_Manual->setObjectName(QStringLiteral("tab_Manual"));
        gridLayout_7 = new QGridLayout(tab_Manual);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(tab_Manual);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(9, -1, 9, 9);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_7, 2, 4, 1, 2);

        toolButton_singlestep_x_inc = new QToolButton(groupBox_3);
        toolButton_singlestep_x_inc->setObjectName(QStringLiteral("toolButton_singlestep_x_inc"));
        sizePolicy.setHeightForWidth(toolButton_singlestep_x_inc->sizePolicy().hasHeightForWidth());
        toolButton_singlestep_x_inc->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/image/icon/arrow-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_singlestep_x_inc->setIcon(icon1);
        toolButton_singlestep_x_inc->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_singlestep_x_inc, 3, 2, 1, 1);

        toolButton_singlestep_y_dec = new QToolButton(groupBox_3);
        toolButton_singlestep_y_dec->setObjectName(QStringLiteral("toolButton_singlestep_y_dec"));
        sizePolicy.setHeightForWidth(toolButton_singlestep_y_dec->sizePolicy().hasHeightForWidth());
        toolButton_singlestep_y_dec->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/image/icon/arrow-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_singlestep_y_dec->setIcon(icon2);
        toolButton_singlestep_y_dec->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_singlestep_y_dec, 3, 4, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_5, 4, 0, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);

        toolButton_singlestep_x_dec = new QToolButton(groupBox_3);
        toolButton_singlestep_x_dec->setObjectName(QStringLiteral("toolButton_singlestep_x_dec"));
        sizePolicy.setHeightForWidth(toolButton_singlestep_x_dec->sizePolicy().hasHeightForWidth());
        toolButton_singlestep_x_dec->setSizePolicy(sizePolicy);
        toolButton_singlestep_x_dec->setLayoutDirection(Qt::LeftToRight);
        toolButton_singlestep_x_dec->setIcon(icon2);
        toolButton_singlestep_x_dec->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_singlestep_x_dec, 3, 1, 1, 1);

        toolButton_jogmode_y_dec = new QToolButton(groupBox_3);
        toolButton_jogmode_y_dec->setObjectName(QStringLiteral("toolButton_jogmode_y_dec"));
        sizePolicy.setHeightForWidth(toolButton_jogmode_y_dec->sizePolicy().hasHeightForWidth());
        toolButton_jogmode_y_dec->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/image/icon/arrow-left-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_jogmode_y_dec->setIcon(icon3);
        toolButton_jogmode_y_dec->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_jogmode_y_dec, 4, 4, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_8, 5, 0, 1, 1);

        toolButton_jogmode_x_dec = new QToolButton(groupBox_3);
        toolButton_jogmode_x_dec->setObjectName(QStringLiteral("toolButton_jogmode_x_dec"));
        sizePolicy.setHeightForWidth(toolButton_jogmode_x_dec->sizePolicy().hasHeightForWidth());
        toolButton_jogmode_x_dec->setSizePolicy(sizePolicy);
        toolButton_jogmode_x_dec->setIcon(icon3);
        toolButton_jogmode_x_dec->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_jogmode_x_dec, 4, 1, 1, 1);

        toolButton_singlestep_y_inc = new QToolButton(groupBox_3);
        toolButton_singlestep_y_inc->setObjectName(QStringLiteral("toolButton_singlestep_y_inc"));
        sizePolicy.setHeightForWidth(toolButton_singlestep_y_inc->sizePolicy().hasHeightForWidth());
        toolButton_singlestep_y_inc->setSizePolicy(sizePolicy);
        toolButton_singlestep_y_inc->setIcon(icon1);
        toolButton_singlestep_y_inc->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_singlestep_y_inc, 3, 5, 1, 1);

        toolButton_jogmode_x_inc = new QToolButton(groupBox_3);
        toolButton_jogmode_x_inc->setObjectName(QStringLiteral("toolButton_jogmode_x_inc"));
        sizePolicy.setHeightForWidth(toolButton_jogmode_x_inc->sizePolicy().hasHeightForWidth());
        toolButton_jogmode_x_inc->setSizePolicy(sizePolicy);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/image/icon/arrow-right-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_jogmode_x_inc->setIcon(icon4);
        toolButton_jogmode_x_inc->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_jogmode_x_inc, 4, 2, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(60, 20));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        doubleSpinBox_Velocity = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_Velocity->setObjectName(QStringLiteral("doubleSpinBox_Velocity"));
        sizePolicy.setHeightForWidth(doubleSpinBox_Velocity->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Velocity->setSizePolicy(sizePolicy);
        doubleSpinBox_Velocity->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_Velocity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_Velocity->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_Velocity->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_Velocity->setPrefix(QStringLiteral(""));
        doubleSpinBox_Velocity->setSuffix(QStringLiteral(" mm/s"));
        doubleSpinBox_Velocity->setMinimum(0.01);
        doubleSpinBox_Velocity->setMaximum(10000);
        doubleSpinBox_Velocity->setValue(50);

        gridLayout_3->addWidget(doubleSpinBox_Velocity, 1, 1, 1, 3);

        doubleSpinBox_Increament = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_Increament->setObjectName(QStringLiteral("doubleSpinBox_Increament"));
        sizePolicy.setHeightForWidth(doubleSpinBox_Increament->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Increament->setSizePolicy(sizePolicy);
        doubleSpinBox_Increament->setCursor(QCursor(Qt::IBeamCursor));
        doubleSpinBox_Increament->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_Increament->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_Increament->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_Increament->setPrefix(QStringLiteral(""));
        doubleSpinBox_Increament->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_Increament->setDecimals(2);
        doubleSpinBox_Increament->setMinimum(0.01);
        doubleSpinBox_Increament->setMaximum(10000);
        doubleSpinBox_Increament->setValue(100);

        gridLayout_3->addWidget(doubleSpinBox_Increament, 0, 1, 1, 3);

        toolButton_jogmode_y_inc = new QToolButton(groupBox_3);
        toolButton_jogmode_y_inc->setObjectName(QStringLiteral("toolButton_jogmode_y_inc"));
        sizePolicy.setHeightForWidth(toolButton_jogmode_y_inc->sizePolicy().hasHeightForWidth());
        toolButton_jogmode_y_inc->setSizePolicy(sizePolicy);
        toolButton_jogmode_y_inc->setIcon(icon4);
        toolButton_jogmode_y_inc->setIconSize(QSize(40, 16));

        gridLayout_3->addWidget(toolButton_jogmode_y_inc, 4, 5, 1, 1);

        pushButton_stop = new QPushButton(groupBox_3);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/image/icon/246.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_stop->setIcon(icon5);
        pushButton_stop->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButton_stop, 3, 3, 2, 1);

        pushButton_apply = new QPushButton(groupBox_3);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        sizePolicy1.setHeightForWidth(pushButton_apply->sizePolicy().hasHeightForWidth());
        pushButton_apply->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(pushButton_apply, 6, 2, 1, 3);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_6, 2, 1, 1, 2);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 20));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        doubleSpinBox_currentPos_y = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_currentPos_y->setObjectName(QStringLiteral("doubleSpinBox_currentPos_y"));
        doubleSpinBox_currentPos_y->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_currentPos_y->sizePolicy().hasHeightForWidth());
        doubleSpinBox_currentPos_y->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        doubleSpinBox_currentPos_y->setFont(font1);
        doubleSpinBox_currentPos_y->setFrame(false);
        doubleSpinBox_currentPos_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_currentPos_y->setReadOnly(true);
        doubleSpinBox_currentPos_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_currentPos_y->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_currentPos_y->setPrefix(QStringLiteral(""));
        doubleSpinBox_currentPos_y->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_currentPos_y->setMinimum(-10000);
        doubleSpinBox_currentPos_y->setMaximum(10000);

        gridLayout_3->addWidget(doubleSpinBox_currentPos_y, 5, 4, 1, 2);

        doubleSpinBox_currentPos_x = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_currentPos_x->setObjectName(QStringLiteral("doubleSpinBox_currentPos_x"));
        doubleSpinBox_currentPos_x->setEnabled(false);
        sizePolicy1.setHeightForWidth(doubleSpinBox_currentPos_x->sizePolicy().hasHeightForWidth());
        doubleSpinBox_currentPos_x->setSizePolicy(sizePolicy1);
        doubleSpinBox_currentPos_x->setFont(font1);
        doubleSpinBox_currentPos_x->setFrame(false);
        doubleSpinBox_currentPos_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_currentPos_x->setReadOnly(true);
        doubleSpinBox_currentPos_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_currentPos_x->setSpecialValueText(QStringLiteral(""));
        doubleSpinBox_currentPos_x->setPrefix(QStringLiteral(""));
        doubleSpinBox_currentPos_x->setSuffix(QStringLiteral(" mm"));
        doubleSpinBox_currentPos_x->setMinimum(-10000);
        doubleSpinBox_currentPos_x->setMaximum(10000);

        gridLayout_3->addWidget(doubleSpinBox_currentPos_x, 5, 1, 1, 2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 7, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        tabWidget->addTab(tab_Manual, QString());
        tab_Monitor = new XConfig();
        tab_Monitor->setObjectName(QStringLiteral("tab_Monitor"));
        horizontalLayout_3 = new QHBoxLayout(tab_Monitor);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tab_Monitor, QString());
        tab_Debug = new XConfig();
        tab_Debug->setObjectName(QStringLiteral("tab_Debug"));
        gridLayout_8 = new QGridLayout(tab_Debug);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_9 = new QLabel(tab_Debug);
        label_9->setObjectName(QStringLiteral("label_9"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_9, 0, 3, 1, 1);

        tvDebug = new QTableView(tab_Debug);
        tvDebug->setObjectName(QStringLiteral("tvDebug"));
        tvDebug->setSelectionMode(QAbstractItemView::SingleSelection);
        tvDebug->setSelectionBehavior(QAbstractItemView::SelectRows);
        tvDebug->horizontalHeader()->setStretchLastSection(true);
        tvDebug->verticalHeader()->setVisible(false);

        gridLayout_5->addWidget(tvDebug, 2, 0, 10, 17);

        toolButton_debugRun = new QToolButton(tab_Debug);
        toolButton_debugRun->setObjectName(QStringLiteral("toolButton_debugRun"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(3);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(toolButton_debugRun->sizePolicy().hasHeightForWidth());
        toolButton_debugRun->setSizePolicy(sizePolicy4);
        toolButton_debugRun->setMinimumSize(QSize(120, 20));
        toolButton_debugRun->setMaximumSize(QSize(16777215, 16777215));
        toolButton_debugRun->setIconSize(QSize(16, 16));

        gridLayout_5->addWidget(toolButton_debugRun, 0, 14, 1, 2);

        btnImport = new QToolButton(tab_Debug);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(1);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btnImport->sizePolicy().hasHeightForWidth());
        btnImport->setSizePolicy(sizePolicy5);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/image/icon/218.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnImport->setIcon(icon6);

        gridLayout_5->addWidget(btnImport, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_6, 0, 8, 1, 2);

        btnDown = new QToolButton(tab_Debug);
        btnDown->setObjectName(QStringLiteral("btnDown"));
        sizePolicy5.setHeightForWidth(btnDown->sizePolicy().hasHeightForWidth());
        btnDown->setSizePolicy(sizePolicy5);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/res/image/icon/arrow-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDown->setIcon(icon7);

        gridLayout_5->addWidget(btnDown, 0, 11, 1, 1);

        btnUp = new QToolButton(tab_Debug);
        btnUp->setObjectName(QStringLiteral("btnUp"));
        sizePolicy5.setHeightForWidth(btnUp->sizePolicy().hasHeightForWidth());
        btnUp->setSizePolicy(sizePolicy5);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/res/image/icon/arrow-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUp->setIcon(icon8);

        gridLayout_5->addWidget(btnUp, 0, 10, 1, 1);

        btnExport = new QToolButton(tab_Debug);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        sizePolicy5.setHeightForWidth(btnExport->sizePolicy().hasHeightForWidth());
        btnExport->setSizePolicy(sizePolicy5);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/res/image/icon/219.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExport->setIcon(icon9);

        gridLayout_5->addWidget(btnExport, 0, 1, 1, 1);

        chkCyclic = new QCheckBox(tab_Debug);
        chkCyclic->setObjectName(QStringLiteral("chkCyclic"));
        sizePolicy3.setHeightForWidth(chkCyclic->sizePolicy().hasHeightForWidth());
        chkCyclic->setSizePolicy(sizePolicy3);
        chkCyclic->setLayoutDirection(Qt::LeftToRight);

        gridLayout_5->addWidget(chkCyclic, 0, 13, 1, 1);

        spinDly = new QDoubleSpinBox(tab_Debug);
        spinDly->setObjectName(QStringLiteral("spinDly"));
        sizePolicy3.setHeightForWidth(spinDly->sizePolicy().hasHeightForWidth());
        spinDly->setSizePolicy(sizePolicy3);
        spinDly->setMinimumSize(QSize(80, 0));
        spinDly->setMaximumSize(QSize(80, 16777215));
        spinDly->setCursor(QCursor(Qt::ArrowCursor));
        spinDly->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinDly->setSpecialValueText(QStringLiteral(""));
        spinDly->setPrefix(QStringLiteral(""));
        spinDly->setSuffix(QStringLiteral("s"));
        spinDly->setMinimum(0);
        spinDly->setMaximum(1e+6);
        spinDly->setValue(1);

        gridLayout_5->addWidget(spinDly, 0, 4, 1, 1);

        btnClr = new QToolButton(tab_Debug);
        btnClr->setObjectName(QStringLiteral("btnClr"));
        sizePolicy5.setHeightForWidth(btnClr->sizePolicy().hasHeightForWidth());
        btnClr->setSizePolicy(sizePolicy5);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/res/image/icon/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClr->setIcon(icon10);

        gridLayout_5->addWidget(btnClr, 0, 7, 1, 1);

        btnDel = new QToolButton(tab_Debug);
        btnDel->setObjectName(QStringLiteral("btnDel"));
        sizePolicy5.setHeightForWidth(btnDel->sizePolicy().hasHeightForWidth());
        btnDel->setSizePolicy(sizePolicy5);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/res/image/icon/subtract.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDel->setIcon(icon11);

        gridLayout_5->addWidget(btnDel, 0, 6, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_7, 0, 2, 1, 1);

        btnAdd = new QToolButton(tab_Debug);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        sizePolicy5.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy5);
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/res/image/icon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd->setIcon(icon12);

        gridLayout_5->addWidget(btnAdd, 0, 5, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_9, 0, 12, 1, 1);


        gridLayout_8->addLayout(gridLayout_5, 0, 7, 2, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_8, 0, 9, 2, 1);

        groupBox_4 = new QGroupBox(tab_Debug);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setVerticalSpacing(12);
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);
        label_10->setMinimumSize(QSize(80, 20));

        gridLayout_6->addWidget(label_10, 0, 0, 1, 1);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy2.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy2);
        label_11->setMinimumSize(QSize(80, 20));

        gridLayout_6->addWidget(label_11, 1, 0, 1, 1);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));
        sizePolicy2.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy2);
        label_23->setMinimumSize(QSize(80, 20));

        gridLayout_6->addWidget(label_23, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 3, 0, 1, 1);

        doubleSpinBox_debugRecord = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_debugRecord->setObjectName(QStringLiteral("doubleSpinBox_debugRecord"));
        doubleSpinBox_debugRecord->setEnabled(false);
        sizePolicy2.setHeightForWidth(doubleSpinBox_debugRecord->sizePolicy().hasHeightForWidth());
        doubleSpinBox_debugRecord->setSizePolicy(sizePolicy2);
        doubleSpinBox_debugRecord->setMinimumSize(QSize(80, 20));
        doubleSpinBox_debugRecord->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_debugRecord->setReadOnly(true);
        doubleSpinBox_debugRecord->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_debugRecord->setDecimals(0);
        doubleSpinBox_debugRecord->setMinimum(-10000);
        doubleSpinBox_debugRecord->setMaximum(10000);

        gridLayout_6->addWidget(doubleSpinBox_debugRecord, 0, 1, 1, 1);

        doubleSpinBox_debug_posX = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_debug_posX->setObjectName(QStringLiteral("doubleSpinBox_debug_posX"));
        doubleSpinBox_debug_posX->setEnabled(false);
        sizePolicy2.setHeightForWidth(doubleSpinBox_debug_posX->sizePolicy().hasHeightForWidth());
        doubleSpinBox_debug_posX->setSizePolicy(sizePolicy2);
        doubleSpinBox_debug_posX->setMinimumSize(QSize(80, 20));
        doubleSpinBox_debug_posX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_debug_posX->setReadOnly(true);
        doubleSpinBox_debug_posX->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_debug_posX->setMinimum(-10000);
        doubleSpinBox_debug_posX->setMaximum(10000);

        gridLayout_6->addWidget(doubleSpinBox_debug_posX, 1, 1, 1, 1);

        doubleSpinBox_debug_posY = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_debug_posY->setObjectName(QStringLiteral("doubleSpinBox_debug_posY"));
        doubleSpinBox_debug_posY->setEnabled(false);
        sizePolicy2.setHeightForWidth(doubleSpinBox_debug_posY->sizePolicy().hasHeightForWidth());
        doubleSpinBox_debug_posY->setSizePolicy(sizePolicy2);
        doubleSpinBox_debug_posY->setMinimumSize(QSize(80, 20));
        doubleSpinBox_debug_posY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_debug_posY->setReadOnly(true);
        doubleSpinBox_debug_posY->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_debug_posY->setMinimum(-10000);
        doubleSpinBox_debug_posY->setMaximum(10000);

        gridLayout_6->addWidget(doubleSpinBox_debug_posY, 2, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_4, 0, 8, 2, 1);

        tabWidget->addTab(tab_Debug, QString());
        tab_Diagnosis = new XConfig();
        tab_Diagnosis->setObjectName(QStringLiteral("tab_Diagnosis"));
        gridLayout_10 = new QGridLayout(tab_Diagnosis);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        btnRead = new QToolButton(tab_Diagnosis);
        btnRead->setObjectName(QStringLiteral("btnRead"));
        sizePolicy.setHeightForWidth(btnRead->sizePolicy().hasHeightForWidth());
        btnRead->setSizePolicy(sizePolicy);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/res/image/icon/skip.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRead->setIcon(icon13);

        gridLayout_10->addWidget(btnRead, 0, 0, 1, 1);

        btnDelete = new QToolButton(tab_Diagnosis);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        sizePolicy.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/res/image/icon/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete->setIcon(icon14);

        gridLayout_10->addWidget(btnDelete, 0, 1, 1, 1);

        tvDiagnosis = new QTableView(tab_Diagnosis);
        tvDiagnosis->setObjectName(QStringLiteral("tvDiagnosis"));
        tvDiagnosis->horizontalHeader()->setStretchLastSection(true);
        tvDiagnosis->verticalHeader()->setVisible(false);

        gridLayout_10->addWidget(tvDiagnosis, 1, 0, 1, 4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_3, 0, 3, 1, 1);

        btnExport_2 = new QToolButton(tab_Diagnosis);
        btnExport_2->setObjectName(QStringLiteral("btnExport_2"));
        sizePolicy.setHeightForWidth(btnExport_2->sizePolicy().hasHeightForWidth());
        btnExport_2->setSizePolicy(sizePolicy);
        btnExport_2->setIcon(icon9);

        gridLayout_10->addWidget(btnExport_2, 0, 2, 1, 1);

        tabWidget->addTab(tab_Diagnosis, QString());

        horizontalLayout_4->addWidget(tabWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);


        retranslateUi(H2Ops);

        tabWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(H2Ops);
    } // setupUi

    void retranslateUi(QWidget *H2Ops)
    {
        H2Ops->setWindowTitle(QApplication::translate("H2Ops", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab_LogOut), QApplication::translate("H2Ops", "Logout", nullptr));
        groupBox_9->setTitle(QApplication::translate("H2Ops", "Dynamic Data", nullptr));
        label_17->setText(QApplication::translate("H2Ops", "Mileage X-Axis:", nullptr));
        label_13->setText(QApplication::translate("H2Ops", "Target Position X:", nullptr));
        label_12->setText(QApplication::translate("H2Ops", "Record Number:", nullptr));
        label_16->setText(QApplication::translate("H2Ops", "Actual Position Y:", nullptr));
        label_18->setText(QApplication::translate("H2Ops", "Mileage Y-Axis:", nullptr));
        label_15->setText(QApplication::translate("H2Ops", "Actual Position X:", nullptr));
        label_14->setText(QApplication::translate("H2Ops", "Target Position Y:", nullptr));
        groupBox_10->setTitle(QApplication::translate("H2Ops", "Additional States", nullptr));
        radES->setText(QApplication::translate("H2Ops", "Extern Stop(ES)", nullptr));
        radHome->setText(QApplication::translate("H2Ops", "Home Valid", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Operate), QApplication::translate("H2Ops", "Operate", nullptr));
        groupBox->setTitle(QApplication::translate("H2Ops", "Digital Inputs", nullptr));
        radioButton_11->setText(QApplication::translate("H2Ops", "Enable Drive", nullptr));
        radioButton_12->setText(QApplication::translate("H2Ops", "Reset Fault", nullptr));
        radioButton_10->setText(QApplication::translate("H2Ops", "Start Record Execution", nullptr));
        radioButton_8->setText(QApplication::translate("H2Ops", "Record Bit5", nullptr));
        radioButton_9->setText(QApplication::translate("H2Ops", "Reserved", nullptr));
        label_4->setText(QApplication::translate("H2Ops", "Record Number:", nullptr));
        radioButton_2->setText(QApplication::translate("H2Ops", "Record Bit2", nullptr));
        radioButton->setText(QApplication::translate("H2Ops", "Record Bit1", nullptr));
        radioButton_4->setText(QApplication::translate("H2Ops", "Record Bit4", nullptr));
        radioButton_3->setText(QApplication::translate("H2Ops", "Record Bit3", nullptr));
        groupBox_2->setTitle(QApplication::translate("H2Ops", "Digital Outputs", nullptr));
        radioButton_moiton_complete->setText(QApplication::translate("H2Ops", "Moiton Complete(MC)", nullptr));
        radioButton_load_voltage->setText(QApplication::translate("H2Ops", "24V Load Voltage", nullptr));
        radioButton_acknowledge_start->setText(QApplication::translate("H2Ops", "Acknowledge Start", nullptr));
        radioButton_fault->setText(QApplication::translate("H2Ops", "Fault", nullptr));
        radioButton_ready->setText(QApplication::translate("H2Ops", "Ready", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_DigitalIO), QApplication::translate("H2Ops", "Digital IO", nullptr));
        groupBox_11->setTitle(QApplication::translate("H2Ops", "Homing", nullptr));
        radioButton_homing_valid->setText(QApplication::translate("H2Ops", "Homing Valid", nullptr));
        label_19->setText(QApplication::translate("H2Ops", "Target:", nullptr));
        label_20->setText(QApplication::translate("H2Ops", "Direction:", nullptr));
        label_22->setText(QApplication::translate("H2Ops", "Actual Position Y:", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButton_starting_home->setToolTip(QApplication::translate("H2Ops", "Move  to Zero Point Position", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton_starting_home->setText(QApplication::translate("H2Ops", "Starting Home", nullptr));
        label_21->setText(QApplication::translate("H2Ops", "Actual Position X:", nullptr));
        label_homing_direction->setText(QString());
        label_homing_target->setText(QString());
        pushButton_go_prjZero->setText(QApplication::translate("H2Ops", "Run to Project Zero Point", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Homing), QApplication::translate("H2Ops", "Homing", nullptr));
        groupBox_3->setTitle(QApplication::translate("H2Ops", "Manual Control", nullptr));
        label_7->setText(QApplication::translate("H2Ops", "Y-Axis", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton_singlestep_x_inc->setToolTip(QApplication::translate("H2Ops", "Clicked Move", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_singlestep_x_inc->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_singlestep_y_dec->setToolTip(QApplication::translate("H2Ops", "Clicked Move", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_singlestep_y_dec->setText(QString());
        label_5->setText(QApplication::translate("H2Ops", "Jog:", nullptr));
        label_3->setText(QApplication::translate("H2Ops", "Single Step:", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton_singlestep_x_dec->setToolTip(QApplication::translate("H2Ops", "Clicked Move", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_singlestep_x_dec->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_jogmode_y_dec->setToolTip(QApplication::translate("H2Ops", "Pressed Move Release Stop", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_jogmode_y_dec->setText(QString());
        label_8->setText(QApplication::translate("H2Ops", "Current Position", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton_jogmode_x_dec->setToolTip(QApplication::translate("H2Ops", "Pressed Move Release Stop", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_jogmode_x_dec->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_singlestep_y_inc->setToolTip(QApplication::translate("H2Ops", "Clicked Move", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_singlestep_y_inc->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_jogmode_x_inc->setToolTip(QApplication::translate("H2Ops", "Pressed Move Release Stop", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_jogmode_x_inc->setText(QString());
        label->setText(QApplication::translate("H2Ops", "Increament:", nullptr));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox_Increament->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        toolButton_jogmode_y_inc->setToolTip(QApplication::translate("H2Ops", "Pressed Move Release Stop", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_jogmode_y_inc->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_stop->setToolTip(QApplication::translate("H2Ops", "Stop Moving", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton_stop->setText(QString());
        pushButton_apply->setText(QApplication::translate("H2Ops", "Apply as point", nullptr));
        label_6->setText(QApplication::translate("H2Ops", "X-Axis", nullptr));
        label_2->setText(QApplication::translate("H2Ops", "Velocity:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Manual), QApplication::translate("H2Ops", "Manual", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Monitor), QApplication::translate("H2Ops", "Monitor", nullptr));
        label_9->setText(QApplication::translate("H2Ops", "Delay Time:", nullptr));
#ifndef QT_NO_TOOLTIP
        toolButton_debugRun->setToolTip(QApplication::translate("H2Ops", "Running", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton_debugRun->setText(QApplication::translate("H2Ops", "Run  Sequence", nullptr));
#ifndef QT_NO_TOOLTIP
        btnImport->setToolTip(QApplication::translate("H2Ops", "Import", nullptr));
#endif // QT_NO_TOOLTIP
        btnImport->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnDown->setToolTip(QApplication::translate("H2Ops", "Move Down", nullptr));
#endif // QT_NO_TOOLTIP
        btnDown->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnUp->setToolTip(QApplication::translate("H2Ops", "Move Up", nullptr));
#endif // QT_NO_TOOLTIP
        btnUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnExport->setToolTip(QApplication::translate("H2Ops", "Export", nullptr));
#endif // QT_NO_TOOLTIP
        btnExport->setText(QString());
        chkCyclic->setText(QApplication::translate("H2Ops", "Cyclic", nullptr));
#ifndef QT_NO_TOOLTIP
        btnClr->setToolTip(QApplication::translate("H2Ops", "Delete all record", nullptr));
#endif // QT_NO_TOOLTIP
        btnClr->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnDel->setToolTip(QApplication::translate("H2Ops", "Remove the current record", nullptr));
#endif // QT_NO_TOOLTIP
        btnDel->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnAdd->setToolTip(QApplication::translate("H2Ops", "add a new record", nullptr));
#endif // QT_NO_TOOLTIP
        btnAdd->setText(QString());
        groupBox_4->setTitle(QApplication::translate("H2Ops", "Status", nullptr));
        label_10->setText(QApplication::translate("H2Ops", "RecordNumber:", nullptr));
        label_11->setText(QApplication::translate("H2Ops", "Position X:", nullptr));
        label_23->setText(QApplication::translate("H2Ops", "Position Y:", nullptr));
        doubleSpinBox_debug_posX->setSuffix(QApplication::translate("H2Ops", " mm", nullptr));
        doubleSpinBox_debug_posY->setSuffix(QApplication::translate("H2Ops", " mm", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Debug), QApplication::translate("H2Ops", "Debug", nullptr));
#ifndef QT_NO_TOOLTIP
        btnRead->setToolTip(QApplication::translate("H2Ops", "Read from the controller", nullptr));
#endif // QT_NO_TOOLTIP
        btnRead->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnDelete->setToolTip(QApplication::translate("H2Ops", "Deleta all", nullptr));
#endif // QT_NO_TOOLTIP
        btnDelete->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnExport_2->setToolTip(QApplication::translate("H2Ops", "Export", nullptr));
#endif // QT_NO_TOOLTIP
        btnExport_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_Diagnosis), QApplication::translate("H2Ops", "Diagnosis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H2Ops: public Ui_H2Ops {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2OPS_H
