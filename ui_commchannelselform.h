/********************************************************************************
** Form generated from reading UI file 'commchannelselform.ui'
**
** Created: Wed 1. Feb 15:02:53 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMCHANNELSELFORM_H
#define UI_COMMCHANNELSELFORM_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_commchannelSelForm
{
public:
    QGridLayout *gridLayout;
    Q3ButtonGroup *CanaliRadioGroup;
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QRadioButton *COM;
    QRadioButton *Socket;
    QHBoxLayout *hboxLayout1;
    Q3Frame *frame4;
    QHBoxLayout *hboxLayout2;
    Q3ButtonGroup *COMPortButtonGroup;
    QVBoxLayout *vboxLayout1;
    QRadioButton *rbCOM1;
    QRadioButton *rbCOM2;
    QRadioButton *rbCOM3;
    QRadioButton *rbCOM4;
    Q3ButtonGroup *BuadRatebuttonGroup;
    QVBoxLayout *vboxLayout2;
    QRadioButton *BR9600;
    QRadioButton *BR38400;
    QRadioButton *BR19200;
    QRadioButton *BR115200;
    Q3Frame *frame5;
    QVBoxLayout *vboxLayout3;
    QLabel *HostTextLabel;
    QLineEdit *host;
    QLabel *TCPPortTextLable;
    QLineEdit *port;

    void setupUi(QDialog *commchannelSelForm)
    {
        if (commchannelSelForm->objectName().isEmpty())
            commchannelSelForm->setObjectName(QString::fromUtf8("commchannelSelForm"));
        commchannelSelForm->resize(579, 342);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(commchannelSelForm->sizePolicy().hasHeightForWidth());
        commchannelSelForm->setSizePolicy(sizePolicy);
        commchannelSelForm->setMinimumSize(QSize(0, 0));
        commchannelSelForm->setMaximumSize(QSize(32767, 32767));
        commchannelSelForm->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(commchannelSelForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        CanaliRadioGroup = new Q3ButtonGroup(commchannelSelForm);
        CanaliRadioGroup->setObjectName(QString::fromUtf8("CanaliRadioGroup"));
        CanaliRadioGroup->setExclusive(true);
        widget = new QWidget(CanaliRadioGroup);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 25, 531, 271));
        vboxLayout = new QVBoxLayout(widget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        COM = new QRadioButton(widget);
        COM->setObjectName(QString::fromUtf8("COM"));

        hboxLayout->addWidget(COM);

        Socket = new QRadioButton(widget);
        Socket->setObjectName(QString::fromUtf8("Socket"));

        hboxLayout->addWidget(Socket);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        frame4 = new Q3Frame(widget);
        frame4->setObjectName(QString::fromUtf8("frame4"));
        frame4->setFrameShape(QFrame::NoFrame);
        frame4->setFrameShadow(QFrame::Plain);
        hboxLayout2 = new QHBoxLayout(frame4);
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(11, 11, 11, 11);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        COMPortButtonGroup = new Q3ButtonGroup(frame4);
        COMPortButtonGroup->setObjectName(QString::fromUtf8("COMPortButtonGroup"));
        COMPortButtonGroup->setColumnLayout(0, Qt::Vertical);
        COMPortButtonGroup->layout()->setSpacing(6);
        COMPortButtonGroup->layout()->setContentsMargins(11, 11, 11, 11);
        vboxLayout1 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(COMPortButtonGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout1);
        vboxLayout1->setAlignment(Qt::AlignTop);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        rbCOM1 = new QRadioButton(COMPortButtonGroup);
        rbCOM1->setObjectName(QString::fromUtf8("rbCOM1"));

        vboxLayout1->addWidget(rbCOM1);

        rbCOM2 = new QRadioButton(COMPortButtonGroup);
        rbCOM2->setObjectName(QString::fromUtf8("rbCOM2"));

        vboxLayout1->addWidget(rbCOM2);

        rbCOM3 = new QRadioButton(COMPortButtonGroup);
        rbCOM3->setObjectName(QString::fromUtf8("rbCOM3"));

        vboxLayout1->addWidget(rbCOM3);

        rbCOM4 = new QRadioButton(COMPortButtonGroup);
        rbCOM4->setObjectName(QString::fromUtf8("rbCOM4"));

        vboxLayout1->addWidget(rbCOM4);


        hboxLayout2->addWidget(COMPortButtonGroup);

        BuadRatebuttonGroup = new Q3ButtonGroup(frame4);
        BuadRatebuttonGroup->setObjectName(QString::fromUtf8("BuadRatebuttonGroup"));
        BuadRatebuttonGroup->setExclusive(false);
        BuadRatebuttonGroup->setColumnLayout(0, Qt::Vertical);
        BuadRatebuttonGroup->layout()->setSpacing(6);
        BuadRatebuttonGroup->layout()->setContentsMargins(11, 11, 11, 11);
        vboxLayout2 = new QVBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(BuadRatebuttonGroup->layout());
        if (boxlayout1)
            boxlayout1->addLayout(vboxLayout2);
        vboxLayout2->setAlignment(Qt::AlignTop);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        BR9600 = new QRadioButton(BuadRatebuttonGroup);
        BR9600->setObjectName(QString::fromUtf8("BR9600"));

        vboxLayout2->addWidget(BR9600);

        BR38400 = new QRadioButton(BuadRatebuttonGroup);
        BR38400->setObjectName(QString::fromUtf8("BR38400"));

        vboxLayout2->addWidget(BR38400);

        BR19200 = new QRadioButton(BuadRatebuttonGroup);
        BR19200->setObjectName(QString::fromUtf8("BR19200"));

        vboxLayout2->addWidget(BR19200);

        BR115200 = new QRadioButton(BuadRatebuttonGroup);
        BR115200->setObjectName(QString::fromUtf8("BR115200"));

        vboxLayout2->addWidget(BR115200);


        hboxLayout2->addWidget(BuadRatebuttonGroup);


        hboxLayout1->addWidget(frame4);

        frame5 = new Q3Frame(widget);
        frame5->setObjectName(QString::fromUtf8("frame5"));
        frame5->setFrameShape(QFrame::NoFrame);
        frame5->setFrameShadow(QFrame::Plain);
        vboxLayout3 = new QVBoxLayout(frame5);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setContentsMargins(11, 11, 11, 11);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        HostTextLabel = new QLabel(frame5);
        HostTextLabel->setObjectName(QString::fromUtf8("HostTextLabel"));

        vboxLayout3->addWidget(HostTextLabel);

        host = new QLineEdit(frame5);
        host->setObjectName(QString::fromUtf8("host"));

        vboxLayout3->addWidget(host);

        TCPPortTextLable = new QLabel(frame5);
        TCPPortTextLable->setObjectName(QString::fromUtf8("TCPPortTextLable"));

        vboxLayout3->addWidget(TCPPortTextLable);

        port = new QLineEdit(frame5);
        port->setObjectName(QString::fromUtf8("port"));

        vboxLayout3->addWidget(port);


        hboxLayout1->addWidget(frame5);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout->addWidget(CanaliRadioGroup, 0, 0, 1, 1);


        retranslateUi(commchannelSelForm);

        QMetaObject::connectSlotsByName(commchannelSelForm);
    } // setupUi

    void retranslateUi(QDialog *commchannelSelForm)
    {
        commchannelSelForm->setWindowTitle(QApplication::translate("commchannelSelForm", "Chennel Selection", 0, QApplication::UnicodeUTF8));
        CanaliRadioGroup->setTitle(QApplication::translate("commchannelSelForm", "Channels", 0, QApplication::UnicodeUTF8));
        COM->setText(QApplication::translate("commchannelSelForm", "COM", 0, QApplication::UnicodeUTF8));
        Socket->setText(QApplication::translate("commchannelSelForm", "TCP/IP Socket", 0, QApplication::UnicodeUTF8));
        COMPortButtonGroup->setTitle(QApplication::translate("commchannelSelForm", "Com Ports", 0, QApplication::UnicodeUTF8));
        rbCOM1->setText(QApplication::translate("commchannelSelForm", "COM 1", 0, QApplication::UnicodeUTF8));
        rbCOM2->setText(QApplication::translate("commchannelSelForm", "COM 2", 0, QApplication::UnicodeUTF8));
        rbCOM3->setText(QApplication::translate("commchannelSelForm", "ttyUSB0", 0, QApplication::UnicodeUTF8));
        rbCOM4->setText(QApplication::translate("commchannelSelForm", "ttyUSB1", 0, QApplication::UnicodeUTF8));
        BuadRatebuttonGroup->setTitle(QApplication::translate("commchannelSelForm", "BaudRate", 0, QApplication::UnicodeUTF8));
        BR9600->setText(QApplication::translate("commchannelSelForm", "9600", 0, QApplication::UnicodeUTF8));
        BR38400->setText(QApplication::translate("commchannelSelForm", "38400", 0, QApplication::UnicodeUTF8));
        BR19200->setText(QApplication::translate("commchannelSelForm", "19200", 0, QApplication::UnicodeUTF8));
        BR115200->setText(QApplication::translate("commchannelSelForm", "115200", 0, QApplication::UnicodeUTF8));
        HostTextLabel->setText(QApplication::translate("commchannelSelForm", "HOST (ip address or name)", 0, QApplication::UnicodeUTF8));
        TCPPortTextLable->setText(QApplication::translate("commchannelSelForm", "TCP Port", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class commchannelSelForm: public Ui_commchannelSelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMCHANNELSELFORM_H
