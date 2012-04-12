#ifndef COMCHANNEL_SELECTION_IMPL_H
#define COMCHANNEL_SELECTION_IMPL_H

#include "ui_commchannelselform.h"

class commchannelSelForm : public QDialog, public Ui_commchannelSelForm {
	Q_OBJECT;

private slots:
	void comClicked_Hndl(bool checked);
	void sockClicked_Hndl(bool checked);
public:
    commchannelSelForm (QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    virtual ~commchannelSelForm();

    
};

#endif

// Local Variables: 
// mode:c++
// End:
