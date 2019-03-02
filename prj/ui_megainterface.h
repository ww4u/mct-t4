/********************************************************************************
** Form generated from reading UI file 'megainterface.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEGAINTERFACE_H
#define UI_MEGAINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MegaInterface
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_icon;
    QComboBox *comboBox_DevType;
    QPushButton *pushButton_Scan;
    QProgressBar *progressBar;
    QTableView *tableView;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MegaInterface)
    {
        if (MegaInterface->objectName().isEmpty())
            MegaInterface->setObjectName(QStringLiteral("MegaInterface"));
        MegaInterface->resize(667, 277);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MegaInterface->sizePolicy().hasHeightForWidth());
        MegaInterface->setSizePolicy(sizePolicy);
        MegaInterface->setMinimumSize(QSize(0, 0));
        MegaInterface->setFocusPolicy(Qt::TabFocus);
        verticalLayout_2 = new QVBoxLayout(MegaInterface);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        label_icon = new QLabel(MegaInterface);
        label_icon->setObjectName(QStringLiteral("label_icon"));
        label_icon->setPixmap(QPixmap(QString::fromUtf8(":/res/image/icon/network.ico")));

        horizontalLayout->addWidget(label_icon);

        comboBox_DevType = new QComboBox(MegaInterface);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/icon/network.ico"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_DevType->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/image/icon/usb.ico"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_DevType->addItem(icon1, QString());
        comboBox_DevType->setObjectName(QStringLiteral("comboBox_DevType"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_DevType->sizePolicy().hasHeightForWidth());
        comboBox_DevType->setSizePolicy(sizePolicy1);
        comboBox_DevType->setMinimumSize(QSize(80, 0));
        comboBox_DevType->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(comboBox_DevType);

        pushButton_Scan = new QPushButton(MegaInterface);
        pushButton_Scan->setObjectName(QStringLiteral("pushButton_Scan"));
        sizePolicy1.setHeightForWidth(pushButton_Scan->sizePolicy().hasHeightForWidth());
        pushButton_Scan->setSizePolicy(sizePolicy1);
        pushButton_Scan->setMinimumSize(QSize(120, 0));
        pushButton_Scan->setMaximumSize(QSize(120, 16777215));
        pushButton_Scan->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(13);
        pushButton_Scan->setFont(font);

        horizontalLayout->addWidget(pushButton_Scan);


        verticalLayout_2->addLayout(horizontalLayout);

        progressBar = new QProgressBar(MegaInterface);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(false);

        verticalLayout_2->addWidget(progressBar);

        tableView = new QTableView(MegaInterface);
        tableView->setObjectName(QStringLiteral("tableView"));
        QFont font1;
        font1.setPointSize(11);
        tableView->setFont(font1);
        tableView->setAutoFillBackground(false);
        tableView->setFrameShape(QFrame::Box);
        tableView->setFrameShadow(QFrame::Plain);
        tableView->setLineWidth(1);
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setProperty("showDropIndicator", QVariant(false));
        tableView->setDragDropOverwriteMode(false);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        tableView->setWordWrap(false);
        tableView->setCornerButtonEnabled(false);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setDefaultSectionSize(120);
        tableView->horizontalHeader()->setMinimumSectionSize(60);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setDefaultSectionSize(40);
        tableView->verticalHeader()->setMinimumSectionSize(30);

        verticalLayout_2->addWidget(tableView);

        line = new QFrame(MegaInterface);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(1);
        line->setFont(font2);
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(1);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line);

        buttonBox = new QDialogButtonBox(MegaInterface);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(MegaInterface);

        QMetaObject::connectSlotsByName(MegaInterface);
    } // setupUi

    void retranslateUi(QDialog *MegaInterface)
    {
        MegaInterface->setWindowTitle(QApplication::translate("MegaInterface", "Interface", nullptr));
        label_icon->setText(QString());
        comboBox_DevType->setItemText(0, QApplication::translate("MegaInterface", "LAN", nullptr));
        comboBox_DevType->setItemText(1, QApplication::translate("MegaInterface", "USB", nullptr));

        pushButton_Scan->setText(QApplication::translate("MegaInterface", "Scan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MegaInterface: public Ui_MegaInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEGAINTERFACE_H
