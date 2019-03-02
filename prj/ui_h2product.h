/********************************************************************************
** Form generated from reading UI file 'h2product.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H2PRODUCT_H
#define UI_H2PRODUCT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H2Product
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLabel *label_picture;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_ip;
    QLabel *labelAddressTip;
    QLabel *label_5;
    QLabel *label_sn;
    QLabel *label_type;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_version;
    QLabel *label_7;
    QPushButton *pushButton_status;

    void setupUi(QWidget *H2Product)
    {
        if (H2Product->objectName().isEmpty())
            H2Product->setObjectName(QStringLiteral("H2Product"));
        H2Product->resize(734, 383);
        gridLayout_2 = new QGridLayout(H2Product);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 263, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        label_picture = new QLabel(H2Product);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setMinimumSize(QSize(100, 100));
        label_picture->setFrameShape(QFrame::Box);
        label_picture->setPixmap(QPixmap(QString::fromUtf8(":/res/image/h2product/product.png")));

        gridLayout_2->addWidget(label_picture, 0, 1, 1, 1);

        groupBox = new QGroupBox(H2Product);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(310, 240));
        QFont font;
        font.setPointSize(9);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_ip = new QLabel(groupBox);
        label_ip->setObjectName(QStringLiteral("label_ip"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_ip->sizePolicy().hasHeightForWidth());
        label_ip->setSizePolicy(sizePolicy);
        label_ip->setMinimumSize(QSize(200, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        label_ip->setFont(font1);
        label_ip->setText(QStringLiteral(""));
        label_ip->setScaledContents(false);
        label_ip->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_ip->setMargin(6);
        label_ip->setIndent(0);

        gridLayout->addWidget(label_ip, 0, 1, 1, 1);

        labelAddressTip = new QLabel(groupBox);
        labelAddressTip->setObjectName(QStringLiteral("labelAddressTip"));
        sizePolicy.setHeightForWidth(labelAddressTip->sizePolicy().hasHeightForWidth());
        labelAddressTip->setSizePolicy(sizePolicy);
        labelAddressTip->setMinimumSize(QSize(80, 20));
        QFont font2;
        font2.setPointSize(11);
        labelAddressTip->setFont(font2);
        labelAddressTip->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelAddressTip->setIndent(0);

        gridLayout->addWidget(labelAddressTip, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(80, 20));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5->setIndent(0);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        label_sn = new QLabel(groupBox);
        label_sn->setObjectName(QStringLiteral("label_sn"));
        sizePolicy.setHeightForWidth(label_sn->sizePolicy().hasHeightForWidth());
        label_sn->setSizePolicy(sizePolicy);
        label_sn->setMinimumSize(QSize(200, 20));
        label_sn->setFont(font1);
        label_sn->setText(QStringLiteral(""));
        label_sn->setScaledContents(false);
        label_sn->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_sn->setMargin(6);
        label_sn->setIndent(0);

        gridLayout->addWidget(label_sn, 2, 1, 1, 1);

        label_type = new QLabel(groupBox);
        label_type->setObjectName(QStringLiteral("label_type"));
        sizePolicy.setHeightForWidth(label_type->sizePolicy().hasHeightForWidth());
        label_type->setSizePolicy(sizePolicy);
        label_type->setMinimumSize(QSize(200, 20));
        label_type->setFont(font1);
        label_type->setText(QStringLiteral(""));
        label_type->setScaledContents(false);
        label_type->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_type->setMargin(6);
        label_type->setIndent(0);

        gridLayout->addWidget(label_type, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(80, 20));
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3->setIndent(0);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);

        label_version = new QLabel(groupBox);
        label_version->setObjectName(QStringLiteral("label_version"));
        sizePolicy.setHeightForWidth(label_version->sizePolicy().hasHeightForWidth());
        label_version->setSizePolicy(sizePolicy);
        label_version->setMinimumSize(QSize(200, 20));
        label_version->setFont(font1);
        label_version->setText(QStringLiteral(""));
        label_version->setScaledContents(false);
        label_version->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_version->setMargin(6);
        label_version->setIndent(0);

        gridLayout->addWidget(label_version, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(80, 20));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7->setIndent(0);

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        pushButton_status = new QPushButton(groupBox);
        pushButton_status->setObjectName(QStringLiteral("pushButton_status"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_status->sizePolicy().hasHeightForWidth());
        pushButton_status->setSizePolicy(sizePolicy1);
        pushButton_status->setFocusPolicy(Qt::ClickFocus);
        pushButton_status->setStyleSheet(QLatin1String("border-color: rgba(255, 255, 255, 0);\n"
"background-color: rgba(255, 255, 255, 0);\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/h2product/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_status->setIcon(icon);
        pushButton_status->setIconSize(QSize(200, 50));
        pushButton_status->setAutoRepeatInterval(800);
        pushButton_status->setFlat(true);

        gridLayout->addWidget(pushButton_status, 5, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(H2Product);

        QMetaObject::connectSlotsByName(H2Product);
    } // setupUi

    void retranslateUi(QWidget *H2Product)
    {
        H2Product->setWindowTitle(QApplication::translate("H2Product", "Form", nullptr));
        label_picture->setText(QString());
        groupBox->setTitle(QApplication::translate("H2Product", "Product", nullptr));
        labelAddressTip->setText(QApplication::translate("H2Product", "ID\357\274\232", nullptr));
        label_5->setText(QApplication::translate("H2Product", "SN:", nullptr));
        label_3->setText(QApplication::translate("H2Product", "Type:", nullptr));
        label_7->setText(QApplication::translate("H2Product", "Version:", nullptr));
        pushButton_status->setText(QString());
#ifndef QT_NO_SHORTCUT
        pushButton_status->setShortcut(QString());
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class H2Product: public Ui_H2Product {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H2PRODUCT_H
