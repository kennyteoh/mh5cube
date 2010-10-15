/********************************************************************************
** Form generated from reading ui file 'dialog.ui'
**
** Created: Fri 12. Feb 10:56:25 2010
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QFormLayout *formLayout;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab_colors;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QPushButton *pushButtonColorLEDOn;
    QLabel *label_4;
    QLabel *labelColorLEDOn;
    QLabel *labelColorLEDOff;
    QPushButton *pushButtonColorLEDOff;
    QLabel *label_6;
    QLabel *labelColorBGNight;
    QPushButton *pushButtonColorBGNight;
    QPushButton *pushButtonColorBGDay;
    QLabel *labelColorBGDay;
    QLabel *label_9;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonDefaultColors;
    QWidget *tab_preview;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_NightMode;
    QPushButton *pushButton_Perspective;
    QPushButton *pushButton_Reset;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(306, 271);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        Dialog->setMaximumSize(QSize(549, 16777215));
        formLayout = new QFormLayout(Dialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        formLayout->setWidget(1, QFormLayout::LabelRole, buttonBox);

        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMaximumSize(QSize(361, 221));
        tabWidget->setTabsClosable(false);
        tab_colors = new QWidget();
        tab_colors->setObjectName(QString::fromUtf8("tab_colors"));
        gridLayout_5 = new QGridLayout(tab_colors);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(tab_colors);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        pushButtonColorLEDOn = new QPushButton(tab_colors);
        pushButtonColorLEDOn->setObjectName(QString::fromUtf8("pushButtonColorLEDOn"));

        gridLayout->addWidget(pushButtonColorLEDOn, 0, 2, 1, 1);

        label_4 = new QLabel(tab_colors);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        labelColorLEDOn = new QLabel(tab_colors);
        labelColorLEDOn->setObjectName(QString::fromUtf8("labelColorLEDOn"));
        sizePolicy.setHeightForWidth(labelColorLEDOn->sizePolicy().hasHeightForWidth());
        labelColorLEDOn->setSizePolicy(sizePolicy);
        labelColorLEDOn->setMinimumSize(QSize(20, 20));
        labelColorLEDOn->setAutoFillBackground(false);
        labelColorLEDOn->setFrameShape(QFrame::Box);
        labelColorLEDOn->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(labelColorLEDOn, 0, 1, 1, 1);

        labelColorLEDOff = new QLabel(tab_colors);
        labelColorLEDOff->setObjectName(QString::fromUtf8("labelColorLEDOff"));
        sizePolicy.setHeightForWidth(labelColorLEDOff->sizePolicy().hasHeightForWidth());
        labelColorLEDOff->setSizePolicy(sizePolicy);
        labelColorLEDOff->setMinimumSize(QSize(20, 20));
        labelColorLEDOff->setFrameShape(QFrame::Box);

        gridLayout->addWidget(labelColorLEDOff, 1, 1, 1, 1);

        pushButtonColorLEDOff = new QPushButton(tab_colors);
        pushButtonColorLEDOff->setObjectName(QString::fromUtf8("pushButtonColorLEDOff"));

        gridLayout->addWidget(pushButtonColorLEDOff, 1, 2, 1, 1);

        label_6 = new QLabel(tab_colors);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        labelColorBGNight = new QLabel(tab_colors);
        labelColorBGNight->setObjectName(QString::fromUtf8("labelColorBGNight"));
        sizePolicy.setHeightForWidth(labelColorBGNight->sizePolicy().hasHeightForWidth());
        labelColorBGNight->setSizePolicy(sizePolicy);
        labelColorBGNight->setMinimumSize(QSize(20, 20));
        labelColorBGNight->setAutoFillBackground(false);
        labelColorBGNight->setFrameShape(QFrame::Box);

        gridLayout->addWidget(labelColorBGNight, 2, 1, 1, 1);

        pushButtonColorBGNight = new QPushButton(tab_colors);
        pushButtonColorBGNight->setObjectName(QString::fromUtf8("pushButtonColorBGNight"));

        gridLayout->addWidget(pushButtonColorBGNight, 2, 2, 1, 1);

        pushButtonColorBGDay = new QPushButton(tab_colors);
        pushButtonColorBGDay->setObjectName(QString::fromUtf8("pushButtonColorBGDay"));

        gridLayout->addWidget(pushButtonColorBGDay, 4, 2, 1, 1);

        labelColorBGDay = new QLabel(tab_colors);
        labelColorBGDay->setObjectName(QString::fromUtf8("labelColorBGDay"));
        sizePolicy.setHeightForWidth(labelColorBGDay->sizePolicy().hasHeightForWidth());
        labelColorBGDay->setSizePolicy(sizePolicy);
        labelColorBGDay->setMinimumSize(QSize(20, 20));
        labelColorBGDay->setFrameShape(QFrame::Box);

        gridLayout->addWidget(labelColorBGDay, 4, 1, 1, 1);

        label_9 = new QLabel(tab_colors);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 0, 1, 1);

        pushButtonDefaultColors = new QPushButton(tab_colors);
        pushButtonDefaultColors->setObjectName(QString::fromUtf8("pushButtonDefaultColors"));

        gridLayout_5->addWidget(pushButtonDefaultColors, 1, 0, 1, 1);

        tabWidget->addTab(tab_colors, QString());
        tab_preview = new QWidget();
        tab_preview->setObjectName(QString::fromUtf8("tab_preview"));
        tab_preview->setEnabled(true);
        gridLayout_6 = new QGridLayout(tab_preview);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 0, 0, 1, 1);

        pushButton_NightMode = new QPushButton(tab_preview);
        pushButton_NightMode->setObjectName(QString::fromUtf8("pushButton_NightMode"));
        pushButton_NightMode->setCheckable(true);

        gridLayout_2->addWidget(pushButton_NightMode, 0, 1, 1, 1);

        pushButton_Perspective = new QPushButton(tab_preview);
        pushButton_Perspective->setObjectName(QString::fromUtf8("pushButton_Perspective"));
        pushButton_Perspective->setCheckable(true);

        gridLayout_2->addWidget(pushButton_Perspective, 1, 1, 1, 1);

        pushButton_Reset = new QPushButton(tab_preview);
        pushButton_Reset->setObjectName(QString::fromUtf8("pushButton_Reset"));

        gridLayout_2->addWidget(pushButton_Reset, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 1, 1, 1, 1);

        label = new QLabel(tab_preview);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_6->addWidget(label, 0, 1, 1, 1);

        tabWidget->addTab(tab_preview, QString());

        formLayout->setWidget(0, QFormLayout::LabelRole, tabWidget);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Settings", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        Dialog->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label_3->setText(QApplication::translate("Dialog", "LED (On)", 0, QApplication::UnicodeUTF8));
        pushButtonColorLEDOn->setText(QApplication::translate("Dialog", "change Color", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "LED (Off)", 0, QApplication::UnicodeUTF8));
        labelColorLEDOn->setText(QString());
        labelColorLEDOff->setText(QString());
        pushButtonColorLEDOff->setText(QApplication::translate("Dialog", "change Color", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog", "Background (Night-Mode)", 0, QApplication::UnicodeUTF8));
        labelColorBGNight->setText(QString());
        pushButtonColorBGNight->setText(QApplication::translate("Dialog", "change Color", 0, QApplication::UnicodeUTF8));
        pushButtonColorBGDay->setText(QApplication::translate("Dialog", "change Color", 0, QApplication::UnicodeUTF8));
        labelColorBGDay->setText(QString());
        label_9->setText(QApplication::translate("Dialog", "Background(Day-Mode)", 0, QApplication::UnicodeUTF8));
        pushButtonDefaultColors->setText(QApplication::translate("Dialog", "Default Colors", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_colors), QApplication::translate("Dialog", "Colors", 0, QApplication::UnicodeUTF8));
        pushButton_NightMode->setText(QApplication::translate("Dialog", "NightMode", 0, QApplication::UnicodeUTF8));
        pushButton_Perspective->setText(QApplication::translate("Dialog", "Perspective", 0, QApplication::UnicodeUTF8));
        pushButton_Reset->setText(QApplication::translate("Dialog", "Reset", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Turn the Cube to select the desired Perspective", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_preview), QApplication::translate("Dialog", "Preview", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
