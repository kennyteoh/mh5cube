/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Fri 12. Feb 10:56:25 2010
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionPerspective;
    QAction *actionExit;
    QAction *actionSelect_All;
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionLayout_Default;
    QAction *actionLayout_Save;
    QAction *actionLayout_Load;
    QAction *actionSaveAs;
    QAction *actionCoordinates;
    QAction *actionAppend;
    QAction *actionNew;
    QAction *actionNightMode;
    QAction *actionReset_Rotation;
    QAction *actionSettings;
    QAction *actionDeveloperOutput;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuInfo;
    QMenu *menu;
    QMenu *menuAnsicht;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidgetEdit;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tabMove;
    QGridLayout *gridLayout_3;
    QPushButton *pushButtonMoveXMinus;
    QPushButton *pushButtonMoveYMinus;
    QPushButton *pushButtonMoveYPlus;
    QPushButton *pushButtonMoveZMinus;
    QPushButton *pushButtonMoveZPlus;
    QPushButton *pushButtonMoveXPlus;
    QWidget *tabRotate;
    QGridLayout *gridLayout_6;
    QPushButton *pushButtonRotateXMinus;
    QPushButton *pushButtonRotateXPlus;
    QPushButton *pushButtonRotateYMinus;
    QPushButton *pushButtonRotateYPlus;
    QPushButton *pushButtonRotateZMinus;
    QPushButton *pushButtonRotateZPlus;
    QDockWidget *dockWidgetStates;
    QWidget *dockWidgetContents_5;
    QGridLayout *gridLayout_5;
    QPushButton *pushButtonStatesInvert;
    QPushButton *pushButtonStatesUnsetAll;
    QPushButton *pushButtonStatesSetAll;
    QPushButton *pushButtonStatesRandom;
    QDockWidget *dockWidgetSelection;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QSlider *horizontalSliderSelectionColumn;
    QSlider *horizontalSliderSelectionRow;
    QLabel *labelRow;
    QLabel *labelColumn;
    QCheckBox *checkBoxSelectionRow;
    QCheckBox *checkBoxSelectionColumn;
    QSlider *horizontalSliderSelectionLevel;
    QCheckBox *checkBoxSelectionLevel;
    QLabel *labelLevel;
    QPushButton *pushButtonSelectionUnset;
    QPushButton *pushButtonSelectionSet;
    QDockWidget *dockWidgetFigures;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QPushButton *pushButtonFigMoveUp;
    QPushButton *pushButtonFigClone;
    QPushButton *pushButtonFigMoveDown;
    QPushButton *pushButtonFigAdd;
    QPushButton *pushButtonFigInsert;
    QPushButton *pushButtonFigDelete;
    QPushButton *pushButtonFigPlay;
    QPushButton *pushButtonFigTimes;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(874, 653);
        MainWindowClass->setDockNestingEnabled(false);
        MainWindowClass->setDockOptions(QMainWindow::AnimatedDocks);
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/document-save.png")), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/document-open.png")), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionPerspective = new QAction(MainWindowClass);
        actionPerspective->setObjectName(QString::fromUtf8("actionPerspective"));
        actionPerspective->setCheckable(true);
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubePerspective.png")), QIcon::Normal, QIcon::Off);
        actionPerspective->setIcon(icon2);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSelect_All = new QAction(MainWindowClass);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionHelp = new QAction(MainWindowClass);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionLayout_Default = new QAction(MainWindowClass);
        actionLayout_Default->setObjectName(QString::fromUtf8("actionLayout_Default"));
        actionLayout_Save = new QAction(MainWindowClass);
        actionLayout_Save->setObjectName(QString::fromUtf8("actionLayout_Save"));
        actionLayout_Load = new QAction(MainWindowClass);
        actionLayout_Load->setObjectName(QString::fromUtf8("actionLayout_Load"));
        actionSaveAs = new QAction(MainWindowClass);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/document-save-as.png")), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon3);
        actionCoordinates = new QAction(MainWindowClass);
        actionCoordinates->setObjectName(QString::fromUtf8("actionCoordinates"));
        actionCoordinates->setCheckable(true);
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeCoordinates.png")), QIcon::Normal, QIcon::Off);
        actionCoordinates->setIcon(icon4);
        actionAppend = new QAction(MainWindowClass);
        actionAppend->setObjectName(QString::fromUtf8("actionAppend"));
        actionAppend->setIcon(icon1);
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/document-new.png")), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon5);
        actionNightMode = new QAction(MainWindowClass);
        actionNightMode->setObjectName(QString::fromUtf8("actionNightMode"));
        actionNightMode->setCheckable(true);
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeNightMode.png")), QIcon::Normal, QIcon::Off);
        actionNightMode->setIcon(icon6);
        actionReset_Rotation = new QAction(MainWindowClass);
        actionReset_Rotation->setObjectName(QString::fromUtf8("actionReset_Rotation"));
        QIcon icon7;
        icon7.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeResetRotation.png")), QIcon::Normal, QIcon::Off);
        actionReset_Rotation->setIcon(icon7);
        actionSettings = new QAction(MainWindowClass);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        QIcon icon8;
        icon8.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/categories/preferences-system.png")), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon8);
        actionDeveloperOutput = new QAction(MainWindowClass);
        actionDeveloperOutput->setObjectName(QString::fromUtf8("actionDeveloperOutput"));
        actionDeveloperOutput->setEnabled(false);
        actionDeveloperOutput->setShortcutContext(Qt::ApplicationShortcut);
        actionDeveloperOutput->setVisible(false);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 874, 19));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuAnsicht = new QMenu(menuBar);
        menuAnsicht->setObjectName(QString::fromUtf8("menuAnsicht"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(true);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        dockWidgetEdit = new QDockWidget(MainWindowClass);
        dockWidgetEdit->setObjectName(QString::fromUtf8("dockWidgetEdit"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidgetEdit->sizePolicy().hasHeightForWidth());
        dockWidgetEdit->setSizePolicy(sizePolicy);
        dockWidgetEdit->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetEdit->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        gridLayout_4 = new QGridLayout(dockWidgetContents_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setMargin(11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(dockWidgetContents_3);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabMove = new QWidget();
        tabMove->setObjectName(QString::fromUtf8("tabMove"));
        gridLayout_3 = new QGridLayout(tabMove);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setMargin(11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButtonMoveXMinus = new QPushButton(tabMove);
        pushButtonMoveXMinus->setObjectName(QString::fromUtf8("pushButtonMoveXMinus"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonMoveXMinus->sizePolicy().hasHeightForWidth());
        pushButtonMoveXMinus->setSizePolicy(sizePolicy2);
        QIcon icon9;
        icon9.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMoveX-minus.png")), QIcon::Normal, QIcon::Off);
        pushButtonMoveXMinus->setIcon(icon9);
        pushButtonMoveXMinus->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButtonMoveXMinus, 0, 0, 1, 1);

        pushButtonMoveYMinus = new QPushButton(tabMove);
        pushButtonMoveYMinus->setObjectName(QString::fromUtf8("pushButtonMoveYMinus"));
        sizePolicy2.setHeightForWidth(pushButtonMoveYMinus->sizePolicy().hasHeightForWidth());
        pushButtonMoveYMinus->setSizePolicy(sizePolicy2);
        QIcon icon10;
        icon10.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMoveY-minus.png")), QIcon::Normal, QIcon::Off);
        pushButtonMoveYMinus->setIcon(icon10);
        pushButtonMoveYMinus->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButtonMoveYMinus, 3, 0, 1, 1);

        pushButtonMoveYPlus = new QPushButton(tabMove);
        pushButtonMoveYPlus->setObjectName(QString::fromUtf8("pushButtonMoveYPlus"));
        sizePolicy2.setHeightForWidth(pushButtonMoveYPlus->sizePolicy().hasHeightForWidth());
        pushButtonMoveYPlus->setSizePolicy(sizePolicy2);
        QIcon icon11;
        icon11.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMoveY-plus.png")), QIcon::Normal, QIcon::Off);
        pushButtonMoveYPlus->setIcon(icon11);
        pushButtonMoveYPlus->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButtonMoveYPlus, 3, 1, 1, 1);

        pushButtonMoveZMinus = new QPushButton(tabMove);
        pushButtonMoveZMinus->setObjectName(QString::fromUtf8("pushButtonMoveZMinus"));
        sizePolicy2.setHeightForWidth(pushButtonMoveZMinus->sizePolicy().hasHeightForWidth());
        pushButtonMoveZMinus->setSizePolicy(sizePolicy2);
        QIcon icon12;
        icon12.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMoveZ-minus.png")), QIcon::Normal, QIcon::Off);
        pushButtonMoveZMinus->setIcon(icon12);
        pushButtonMoveZMinus->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButtonMoveZMinus, 4, 0, 1, 1);

        pushButtonMoveZPlus = new QPushButton(tabMove);
        pushButtonMoveZPlus->setObjectName(QString::fromUtf8("pushButtonMoveZPlus"));
        sizePolicy2.setHeightForWidth(pushButtonMoveZPlus->sizePolicy().hasHeightForWidth());
        pushButtonMoveZPlus->setSizePolicy(sizePolicy2);
        QIcon icon13;
        icon13.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMoveZ-plus.png")), QIcon::Normal, QIcon::Off);
        pushButtonMoveZPlus->setIcon(icon13);
        pushButtonMoveZPlus->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButtonMoveZPlus, 4, 1, 1, 1);

        pushButtonMoveXPlus = new QPushButton(tabMove);
        pushButtonMoveXPlus->setObjectName(QString::fromUtf8("pushButtonMoveXPlus"));
        sizePolicy2.setHeightForWidth(pushButtonMoveXPlus->sizePolicy().hasHeightForWidth());
        pushButtonMoveXPlus->setSizePolicy(sizePolicy2);
        QIcon icon14;
        icon14.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMoveX-plus.png")), QIcon::Normal, QIcon::Off);
        pushButtonMoveXPlus->setIcon(icon14);
        pushButtonMoveXPlus->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(pushButtonMoveXPlus, 0, 1, 1, 1);

        QIcon icon15;
        icon15.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeMove.png")), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabMove, icon15, QString());
        tabRotate = new QWidget();
        tabRotate->setObjectName(QString::fromUtf8("tabRotate"));
        gridLayout_6 = new QGridLayout(tabRotate);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setMargin(11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pushButtonRotateXMinus = new QPushButton(tabRotate);
        pushButtonRotateXMinus->setObjectName(QString::fromUtf8("pushButtonRotateXMinus"));
        sizePolicy2.setHeightForWidth(pushButtonRotateXMinus->sizePolicy().hasHeightForWidth());
        pushButtonRotateXMinus->setSizePolicy(sizePolicy2);
        QIcon icon16;
        icon16.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeTurnX-minus.png")), QIcon::Normal, QIcon::Off);
        pushButtonRotateXMinus->setIcon(icon16);
        pushButtonRotateXMinus->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(pushButtonRotateXMinus, 0, 0, 1, 1);

        pushButtonRotateXPlus = new QPushButton(tabRotate);
        pushButtonRotateXPlus->setObjectName(QString::fromUtf8("pushButtonRotateXPlus"));
        sizePolicy2.setHeightForWidth(pushButtonRotateXPlus->sizePolicy().hasHeightForWidth());
        pushButtonRotateXPlus->setSizePolicy(sizePolicy2);
        QIcon icon17;
        icon17.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeTurnX-plus.png")), QIcon::Normal, QIcon::Off);
        pushButtonRotateXPlus->setIcon(icon17);
        pushButtonRotateXPlus->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(pushButtonRotateXPlus, 0, 1, 1, 1);

        pushButtonRotateYMinus = new QPushButton(tabRotate);
        pushButtonRotateYMinus->setObjectName(QString::fromUtf8("pushButtonRotateYMinus"));
        QIcon icon18;
        icon18.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeTurnY-minus.png")), QIcon::Normal, QIcon::Off);
        pushButtonRotateYMinus->setIcon(icon18);
        pushButtonRotateYMinus->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(pushButtonRotateYMinus, 1, 0, 1, 1);

        pushButtonRotateYPlus = new QPushButton(tabRotate);
        pushButtonRotateYPlus->setObjectName(QString::fromUtf8("pushButtonRotateYPlus"));
        QIcon icon19;
        icon19.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeTurnY-plus.png")), QIcon::Normal, QIcon::Off);
        pushButtonRotateYPlus->setIcon(icon19);
        pushButtonRotateYPlus->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(pushButtonRotateYPlus, 1, 1, 1, 1);

        pushButtonRotateZMinus = new QPushButton(tabRotate);
        pushButtonRotateZMinus->setObjectName(QString::fromUtf8("pushButtonRotateZMinus"));
        QIcon icon20;
        icon20.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeTurnZ-minus.png")), QIcon::Normal, QIcon::Off);
        pushButtonRotateZMinus->setIcon(icon20);
        pushButtonRotateZMinus->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(pushButtonRotateZMinus, 2, 0, 1, 1);

        pushButtonRotateZPlus = new QPushButton(tabRotate);
        pushButtonRotateZPlus->setObjectName(QString::fromUtf8("pushButtonRotateZPlus"));
        QIcon icon21;
        icon21.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeTurnZ-plus.png")), QIcon::Normal, QIcon::Off);
        pushButtonRotateZPlus->setIcon(icon21);
        pushButtonRotateZPlus->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(pushButtonRotateZPlus, 2, 1, 1, 1);

        QIcon icon22;
        icon22.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeRotate.png")), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabRotate, icon22, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);

        dockWidgetEdit->setWidget(dockWidgetContents_3);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetEdit);
        dockWidgetStates = new QDockWidget(MainWindowClass);
        dockWidgetStates->setObjectName(QString::fromUtf8("dockWidgetStates"));
        sizePolicy.setHeightForWidth(dockWidgetStates->sizePolicy().hasHeightForWidth());
        dockWidgetStates->setSizePolicy(sizePolicy);
        dockWidgetStates->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetStates->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        gridLayout_5 = new QGridLayout(dockWidgetContents_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setMargin(11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButtonStatesInvert = new QPushButton(dockWidgetContents_5);
        pushButtonStatesInvert->setObjectName(QString::fromUtf8("pushButtonStatesInvert"));

        gridLayout_5->addWidget(pushButtonStatesInvert, 1, 1, 1, 1);

        pushButtonStatesUnsetAll = new QPushButton(dockWidgetContents_5);
        pushButtonStatesUnsetAll->setObjectName(QString::fromUtf8("pushButtonStatesUnsetAll"));

        gridLayout_5->addWidget(pushButtonStatesUnsetAll, 0, 1, 1, 1);

        pushButtonStatesSetAll = new QPushButton(dockWidgetContents_5);
        pushButtonStatesSetAll->setObjectName(QString::fromUtf8("pushButtonStatesSetAll"));

        gridLayout_5->addWidget(pushButtonStatesSetAll, 0, 0, 1, 1);

        pushButtonStatesRandom = new QPushButton(dockWidgetContents_5);
        pushButtonStatesRandom->setObjectName(QString::fromUtf8("pushButtonStatesRandom"));

        gridLayout_5->addWidget(pushButtonStatesRandom, 1, 0, 1, 1);

        dockWidgetStates->setWidget(dockWidgetContents_5);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetStates);
        dockWidgetSelection = new QDockWidget(MainWindowClass);
        dockWidgetSelection->setObjectName(QString::fromUtf8("dockWidgetSelection"));
        sizePolicy.setHeightForWidth(dockWidgetSelection->sizePolicy().hasHeightForWidth());
        dockWidgetSelection->setSizePolicy(sizePolicy);
        dockWidgetSelection->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetSelection->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalSliderSelectionColumn = new QSlider(dockWidgetContents);
        horizontalSliderSelectionColumn->setObjectName(QString::fromUtf8("horizontalSliderSelectionColumn"));
        horizontalSliderSelectionColumn->setMinimum(1);
        horizontalSliderSelectionColumn->setMaximum(5);
        horizontalSliderSelectionColumn->setPageStep(1);
        horizontalSliderSelectionColumn->setValue(1);
        horizontalSliderSelectionColumn->setTracking(true);
        horizontalSliderSelectionColumn->setOrientation(Qt::Horizontal);
        horizontalSliderSelectionColumn->setTickPosition(QSlider::TicksBelow);
        horizontalSliderSelectionColumn->setTickInterval(1);

        gridLayout->addWidget(horizontalSliderSelectionColumn, 3, 2, 1, 1);

        horizontalSliderSelectionRow = new QSlider(dockWidgetContents);
        horizontalSliderSelectionRow->setObjectName(QString::fromUtf8("horizontalSliderSelectionRow"));
        horizontalSliderSelectionRow->setMinimum(1);
        horizontalSliderSelectionRow->setMaximum(5);
        horizontalSliderSelectionRow->setPageStep(1);
        horizontalSliderSelectionRow->setValue(1);
        horizontalSliderSelectionRow->setOrientation(Qt::Horizontal);
        horizontalSliderSelectionRow->setTickPosition(QSlider::TicksBelow);
        horizontalSliderSelectionRow->setTickInterval(1);

        gridLayout->addWidget(horizontalSliderSelectionRow, 2, 2, 1, 1);

        labelRow = new QLabel(dockWidgetContents);
        labelRow->setObjectName(QString::fromUtf8("labelRow"));

        gridLayout->addWidget(labelRow, 2, 1, 1, 1);

        labelColumn = new QLabel(dockWidgetContents);
        labelColumn->setObjectName(QString::fromUtf8("labelColumn"));

        gridLayout->addWidget(labelColumn, 3, 1, 1, 1);

        checkBoxSelectionRow = new QCheckBox(dockWidgetContents);
        checkBoxSelectionRow->setObjectName(QString::fromUtf8("checkBoxSelectionRow"));

        gridLayout->addWidget(checkBoxSelectionRow, 2, 3, 1, 1);

        checkBoxSelectionColumn = new QCheckBox(dockWidgetContents);
        checkBoxSelectionColumn->setObjectName(QString::fromUtf8("checkBoxSelectionColumn"));

        gridLayout->addWidget(checkBoxSelectionColumn, 3, 3, 1, 1);

        horizontalSliderSelectionLevel = new QSlider(dockWidgetContents);
        horizontalSliderSelectionLevel->setObjectName(QString::fromUtf8("horizontalSliderSelectionLevel"));
        horizontalSliderSelectionLevel->setMinimum(1);
        horizontalSliderSelectionLevel->setMaximum(5);
        horizontalSliderSelectionLevel->setPageStep(1);
        horizontalSliderSelectionLevel->setValue(1);
        horizontalSliderSelectionLevel->setOrientation(Qt::Horizontal);
        horizontalSliderSelectionLevel->setTickPosition(QSlider::TicksBelow);
        horizontalSliderSelectionLevel->setTickInterval(1);

        gridLayout->addWidget(horizontalSliderSelectionLevel, 1, 2, 1, 1);

        checkBoxSelectionLevel = new QCheckBox(dockWidgetContents);
        checkBoxSelectionLevel->setObjectName(QString::fromUtf8("checkBoxSelectionLevel"));

        gridLayout->addWidget(checkBoxSelectionLevel, 1, 3, 1, 1);

        labelLevel = new QLabel(dockWidgetContents);
        labelLevel->setObjectName(QString::fromUtf8("labelLevel"));

        gridLayout->addWidget(labelLevel, 1, 1, 1, 1);

        pushButtonSelectionUnset = new QPushButton(dockWidgetContents);
        pushButtonSelectionUnset->setObjectName(QString::fromUtf8("pushButtonSelectionUnset"));

        gridLayout->addWidget(pushButtonSelectionUnset, 6, 2, 1, 1);

        pushButtonSelectionSet = new QPushButton(dockWidgetContents);
        pushButtonSelectionSet->setObjectName(QString::fromUtf8("pushButtonSelectionSet"));

        gridLayout->addWidget(pushButtonSelectionSet, 4, 2, 1, 1);

        dockWidgetSelection->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetSelection);
        dockWidgetFigures = new QDockWidget(MainWindowClass);
        dockWidgetFigures->setObjectName(QString::fromUtf8("dockWidgetFigures"));
        dockWidgetFigures->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetFigures->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        gridLayout_2 = new QGridLayout(dockWidgetContents_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setMargin(11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableView = new QTableView(dockWidgetContents_4);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout_2->addWidget(tableView, 1, 0, 1, 2);

        pushButtonFigMoveUp = new QPushButton(dockWidgetContents_4);
        pushButtonFigMoveUp->setObjectName(QString::fromUtf8("pushButtonFigMoveUp"));
        QIcon icon23;
        icon23.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/go-up.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigMoveUp->setIcon(icon23);

        gridLayout_2->addWidget(pushButtonFigMoveUp, 3, 0, 1, 1);

        pushButtonFigClone = new QPushButton(dockWidgetContents_4);
        pushButtonFigClone->setObjectName(QString::fromUtf8("pushButtonFigClone"));
        QIcon icon24;
        icon24.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeClone.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigClone->setIcon(icon24);

        gridLayout_2->addWidget(pushButtonFigClone, 4, 0, 1, 1);

        pushButtonFigMoveDown = new QPushButton(dockWidgetContents_4);
        pushButtonFigMoveDown->setObjectName(QString::fromUtf8("pushButtonFigMoveDown"));
        QIcon icon25;
        icon25.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/go-down.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigMoveDown->setIcon(icon25);

        gridLayout_2->addWidget(pushButtonFigMoveDown, 5, 0, 1, 1);

        pushButtonFigAdd = new QPushButton(dockWidgetContents_4);
        pushButtonFigAdd->setObjectName(QString::fromUtf8("pushButtonFigAdd"));
        QIcon icon26;
        icon26.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/list-add.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigAdd->setIcon(icon26);

        gridLayout_2->addWidget(pushButtonFigAdd, 3, 1, 1, 1);

        pushButtonFigInsert = new QPushButton(dockWidgetContents_4);
        pushButtonFigInsert->setObjectName(QString::fromUtf8("pushButtonFigInsert"));
        QIcon icon27;
        icon27.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/icons_cube/CubeInsert.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigInsert->setIcon(icon27);

        gridLayout_2->addWidget(pushButtonFigInsert, 4, 1, 1, 1);

        pushButtonFigDelete = new QPushButton(dockWidgetContents_4);
        pushButtonFigDelete->setObjectName(QString::fromUtf8("pushButtonFigDelete"));
        QIcon icon28;
        icon28.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/list-remove.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigDelete->setIcon(icon28);

        gridLayout_2->addWidget(pushButtonFigDelete, 5, 1, 1, 1);

        pushButtonFigPlay = new QPushButton(dockWidgetContents_4);
        pushButtonFigPlay->setObjectName(QString::fromUtf8("pushButtonFigPlay"));
        QIcon icon29;
        icon29.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/media-playback-start.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigPlay->setIcon(icon29);
        pushButtonFigPlay->setCheckable(true);
        pushButtonFigPlay->setChecked(false);

        gridLayout_2->addWidget(pushButtonFigPlay, 0, 0, 1, 1);

        pushButtonFigTimes = new QPushButton(dockWidgetContents_4);
        pushButtonFigTimes->setObjectName(QString::fromUtf8("pushButtonFigTimes"));
        QIcon icon30;
        icon30.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/ressources/tango-icon-theme-0.8.90/32x32/actions/appointment-new.png")), QIcon::Normal, QIcon::Off);
        pushButtonFigTimes->setIcon(icon30);

        gridLayout_2->addWidget(pushButtonFigTimes, 0, 1, 1, 1);

        dockWidgetFigures->setWidget(dockWidgetContents_4);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidgetFigures);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuBar->addAction(menuAnsicht->menuAction());
        menuBar->addAction(menu->menuAction());
        menuDatei->addAction(actionNew);
        menuDatei->addSeparator();
        menuDatei->addAction(actionOpen);
        menuDatei->addAction(actionAppend);
        menuDatei->addSeparator();
        menuDatei->addAction(actionSave);
        menuDatei->addAction(actionSaveAs);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExit);
        menuInfo->addSeparator();
        menuInfo->addAction(actionSelect_All);
        menu->addAction(actionAbout);
        menuAnsicht->addAction(actionPerspective);
        menuAnsicht->addAction(actionCoordinates);
        menuAnsicht->addAction(actionNightMode);
        menuAnsicht->addAction(actionReset_Rotation);
        menuAnsicht->addSeparator();
        menuAnsicht->addAction(actionSettings);
        menuAnsicht->addAction(actionDeveloperOutput);
        menuAnsicht->addAction(actionLayout_Save);
        menuAnsicht->addAction(actionLayout_Load);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSaveAs);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPerspective);
        mainToolBar->addAction(actionCoordinates);
        mainToolBar->addAction(actionNightMode);
        mainToolBar->addAction(actionReset_Rotation);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSettings);

        retranslateUi(MainWindowClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindowClass", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindowClass", "Open File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionPerspective->setText(QApplication::translate("MainWindowClass", "Perspective", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPerspective->setToolTip(QApplication::translate("MainWindowClass", "Switch Perspective", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPerspective->setShortcut(QApplication::translate("MainWindowClass", "P", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionSelect_All->setText(QApplication::translate("MainWindowClass", "Select All", 0, QApplication::UnicodeUTF8));
        actionSelect_All->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Shift+A", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowClass", "About", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindowClass", "Help", 0, QApplication::UnicodeUTF8));
        actionLayout_Default->setText(QApplication::translate("MainWindowClass", "Default Layout", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLayout_Default->setToolTip(QApplication::translate("MainWindowClass", "Restore Default Layout", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLayout_Save->setText(QApplication::translate("MainWindowClass", "Save Layout", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLayout_Save->setToolTip(QApplication::translate("MainWindowClass", "Save Current Layout", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLayout_Load->setText(QApplication::translate("MainWindowClass", "Load Layout", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLayout_Load->setToolTip(QApplication::translate("MainWindowClass", "Load Saved Layout", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setText(QApplication::translate("MainWindowClass", "Save As", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("MainWindowClass", "Save As", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setShortcut(QApplication::translate("MainWindowClass", "Shift+S", 0, QApplication::UnicodeUTF8));
        actionCoordinates->setText(QApplication::translate("MainWindowClass", "Coordinates", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCoordinates->setToolTip(QApplication::translate("MainWindowClass", "Display Coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCoordinates->setShortcut(QApplication::translate("MainWindowClass", "C", 0, QApplication::UnicodeUTF8));
        actionAppend->setText(QApplication::translate("MainWindowClass", "Append", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAppend->setToolTip(QApplication::translate("MainWindowClass", "Open File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAppend->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindowClass", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionNightMode->setText(QApplication::translate("MainWindowClass", "NightMode", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNightMode->setToolTip(QApplication::translate("MainWindowClass", "Toggle NightMode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNightMode->setShortcut(QApplication::translate("MainWindowClass", "N", 0, QApplication::UnicodeUTF8));
        actionReset_Rotation->setText(QApplication::translate("MainWindowClass", "Reset Rotation", 0, QApplication::UnicodeUTF8));
        actionReset_Rotation->setShortcut(QApplication::translate("MainWindowClass", "Home", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindowClass", "Settings", 0, QApplication::UnicodeUTF8));
        actionSettings->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        actionDeveloperOutput->setText(QApplication::translate("MainWindowClass", "Developer Output", 0, QApplication::UnicodeUTF8));
        actionDeveloperOutput->setShortcut(QApplication::translate("MainWindowClass", "F12", 0, QApplication::UnicodeUTF8));
        menuDatei->setTitle(QApplication::translate("MainWindowClass", "File", 0, QApplication::UnicodeUTF8));
        menuInfo->setTitle(QApplication::translate("MainWindowClass", "Edit", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindowClass", "?", 0, QApplication::UnicodeUTF8));
        menuAnsicht->setTitle(QApplication::translate("MainWindowClass", "View", 0, QApplication::UnicodeUTF8));
        dockWidgetEdit->setWindowTitle(QApplication::translate("MainWindowClass", "Move/Rotate Figure", 0, QApplication::UnicodeUTF8));
        pushButtonMoveXMinus->setText(QApplication::translate("MainWindowClass", "X-", 0, QApplication::UnicodeUTF8));
        pushButtonMoveYMinus->setText(QApplication::translate("MainWindowClass", "Y-", 0, QApplication::UnicodeUTF8));
        pushButtonMoveYPlus->setText(QApplication::translate("MainWindowClass", "Y+", 0, QApplication::UnicodeUTF8));
        pushButtonMoveZMinus->setText(QApplication::translate("MainWindowClass", "Z-", 0, QApplication::UnicodeUTF8));
        pushButtonMoveZPlus->setText(QApplication::translate("MainWindowClass", "Z+", 0, QApplication::UnicodeUTF8));
        pushButtonMoveXPlus->setText(QApplication::translate("MainWindowClass", "X+", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabMove), QApplication::translate("MainWindowClass", "Move", 0, QApplication::UnicodeUTF8));
        pushButtonRotateXMinus->setText(QApplication::translate("MainWindowClass", "X-", 0, QApplication::UnicodeUTF8));
        pushButtonRotateXPlus->setText(QApplication::translate("MainWindowClass", "X+", 0, QApplication::UnicodeUTF8));
        pushButtonRotateYMinus->setText(QApplication::translate("MainWindowClass", "Y-", 0, QApplication::UnicodeUTF8));
        pushButtonRotateYPlus->setText(QApplication::translate("MainWindowClass", "Y+", 0, QApplication::UnicodeUTF8));
        pushButtonRotateZMinus->setText(QApplication::translate("MainWindowClass", "Z-", 0, QApplication::UnicodeUTF8));
        pushButtonRotateZPlus->setText(QApplication::translate("MainWindowClass", "Z+", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabRotate), QApplication::translate("MainWindowClass", "Rotate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dockWidgetStates->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        dockWidgetStates->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_ACCESSIBILITY
        dockWidgetStates->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        dockWidgetStates->setWindowTitle(QApplication::translate("MainWindowClass", "Edit States", 0, QApplication::UnicodeUTF8));
        pushButtonStatesInvert->setText(QApplication::translate("MainWindowClass", "Invert", 0, QApplication::UnicodeUTF8));
        pushButtonStatesUnsetAll->setText(QApplication::translate("MainWindowClass", "UnsetAll", 0, QApplication::UnicodeUTF8));
        pushButtonStatesSetAll->setText(QApplication::translate("MainWindowClass", "SetAll", 0, QApplication::UnicodeUTF8));
        pushButtonStatesRandom->setText(QApplication::translate("MainWindowClass", "Random", 0, QApplication::UnicodeUTF8));
        dockWidgetSelection->setWindowTitle(QApplication::translate("MainWindowClass", "Selection", 0, QApplication::UnicodeUTF8));
        labelRow->setText(QApplication::translate("MainWindowClass", "Row", 0, QApplication::UnicodeUTF8));
        labelColumn->setText(QApplication::translate("MainWindowClass", "Col", 0, QApplication::UnicodeUTF8));
        checkBoxSelectionRow->setText(QString());
        checkBoxSelectionLevel->setText(QString());
        labelLevel->setText(QApplication::translate("MainWindowClass", "Level", 0, QApplication::UnicodeUTF8));
        pushButtonSelectionUnset->setText(QApplication::translate("MainWindowClass", "Unset", 0, QApplication::UnicodeUTF8));
        pushButtonSelectionSet->setText(QApplication::translate("MainWindowClass", "Set", 0, QApplication::UnicodeUTF8));
        dockWidgetFigures->setWindowTitle(QApplication::translate("MainWindowClass", "Figures", 0, QApplication::UnicodeUTF8));
        pushButtonFigMoveUp->setText(QApplication::translate("MainWindowClass", "Move Up", 0, QApplication::UnicodeUTF8));
        pushButtonFigMoveUp->setShortcut(QApplication::translate("MainWindowClass", "Alt+Up", 0, QApplication::UnicodeUTF8));
        pushButtonFigClone->setText(QApplication::translate("MainWindowClass", "Clone", 0, QApplication::UnicodeUTF8));
        pushButtonFigClone->setShortcut(QApplication::translate("MainWindowClass", "Alt+C", 0, QApplication::UnicodeUTF8));
        pushButtonFigMoveDown->setText(QApplication::translate("MainWindowClass", "Move Down", 0, QApplication::UnicodeUTF8));
        pushButtonFigMoveDown->setShortcut(QApplication::translate("MainWindowClass", "Alt+Down", 0, QApplication::UnicodeUTF8));
        pushButtonFigAdd->setText(QApplication::translate("MainWindowClass", "Add", 0, QApplication::UnicodeUTF8));
        pushButtonFigAdd->setShortcut(QApplication::translate("MainWindowClass", "Alt+A", 0, QApplication::UnicodeUTF8));
        pushButtonFigInsert->setText(QApplication::translate("MainWindowClass", "Insert", 0, QApplication::UnicodeUTF8));
        pushButtonFigInsert->setShortcut(QApplication::translate("MainWindowClass", "Alt+I", 0, QApplication::UnicodeUTF8));
        pushButtonFigDelete->setText(QApplication::translate("MainWindowClass", "Del", 0, QApplication::UnicodeUTF8));
        pushButtonFigDelete->setShortcut(QApplication::translate("MainWindowClass", "Alt+D", 0, QApplication::UnicodeUTF8));
        pushButtonFigPlay->setText(QApplication::translate("MainWindowClass", "Play", 0, QApplication::UnicodeUTF8));
        pushButtonFigTimes->setText(QApplication::translate("MainWindowClass", "Change Times", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
