/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStop;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionUpload;
    QAction *actionDownload;
    QAction *actionStore;
    QAction *actionSync;
    QAction *actionChinese;
    QAction *actionEnglish;
    QAction *actionMega;
    QAction *actionClassic;
    QAction *actionSearch;
    QAction *actionConnect;
    QAction *actionIP;
    QAction *actionReboot;
    QAction *actionPoweroff;
    QAction *actionWifi;
    QAction *actiontest;
    QAction *actionPref;
    QTabWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOperate;
    QMenu *menuHelp;
    QMenu *menuToo;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1200, 900);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 768));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionUpload = new QAction(MainWindow);
        actionUpload->setObjectName(QStringLiteral("actionUpload"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/image/icon/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpload->setIcon(icon1);
        actionDownload = new QAction(MainWindow);
        actionDownload->setObjectName(QStringLiteral("actionDownload"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/image/icon/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownload->setIcon(icon2);
        actionStore = new QAction(MainWindow);
        actionStore->setObjectName(QStringLiteral("actionStore"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/image/icon/store.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStore->setIcon(icon3);
        actionSync = new QAction(MainWindow);
        actionSync->setObjectName(QStringLiteral("actionSync"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/image/icon/sync.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSync->setIcon(icon4);
        actionChinese = new QAction(MainWindow);
        actionChinese->setObjectName(QStringLiteral("actionChinese"));
        actionChinese->setCheckable(true);
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionEnglish->setCheckable(true);
        actionEnglish->setChecked(false);
        actionMega = new QAction(MainWindow);
        actionMega->setObjectName(QStringLiteral("actionMega"));
        actionMega->setCheckable(true);
        actionMega->setChecked(false);
        actionClassic = new QAction(MainWindow);
        actionClassic->setObjectName(QStringLiteral("actionClassic"));
        actionClassic->setCheckable(true);
        actionClassic->setChecked(false);
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName(QStringLiteral("actionSearch"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/image/icon/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSearch->setIcon(icon5);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/image/h2product/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon6);
        actionIP = new QAction(MainWindow);
        actionIP->setObjectName(QStringLiteral("actionIP"));
        actionIP->setEnabled(false);
        actionReboot = new QAction(MainWindow);
        actionReboot->setObjectName(QStringLiteral("actionReboot"));
        actionPoweroff = new QAction(MainWindow);
        actionPoweroff->setObjectName(QStringLiteral("actionPoweroff"));
        actionWifi = new QAction(MainWindow);
        actionWifi->setObjectName(QStringLiteral("actionWifi"));
        actiontest = new QAction(MainWindow);
        actiontest->setObjectName(QStringLiteral("actiontest"));
        actionPref = new QAction(MainWindow);
        actionPref->setObjectName(QStringLiteral("actionPref"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/res/image/icon/205.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPref->setIcon(icon7);
        centralWidget = new QTabWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setTabBarAutoHide(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOperate = new QMenu(menuBar);
        menuOperate->setObjectName(QStringLiteral("menuOperate"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuToo = new QMenu(menuBar);
        menuToo->setObjectName(QStringLiteral("menuToo"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy1);
        mainToolBar->setFocusPolicy(Qt::ClickFocus);
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(48, 36));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        mainToolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuOperate->menuAction());
        menuBar->addAction(menuToo->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionPoweroff);
        menuFile->addAction(actionReboot);
        menuFile->addAction(actionExit);
        menuOperate->addAction(actionStop);
        menuOperate->addSeparator();
        menuOperate->addAction(actionUpload);
        menuOperate->addAction(actionDownload);
        menuOperate->addAction(actionStore);
        menuOperate->addAction(actionSync);
        menuOperate->addSeparator();
        menuOperate->addAction(actionSearch);
        menuHelp->addAction(actionAbout);
        menuToo->addAction(actionWifi);
        menuToo->addAction(actionPref);
        menuToo->addAction(actiontest);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MEGAROBO", nullptr));
        actionStop->setText(QApplication::translate("MainWindow", "&Stop", nullptr));
#ifndef QT_NO_SHORTCUT
        actionStop->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("MainWindow", "&About", nullptr));
#ifndef QT_NO_SHORTCUT
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_NO_SHORTCUT
        actionHelp->setText(QApplication::translate("MainWindow", "&Help", nullptr));
        actionUpload->setText(QApplication::translate("MainWindow", "&Upload", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUpload->setShortcut(QApplication::translate("MainWindow", "Ctrl+U", nullptr));
#endif // QT_NO_SHORTCUT
        actionDownload->setText(QApplication::translate("MainWindow", "&Download", nullptr));
#ifndef QT_NO_SHORTCUT
        actionDownload->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        actionStore->setText(QApplication::translate("MainWindow", "S&tore", nullptr));
#ifndef QT_NO_SHORTCUT
        actionStore->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", nullptr));
#endif // QT_NO_SHORTCUT
        actionSync->setText(QApplication::translate("MainWindow", "S&ync", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSync->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionChinese->setText(QApplication::translate("MainWindow", "&Chinese", nullptr));
        actionEnglish->setText(QApplication::translate("MainWindow", "&English", nullptr));
        actionMega->setText(QApplication::translate("MainWindow", "&MEGAROBO", nullptr));
        actionClassic->setText(QApplication::translate("MainWindow", "&Classic", nullptr));
        actionSearch->setText(QApplication::translate("MainWindow", "&Search", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSearch->setToolTip(QApplication::translate("MainWindow", "SearchDevice", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSearch->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionConnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_NO_SHORTCUT
        actionIP->setText(QApplication::translate("MainWindow", "MRX-H2:[0.0.0.0]", nullptr));
        actionReboot->setText(QApplication::translate("MainWindow", "&Reboot", nullptr));
#ifndef QT_NO_SHORTCUT
        actionReboot->setShortcut(QApplication::translate("MainWindow", "Ctrl+Alt+R", nullptr));
#endif // QT_NO_SHORTCUT
        actionPoweroff->setText(QApplication::translate("MainWindow", "&Poweroff", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPoweroff->setShortcut(QApplication::translate("MainWindow", "Ctrl+Alt+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionWifi->setText(QApplication::translate("MainWindow", "&Wifi", nullptr));
        actiontest->setText(QApplication::translate("MainWindow", "test", nullptr));
        actionPref->setText(QApplication::translate("MainWindow", "Pref", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File(&F)", nullptr));
        menuOperate->setTitle(QApplication::translate("MainWindow", "Operate(&O)", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help(&H)", nullptr));
        menuToo->setTitle(QApplication::translate("MainWindow", "Tool(&T)", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View(&V)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
