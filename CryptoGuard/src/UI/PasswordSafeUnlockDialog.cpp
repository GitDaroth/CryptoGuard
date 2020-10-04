#include "UI/PasswordSafeUnlockDialog.h"

#include <QFileDialog>

PasswordSafeUnlockDialog::PasswordSafeUnlockDialog(PasswordSafe* passwordSafe, QWidget* parent, Qt::WindowFlags flags) :
	QDialog(parent, flags),
	m_passwordSafe(passwordSafe)
{
	m_ui.setupUi(this);
	connectUiEvents();
}

PasswordSafeUnlockDialog::~PasswordSafeUnlockDialog()
{

}

QString PasswordSafeUnlockDialog::getMasterPassword() const
{
	return m_ui.masterPasswordLineEdit->text();
}

void PasswordSafeUnlockDialog::onUnlockButtonClicked()
{
	if (!m_passwordSafe->isMasterPasswordCorrect(m_ui.masterPasswordLineEdit->text().toStdString()))
		return;

	accept();
}

void PasswordSafeUnlockDialog::onCancelButtonClicked()
{
	reject();
}

void PasswordSafeUnlockDialog::connectUiEvents()
{
	connect(m_ui.unlockButton, &QPushButton::clicked, this, &PasswordSafeUnlockDialog::onUnlockButtonClicked);
	connect(m_ui.cancelButton, &QPushButton::clicked, this, &PasswordSafeUnlockDialog::onCancelButtonClicked);
}
