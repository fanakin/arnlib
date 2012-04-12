/********************************************************************************
** Form generated from reading UI file 'comselectionform.ui'
**
** Created: Wed 1. Feb 15:02:53 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMSELECTIONFORM_H
#define UI_COMSELECTIONFORM_H

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

QT_BEGIN_NAMESPACE

class Ui_COMSelectionForm
{
public:
    QGridLayout *gridLayout;
    Q3ButtonGroup *ComPortButtonGroup;
    QGridLayout *gridLayout1;
    QRadioButton *COM1Button;
    QRadioButton *COM2Button;
    QRadioButton *COM3Button;
    QRadioButton *COM4Button;

    void setupUi(QDialog *COMSelectionForm)
    {
        if (COMSelectionForm->objectName().isEmpty())
            COMSelectionForm->setObjectName(QString::fromUtf8("COMSelectionForm"));
        COMSelectionForm->resize(200, 200);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(COMSelectionForm->sizePolicy().hasHeightForWidth());
        COMSelectionForm->setSizePolicy(sizePolicy);
        COMSelectionForm->setMinimumSize(QSize(200, 200));
        COMSelectionForm->setMaximumSize(QSize(200, 200));
        COMSelectionForm->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(COMSelectionForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ComPortButtonGroup = new Q3ButtonGroup(COMSelectionForm);
        ComPortButtonGroup->setObjectName(QString::fromUtf8("ComPortButtonGroup"));
        ComPortButtonGroup->setRadioButtonExclusive(true);
        ComPortButtonGroup->setColumnLayout(0, Qt::Vertical);
        ComPortButtonGroup->layout()->setSpacing(16);
        ComPortButtonGroup->layout()->setContentsMargins(12, 12, 12, 12);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(ComPortButtonGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        COM1Button = new QRadioButton(ComPortButtonGroup);
        COM1Button->setObjectName(QString::fromUtf8("COM1Button"));
        COM1Button->setChecked(true);

        gridLayout1->addWidget(COM1Button, 0, 0, 1, 1);

        COM2Button = new QRadioButton(ComPortButtonGroup);
        COM2Button->setObjectName(QString::fromUtf8("COM2Button"));
        COM2Button->setChecked(false);

        gridLayout1->addWidget(COM2Button, 1, 0, 1, 1);

        COM3Button = new QRadioButton(ComPortButtonGroup);
        COM3Button->setObjectName(QString::fromUtf8("COM3Button"));

        gridLayout1->addWidget(COM3Button, 2, 0, 1, 1);

        COM4Button = new QRadioButton(ComPortButtonGroup);
        COM4Button->setObjectName(QString::fromUtf8("COM4Button"));

        gridLayout1->addWidget(COM4Button, 3, 0, 1, 1);


        gridLayout->addWidget(ComPortButtonGroup, 0, 0, 1, 1);


        retranslateUi(COMSelectionForm);

        QMetaObject::connectSlotsByName(COMSelectionForm);
    } // setupUi

    void retranslateUi(QDialog *COMSelectionForm)
    {
        COMSelectionForm->setWindowTitle(QApplication::translate("COMSelectionForm", "Selezione Porta COM", 0, QApplication::UnicodeUTF8));
        ComPortButtonGroup->setTitle(QApplication::translate("COMSelectionForm", "Seleziona porta COM", 0, QApplication::UnicodeUTF8));
        COM1Button->setText(QApplication::translate("COMSelectionForm", "COM 1", 0, QApplication::UnicodeUTF8));
        COM2Button->setText(QApplication::translate("COMSelectionForm", "COM 2", 0, QApplication::UnicodeUTF8));
        COM3Button->setText(QApplication::translate("COMSelectionForm", "COM 3", 0, QApplication::UnicodeUTF8));
        COM4Button->setText(QApplication::translate("COMSelectionForm", "COM 4", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class COMSelectionForm: public Ui_COMSelectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMSELECTIONFORM_H
