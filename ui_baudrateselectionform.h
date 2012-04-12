/********************************************************************************
** Form generated from reading UI file 'baudrateselectionform.ui'
**
** Created: Wed 1. Feb 15:02:52 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAUDRATESELECTIONFORM_H
#define UI_BAUDRATESELECTIONFORM_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BaudRateSelectionForm
{
public:
    QGridLayout *gridLayout;
    Q3ButtonGroup *buttonGroup2;
    QVBoxLayout *vboxLayout;
    QRadioButton *BR2400RadioButton;
    QRadioButton *BR4800RadioButton;
    QRadioButton *BR9600RadioButton;
    QRadioButton *BR19200RadioButton;
    QRadioButton *BR38400RadioButton;

    void setupUi(QDialog *BaudRateSelectionForm)
    {
        if (BaudRateSelectionForm->objectName().isEmpty())
            BaudRateSelectionForm->setObjectName(QString::fromUtf8("BaudRateSelectionForm"));
        BaudRateSelectionForm->resize(200, 200);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BaudRateSelectionForm->sizePolicy().hasHeightForWidth());
        BaudRateSelectionForm->setSizePolicy(sizePolicy);
        BaudRateSelectionForm->setMinimumSize(QSize(200, 200));
        BaudRateSelectionForm->setMaximumSize(QSize(200, 200));
        BaudRateSelectionForm->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(BaudRateSelectionForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonGroup2 = new Q3ButtonGroup(BaudRateSelectionForm);
        buttonGroup2->setObjectName(QString::fromUtf8("buttonGroup2"));
        buttonGroup2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2->layout()->setSpacing(6);
        buttonGroup2->layout()->setContentsMargins(11, 11, 11, 11);
        vboxLayout = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup2->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout);
        vboxLayout->setAlignment(Qt::AlignTop);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        BR2400RadioButton = new QRadioButton(buttonGroup2);
        BR2400RadioButton->setObjectName(QString::fromUtf8("BR2400RadioButton"));

        vboxLayout->addWidget(BR2400RadioButton);

        BR4800RadioButton = new QRadioButton(buttonGroup2);
        BR4800RadioButton->setObjectName(QString::fromUtf8("BR4800RadioButton"));

        vboxLayout->addWidget(BR4800RadioButton);

        BR9600RadioButton = new QRadioButton(buttonGroup2);
        BR9600RadioButton->setObjectName(QString::fromUtf8("BR9600RadioButton"));

        vboxLayout->addWidget(BR9600RadioButton);

        BR19200RadioButton = new QRadioButton(buttonGroup2);
        BR19200RadioButton->setObjectName(QString::fromUtf8("BR19200RadioButton"));

        vboxLayout->addWidget(BR19200RadioButton);

        BR38400RadioButton = new QRadioButton(buttonGroup2);
        BR38400RadioButton->setObjectName(QString::fromUtf8("BR38400RadioButton"));

        vboxLayout->addWidget(BR38400RadioButton);


        gridLayout->addWidget(buttonGroup2, 0, 0, 1, 1);


        retranslateUi(BaudRateSelectionForm);

        QMetaObject::connectSlotsByName(BaudRateSelectionForm);
    } // setupUi

    void retranslateUi(QDialog *BaudRateSelectionForm)
    {
        BaudRateSelectionForm->setWindowTitle(QApplication::translate("BaudRateSelectionForm", "Baudrate Selection", 0, QApplication::UnicodeUTF8));
        buttonGroup2->setTitle(QApplication::translate("BaudRateSelectionForm", "Baudrate Selection", 0, QApplication::UnicodeUTF8));
        BR2400RadioButton->setText(QApplication::translate("BaudRateSelectionForm", "2400", 0, QApplication::UnicodeUTF8));
        BR4800RadioButton->setText(QApplication::translate("BaudRateSelectionForm", "4800", 0, QApplication::UnicodeUTF8));
        BR9600RadioButton->setText(QApplication::translate("BaudRateSelectionForm", "9600", 0, QApplication::UnicodeUTF8));
        BR19200RadioButton->setText(QApplication::translate("BaudRateSelectionForm", "19200", 0, QApplication::UnicodeUTF8));
        BR38400RadioButton->setText(QApplication::translate("BaudRateSelectionForm", "38400", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BaudRateSelectionForm: public Ui_BaudRateSelectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAUDRATESELECTIONFORM_H
