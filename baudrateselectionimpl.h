#ifndef BAUDRATE_SELECTION_IMPL_H
#define BAUDRATE_SELECTION_IMPL_H

#include "ui_baudrateselectionform.h"

class BaudrateSelectionForm : public QDialog, public Ui_BaudRateSelectionForm {
	Q_OBJECT;

public:
    BaudrateSelectionForm (QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    virtual ~BaudrateSelectionForm();

    
};

#endif

// Local Variables: 
// mode:c++
// End:
