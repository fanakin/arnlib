#ifndef COM_SELECTION_IMPL_H
#define COM_SELECTION_IMPL_H

#include "ui_comselectionform.h"

class ComSelectionForm : public QDialog, public Ui_COMSelectionForm {
	Q_OBJECT;

public:
    ComSelectionForm (QWidget *parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    virtual ~ComSelectionForm();

    
};

#endif

// Local Variables: 
// mode:c++
// End:
