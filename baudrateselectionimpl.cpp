#include "baudrateselectionimpl.h"

BaudrateSelectionForm::BaudrateSelectionForm (QWidget* parent, const char* name, bool modal, Qt::WFlags fl)
    : QDialog (parent, name, modal, fl), Ui_BaudRateSelectionForm()
{
    setupUi (this);
}

BaudrateSelectionForm::~BaudrateSelectionForm()
{
}

