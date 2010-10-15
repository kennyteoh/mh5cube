/********************************************************************************
** Form generated from reading ui file 'timesdialog.ui'
**
** Created: Fri 12. Feb 10:56:25 2010
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TIMESDIALOG_H
#define UI_TIMESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_TimesDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QPushButton *pushButton_apply;
    QSpinBox *spinBox;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_minus;
    QPushButton *pushButton_plus;

    void setupUi(QDialog *TimesDialog)
    {
        if (TimesDialog->objectName().isEmpty())
            TimesDialog->setObjectName(QString::fromUtf8("TimesDialog"));
        TimesDialog->resize(213, 184);
        buttonBox = new QDialogButtonBox(TimesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 150, 156, 24));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        groupBox = new QGroupBox(TimesDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 70, 171, 61));
        pushButton_apply = new QPushButton(groupBox);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(90, 20, 75, 24));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(40, 20, 46, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(20);
        spinBox->setValue(10);
        groupBox_2 = new QGroupBox(TimesDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 171, 51));
        pushButton_minus = new QPushButton(groupBox_2);
        pushButton_minus->setObjectName(QString::fromUtf8("pushButton_minus"));
        pushButton_minus->setGeometry(QRect(10, 20, 75, 24));
        pushButton_plus = new QPushButton(groupBox_2);
        pushButton_plus->setObjectName(QString::fromUtf8("pushButton_plus"));
        pushButton_plus->setGeometry(QRect(90, 20, 75, 24));

        retranslateUi(TimesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TimesDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(TimesDialog);
    } // setupUi

    void retranslateUi(QDialog *TimesDialog)
    {
        TimesDialog->setWindowTitle(QApplication::translate("TimesDialog", "Change Times", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        TimesDialog->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("TimesDialog", "Fixed Time for all Figures", 0, QApplication::UnicodeUTF8));
        pushButton_apply->setText(QApplication::translate("TimesDialog", "apply", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("TimesDialog", "Faster / Slower", 0, QApplication::UnicodeUTF8));
        pushButton_minus->setText(QApplication::translate("TimesDialog", "-", 0, QApplication::UnicodeUTF8));
        pushButton_plus->setText(QApplication::translate("TimesDialog", "+", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(TimesDialog);
    } // retranslateUi

};

namespace Ui {
    class TimesDialog: public Ui_TimesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESDIALOG_H
