#include "comselectionimpl.h"

ComSelectionForm::ComSelectionForm (QWidget* parent, const char* name, bool modal, Qt::WFlags fl)
    : QDialog (parent, name, modal, fl), Ui_COMSelectionForm()
{
    setupUi (this);
}

ComSelectionForm::~ComSelectionForm()
{
}

