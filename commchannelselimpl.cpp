#include "commchannelselimpl.h"

commchannelSelForm::commchannelSelForm (QWidget* parent, const char*name, bool modal, Qt::WFlags flg)
    : QDialog (parent, name, modal, flg), Ui_commchannelSelForm()
{
    setupUi (this);
	connect(COM,SIGNAL(clicked(bool)),this,SLOT( comClicked_Hndl(bool)) ) ;
	connect(Socket,SIGNAL(clicked(bool)),this,SLOT( sockClicked_Hndl(bool)) ) ;
#ifdef WIN32
	rbCOM3->setText("COM3");
	rbCOM4->setText("COM4");
#endif
}

commchannelSelForm::~commchannelSelForm()
{
}

void commchannelSelForm::comClicked_Hndl(bool checked)
{
	if (checked) {
		host->setEnabled(false);
		port->setEnabled(false);
		rbCOM1->setEnabled(true);
		rbCOM2->setEnabled(true);
		rbCOM3->setEnabled(true);
		rbCOM4->setEnabled(true);
		BR9600->setEnabled(true);
		BR19200->setEnabled(true);
		BR38400->setEnabled(true);
		BR115200->setEnabled(true);
	}
}

void commchannelSelForm::sockClicked_Hndl(bool checked)
{
	if (checked) {
		host->setEnabled(true);
		port->setEnabled(true);
		rbCOM1->setEnabled(false);
		rbCOM2->setEnabled(false);
		rbCOM3->setEnabled(false);
		rbCOM4->setEnabled(false);
		BR9600->setEnabled(false);
		BR19200->setEnabled(false);
		BR38400->setEnabled(false);
		BR115200->setEnabled(false);
	}
}
